# Relatório Descritivo Curto

Este projeto demonstra um sistema de monitoração e controle em tempo real usando **ESP32 + FreeRTOS** executado no simulador **Wokwi**. A implementação prioriza o escalonamento preemptivo, a coleta de dados de execução e a análise temporal.

## O que foi feito
- **Configuração de tarefas periódicas** com diferentes prioridades e períodos (1000 ms a 200 ms), simulando cargas de CPU para observar preempções.
- **Instrumentação de tempo real**: cada tarefa registra eventos de início/fim em microsegundos e mantém estatísticas (média, mínimo, máximo e jitter) durante a execução.
- **Monitoramento contínuo**: uma tarefa de monitor imprime periodicamente o uso de CPU/heap e estatísticas de cada tarefa; ao final do período de coleta, gera um log CSV para análise externa.
- **Análise temporal offline** com `analyze.py`, que calcula tempos de execução, jitter, uso de CPU e gráficos (Gantt, histogramas e timeline) a partir do CSV coletado.

## Como funciona
1. No `setup()`, o ESP32 configura GPIOs para LEDs das tarefas, inicializa estatísticas e cria as cinco tarefas + monitor.
2. Cada tarefa executa uma carga de trabalho definida por período/prioridade; tarefas de maior prioridade podem **preemptar** as de menor prioridade, evidenciando escalonamento preemptivo do FreeRTOS.
3. A função `logEvent` grava cada início/fim (`S`/`E`) no buffer `events`, permitindo reconstruir a linha do tempo em microsegundos.
4. A **tarefa de monitoramento** (`MonitorTask`) imprime estatísticas a cada 10s e, após 60s, desativa o log, imprime o CSV e sinaliza o fim da coleta.
5. O CSV copiado do Serial Monitor é processado com `python3 analyze.py wokwi/events.csv`, produzindo gráficos e tabela de desempenho para o relatório de tempo real.

## Como executar
1. Abrir o projeto no Wokwi e iniciar a simulação por **60 segundos completos** até a mensagem "COLETA DE DADOS CONCLUÍDA".
2. Copiar o bloco CSV do Serial Monitor para `wokwi/events.csv` no repositório.
3. Rodar `python3 analyze.py wokwi/events.csv` para gerar gráficos e tabelas.

## Evidências de análise temporal
- **Tempo de resposta e jitter** são calculados por tarefa com base na diferença entre eventos de início/fim e apresentados tanto no monitor serial quanto nas figuras geradas pelo script de análise.
- **Uso de CPU** é estimado pela soma dos tempos de execução de cada tarefa, permitindo discutir margem temporal e prioridades.

Este fluxo atende aos requisitos de um projeto de Sistemas Operacionais de Tempo Real ao combinar execução preemptiva, coleta de dados temporais e análise quantitativa do comportamento das tarefas.
