# Relatório do Sistema: ESP32 c/ FreeRTOS Simulado em Wokwi e Analisado em Python

## 1. Dados Gerais

- **Nome**: Laura Righi Boemo
- **Disciplina**: Sistemas Operacionais & Tempo Real
- **Semestre**: 2025/2

## 2. Objetivo Deste Trabalho 

### 2.1. Objetivos Gerais

Desenvolver a [_Possibilidade 3_](https://ead06.proj.ufsm.br/pluginfile.php/5435249/mod_resource/content/4/descri%C3%A7%C3%A3o%20do%20projeto%20semestral.pdf), cujos requisitos eram:

1. Projeto monitoração/controle tempo real;
2. Hardware e software a escolha do grupo;
3. Análise temporal de resposta do sistema.

### 2.2. Objetivo Específico

Desenvolver um sistema de monitoração e controle em tempo real usando **ESP32** com **FreeRTOS** nativo enquanto executado no simulador **Wokwi** com indução de escalonamento preemptivo e coleta de dados de execução cuja análise temporal de resposta do sistema é feita via **Python**.

## 3. Detalhes Do Sistema

### 3.1. FreeRTOS & ESP32

No arquivo `esp32_freertos_wokwi.ino`, compilado pelo **ESP32** no simulador **Wokwi**, é possível conferir a **configuração de tarefas periódicas**. Cinco tarefas apresentam diferentes prioridades (Baixa, Média, Alta e Crítica) e períodos (1000 ms a 200 ms), a fim de simular cargas de CPU para observar preempções, por meio das funções nativas de **FreeRTOS** (como xTaskCreatePinnedToCore, vTaskDelay ou pdMS_TO_TICKS).

Uma vez que o código é executado no simulador, é possível conferir sua execução por meio dos leds simulados (gerados em `diagram.json`). Além disso, em seu console há a **instrumentação de tempo real**, onde cada tarefa registra eventos de início/fim em microsegundos e mantém estatísticas (média, mínimo, máximo e jitter) durante a execução. Assim, uma função de monitor imprime periodicamente o uso de CPU/heap e estatísticas de cada tarefa; ao final do período de coleta, gera um log CSV para análise externa (`events.csv`).

### 3.2. Python & Análise

Uma vez que os dados gerados pelo simulador estejam recolhidos em `events.csv`, é posssível executar o código de **análise temporal offline** com `analyze.py`. Dessa forma, são calculados tempos de execução, jitter, uso de CPU e gráficos (Gantt, histogramas e timeline) a partir do CSV coletado.

## 4. Funcionamento Geral
1. No `setup()`, o ESP32 configura GPIOs para LEDs das tarefas, inicializa estatísticas e cria as cinco tarefas + monitor.
2. Cada tarefa executa uma carga de trabalho definida por período/prioridade; tarefas de maior prioridade podem **preemptar** as de menor prioridade, evidenciando escalonamento preemptivo do FreeRTOS.
3. A função `logEvent` grava cada início/fim (`S`/`E`) no buffer `events`, permitindo reconstruir a linha do tempo em microsegundos.
4. A **tarefa de monitoramento** (`MonitorTask`) imprime estatísticas a cada 10s e, após 60s, desativa o log, imprime o CSV e sinaliza o fim da coleta.
5. O CSV copiado do Serial Monitor é processado com `python3 analyze.py wokwi/events.csv`, produzindo gráficos e tabela de desempenho para o relatório de tempo real.

## 5. Avaliação dos Resultados

## 6. Bônus: Como executar
1. Abrir o [projeto no Wokwi](https://wokwi.com/projects/449086123858100225) e iniciar a simulação por **60 segundos completos** até a mensagem "COLETA DE DADOS CONCLUÍDA".
2. Copiar o bloco CSV do Serial Monitor para `wokwi/events.csv` no repositório.
3. Rodar `python3 analyze.py wokwi/events.csv` para gerar gráficos e tabelas.