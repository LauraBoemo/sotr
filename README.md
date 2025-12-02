# Relatório Descritivo Curto

## Dados Gerais

- **Nome**: Laura Righi Boemo
- **Cadeira**: Sistemas Operacionais & Tempo Real
- **Semestre**: 2025/2

## Objetivo Deste Trabalho 

- **Objetivos Gerais**: Realizar a [_Possibilidade 3_](https://ead06.proj.ufsm.br/pluginfile.php/5435249/mod_resource/content/4/descri%C3%A7%C3%A3o%20do%20projeto%20semestral.pdf) sugerida para o _Trabalho Semestral_ da cadeira _Sistemas Operacionais & Tempo Real_. Cujos requisitos eram:

1. Projeto monitoração/controle tempo real com
auxílio computacional;
2. Hardware e software a escolha do grupo;
3. Análise temporal de resposta do sistema deve ser
abordada.

- **Objetivos Específicos**: Este projeto demonstra um sistema de monitoração e controle em tempo real usando **ESP32** executado no simulador **Wokwi**, com:

1. Indução do escalonamento preemptivo;
2. Realização da coleta de dados de execução;
3. Analisando seus tempos de resposta com Python.

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