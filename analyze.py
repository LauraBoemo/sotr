import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np
import sys
import os

# Configurações
plt.style.use('seaborn-v0_8-darkgrid')
COLORS = {1: '#e74c3c', 2: '#2ecc71', 3: '#3498db', 4: '#f39c12', 5: '#e67e22'}
TASK_NAMES = {1: 'Task 1 (P1)', 2: 'Task 2 (P2)', 3: 'Task 3 (P3)', 
              4: 'Task 4 (P4)', 5: 'Task 5 (P2)'}

def load_data(filename):
    """Carrega dados do CSV"""
    print(f"📂 Carregando dados de {filename}...")
    try:
        df = pd.read_csv(filename)
        print(f"✓ {len(df)} eventos carregados")
        print(f"✓ Colunas encontradas: {list(df.columns)}")
        print(f"✓ Primeiras linhas:")
        print(df.head())
        return df
    except Exception as e:
        print(f"❌ Erro ao carregar arquivo: {e}")
        sys.exit(1)

def calculate_executions(df):
    """
    Calcula intervalos de execução para cada tarefa
    Agrupa eventos S (Start) e E (End) consecutivos
    """
    executions = {1: [], 2: [], 3: [], 4: [], 5: []}
    
    print("\n🔄 Processando eventos...")
    
    for task_id in range(1, 6):
        # Filtrar eventos desta tarefa
        task_events = df[df['Task'] == task_id].sort_values('Timestamp_us')
        
        start_time = None
        count = 0
        
        for idx, row in task_events.iterrows():
            timestamp = row['Timestamp_us']
            event = row['Event']
            
            if event == 'S':
                start_time = timestamp
            elif event == 'E' and start_time is not None:
                duration = timestamp - start_time
                if duration > 0:  # Ignorar durações inválidas
                    executions[task_id].append((start_time, duration))
                    count += 1
                start_time = None
        
        print(f"  Task {task_id}: {count} execuções completas encontradas")
    
    return executions

def plot_gantt_chart(executions, output_file='gantt_chart.png'):
    """Cria diagrama de Gantt"""
    print("\n📊 Gerando diagrama de Gantt...")
    
    # Verificar se temos dados
    total_execs = sum(len(execs) for execs in executions.values())
    if total_execs == 0:
        print("⚠️  Aviso: Nenhuma execução completa (pares S-E) encontrada!")
        print("   Verifique se o CSV tem eventos 'S' e 'E' alternados")
        return
    
    fig, ax = plt.subplots(figsize=(16, 8))
    
    for task_id in range(1, 6):
        y_pos = 6 - task_id
        for start, duration in executions[task_id]:
            ax.barh(y_pos, duration, left=start, height=0.7,
                   color=COLORS[task_id], alpha=0.8, edgecolor='black', linewidth=0.5)
    
    ax.set_yticks(range(1, 6))
    ax.set_yticklabels(['Task 5 (P2)', 'Task 4 (P4)', 'Task 3 (P3)', 
                        'Task 2 (P2)', 'Task 1 (P1)'])
    ax.set_xlabel('Tempo (μs)', fontsize=12)
    ax.set_ylabel('Tarefa', fontsize=12)
    ax.set_title('Diagrama de Gantt - Escalonamento FreeRTOS', fontsize=14, fontweight='bold')
    ax.grid(True, alpha=0.3, axis='x')
    
    # Legenda
    legend_elements = [mpatches.Patch(color=COLORS[i], label=TASK_NAMES[i], alpha=0.8) 
                      for i in range(1, 6)]
    ax.legend(handles=legend_elements, loc='upper right', fontsize=10)
    
    # Adicionar anotação
    ax.text(0.02, 0.98, 'Preempções visíveis:\nTarefas de maior prioridade\ninterrompem as de menor prioridade', 
            transform=ax.transAxes, fontsize=9, verticalalignment='top',
            bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5))
    
    plt.tight_layout()
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    print(f"✓ Salvo: {output_file}")
    plt.close()

def calculate_statistics(executions):
    """Calcula estatísticas de execução"""
    stats = {}
    
    for task_id in range(1, 6):
        durations = [dur for _, dur in executions[task_id]]
        if durations:
            stats[task_id] = {
                'count': len(durations),
                'mean': np.mean(durations),
                'min': np.min(durations),
                'max': np.max(durations),
                'std': np.std(durations),
                'jitter': np.max(durations) - np.min(durations),
                'total_time': np.sum(durations)
            }
    
    return stats

def plot_cpu_usage(stats, df, output_file='cpu_usage.png'):
    """Cria gráfico de uso da CPU"""
    print("\n💻 Gerando gráfico de uso da CPU...")
    
    if not stats:
        print("⚠️  Nenhuma estatística disponível para plotar")
        return {}
    
    # Tempo total de simulação
    total_time = df['Timestamp_us'].max() - df['Timestamp_us'].min()
    
    # Calcular percentuais
    task_percentages = {}
    for task_id in range(1, 6):
        if task_id in stats:
            percentage = (stats[task_id]['total_time'] / total_time) * 100
            task_percentages[TASK_NAMES[task_id]] = percentage
    
    # CPU ociosa
    busy_time = sum(stats[tid]['total_time'] for tid in range(1, 6) if tid in stats)
    idle_percentage = ((total_time - busy_time) / total_time) * 100
    task_percentages['Idle'] = idle_percentage
    
    # Criar gráfico de pizza
    fig, ax = plt.subplots(figsize=(10, 8))
    
    colors_pie = [COLORS.get(i+1, '#95a5a6') for i in range(5)] + ['#bdc3c7']
    
    wedges, texts, autotexts = ax.pie(task_percentages.values(), 
                                       labels=task_percentages.keys(),
                                       autopct='%1.1f%%',
                                       startangle=90,
                                       colors=colors_pie,
                                       explode=[0.05]*len(task_percentages))
    
    for autotext in autotexts:
        autotext.set_color('white')
        autotext.set_fontsize(10)
        autotext.set_fontweight('bold')
    
    ax.set_title('Uso da CPU por Tarefa', fontsize=14, fontweight='bold')
    
    plt.tight_layout()
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    print(f"✓ Salvo: {output_file}")
    plt.close()
    
    return task_percentages

def plot_response_times(executions, output_file='response_times.png'):
    """Cria histogramas de tempos de resposta"""
    print("\n⏱️  Gerando histogramas de tempos de resposta...")
    
    fig, axes = plt.subplots(5, 1, figsize=(12, 14))
    
    for i, task_id in enumerate(range(1, 6)):
        durations_ms = [dur/1000 for _, dur in executions[task_id]]
        
        if durations_ms:
            axes[i].hist(durations_ms, bins=min(30, len(durations_ms)), 
                        color=COLORS[task_id], edgecolor='black', alpha=0.7)
            axes[i].set_title(f'{TASK_NAMES[task_id]} - Distribuição de Tempos', 
                            fontsize=12, fontweight='bold')
            axes[i].set_xlabel('Tempo de Execução (ms)')
            axes[i].set_ylabel('Frequência')
            axes[i].grid(True, alpha=0.3)
            
            # Estatísticas
            mean_val = np.mean(durations_ms)
            axes[i].axvline(mean_val, color='red', linestyle='--', linewidth=2, 
                          label=f'Média: {mean_val:.2f} ms')
            axes[i].legend()
        else:
            axes[i].text(0.5, 0.5, f'Sem dados para {TASK_NAMES[task_id]}',
                        ha='center', va='center', transform=axes[i].transAxes)
    
    plt.tight_layout()
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    print(f"✓ Salvo: {output_file}")
    plt.close()

def plot_jitter_comparison(stats, output_file='jitter_comparison.png'):
    """Compara jitter entre tarefas"""
    print("\n📉 Gerando gráfico de comparação de jitter...")
    
    if not stats:
        print("⚠️  Nenhuma estatística disponível")
        return
    
    fig, ax = plt.subplots(figsize=(10, 6))
    
    tasks = []
    jitters_ms = []
    colors = []
    
    for task_id in range(1, 6):
        if task_id in stats:
            tasks.append(TASK_NAMES[task_id])
            jitters_ms.append(stats[task_id]['jitter'] / 1000)
            colors.append(COLORS[task_id])
    
    if not tasks:
        print("⚠️  Nenhum dado para plotar")
        return
    
    bars = ax.bar(tasks, jitters_ms, color=colors, alpha=0.7, edgecolor='black')
    
    ax.set_ylabel('Jitter (ms)', fontsize=12)
    ax.set_title('Comparação de Jitter entre Tarefas', fontsize=14, fontweight='bold')
    ax.grid(True, alpha=0.3, axis='y')
    
    # Adicionar valores em cima das barras
    for bar, jitter in zip(bars, jitters_ms):
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2., height,
               f'{jitter:.2f} ms',
               ha='center', va='bottom', fontsize=10, fontweight='bold')
    
    plt.tight_layout()
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    print(f"✓ Salvo: {output_file}")
    plt.close()

def print_statistics_table(stats, cpu_usage):
    """Imprime tabela de estatísticas"""
    print("\n╔══════════════════════════════════════════════════════════════════════╗")
    print("║                    ESTATÍSTICAS DE EXECUÇÃO                           ║")
    print("╚══════════════════════════════════════════════════════════════════════╝\n")
    
    if not stats:
        print("⚠️  Nenhuma estatística disponível para exibir")
        return
    
    print("┌─────────────┬───────────┬──────────┬──────────┬──────────┬──────────┬─────────┐")
    print("│    Tarefa   │ Execuções │ Média(ms)│ Min (ms) │ Max (ms) │Jitter(ms)│CPU Usage│")
    print("├─────────────┼───────────┼──────────┼──────────┼──────────┼──────────┼─────────┤")
    
    for task_id in range(1, 6):
        if task_id in stats:
            s = stats[task_id]
            name = TASK_NAMES[task_id]
            cpu = cpu_usage.get(name, 0)
            
            print(f"│ {name:11} │   {s['count']:5}   │  {s['mean']/1000:6.2f}  │"
                  f"  {s['min']/1000:6.2f}  │  {s['max']/1000:6.2f}  │"
                  f"  {s['jitter']/1000:6.2f}  │  {cpu:5.1f}% │")
    
    print("└─────────────┴───────────┴──────────┴──────────┴──────────┴──────────┴─────────┘")

def plot_timeline(df, output_file='timeline.png'):
    """Plota timeline simples de eventos"""
    print("\n📅 Gerando timeline de eventos...")
    
    fig, ax = plt.subplots(figsize=(16, 6))
    
    for task_id in range(1, 6):
        task_events = df[df['Task'] == task_id]
        y_pos = 6 - task_id
        
        for _, row in task_events.iterrows():
            timestamp = row['Timestamp_us']
            event = row['Event']
            
            if event == 'S':
                marker = '^'
                size = 100
            else:
                marker = 'v'
                size = 100
            
            ax.scatter(timestamp, y_pos, color=COLORS[task_id], 
                      marker=marker, s=size, alpha=0.7, edgecolors='black')
    
    ax.set_yticks(range(1, 6))
    ax.set_yticklabels(['Task 5', 'Task 4', 'Task 3', 'Task 2', 'Task 1'])
    ax.set_xlabel('Tempo (μs)', fontsize=12)
    ax.set_ylabel('Tarefa', fontsize=12)
    ax.set_title('Timeline de Eventos (^ = Start, v = End)', fontsize=14, fontweight='bold')
    ax.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    print(f"✓ Salvo: {output_file}")
    plt.close()

def main():
    if len(sys.argv) < 2:
        print("Uso: python3 analyze_fixed.py events.csv")
        sys.exit(1)
    
    input_file = sys.argv[1]
    
    if not os.path.exists(input_file):
        print(f"❌ Erro: Arquivo {input_file} não encontrado!")
        sys.exit(1)
    
    print("╔══════════════════════════════════════════════════════════╗")
    print("║        ANÁLISE DE DADOS - PROJETO SOTR (FIXED)          ║")
    print("╚══════════════════════════════════════════════════════════╝")
    
    # Carregar dados
    df = load_data(input_file)
    
    # Plotar timeline de eventos
    plot_timeline(df)
    
    # Calcular execuções
    print("\n🔄 Processando eventos...")
    executions = calculate_executions(df)
    
    total_execs = sum(len(execs) for execs in executions.values())
    print(f"\n✓ Total: {total_execs} execuções completas processadas")
    
    if total_execs == 0:
        print("\n❌ PROBLEMA: Nenhuma execução completa encontrada!")
        print("\n💡 Possíveis causas:")
        print("   1. CSV só tem eventos 'S' (Start) sem 'E' (End)")
        print("   2. Simulação foi interrompida antes das tarefas terminarem")
        print("   3. Tempo de simulação muito curto (< 60 segundos)")
        print("\n🔧 Soluções:")
        print("   1. No Wokwi, deixe a simulação rodar por EXATOS 60 segundos")
        print("   2. Aguarde a mensagem 'COLETA DE DADOS CONCLUÍDA'")
        print("   3. Então copie o CSV completo do Serial Monitor")
        print("\n📊 Por enquanto, gerei um gráfico de timeline com os eventos disponíveis.")
        return
    
    # Calcular estatísticas
    stats = calculate_statistics(executions)
    
    # Gerar visualizações
    plot_gantt_chart(executions)
    cpu_usage = plot_cpu_usage(stats, df)
    plot_response_times(executions)
    plot_jitter_comparison(stats)
    
    # Imprimir estatísticas
    print_statistics_table(stats, cpu_usage)
    
    print("\n╔══════════════════════════════════════════════════════════╗")
    print("║              ANÁLISE CONCLUÍDA COM SUCESSO!             ║")
    print("╚══════════════════════════════════════════════════════════╝\n")
    
    print("📁 Arquivos gerados:")
    print("   • timeline.png (timeline de eventos)")
    if total_execs > 0:
        print("   • gantt_chart.png")
        print("   • cpu_usage.png")
        print("   • response_times.png")
        print("   • jitter_comparison.png")
    print("\n✅ Use esses gráficos no seu relatório!")

if __name__ == '__main__':
    main()