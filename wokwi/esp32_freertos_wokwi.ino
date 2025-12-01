// ========================================
// INCLUDES
// ========================================
#include <Arduino.h>

// ========================================
// CONFIGURAÇÕES
// ========================================

// LEDs (pinos do Wokwi)
#define LED_TASK1 2   // Vermelho
#define LED_TASK2 4   // Verde
#define LED_TASK3 5   // Azul
#define LED_TASK4 18  // Amarelo
#define LED_TASK5 19  // Laranja

// Debug e Logging
#define DEBUG_SERIAL true
#define SERIAL_BAUD 115200
#define LOG_EVENTS true

// Tempo de execução para coleta de dados (segundos)
#define RUN_TIME_SEC 60

// ========================================
// ESTRUTURA DE EVENTOS (para análise)
// ========================================
#if LOG_EVENTS
struct EventLog {
  uint32_t timestamp_us;
  uint8_t task_id;
  char event_type;  // 'S' = Start, 'E' = End, 'P' = Preempted
};

const int MAX_EVENTS = 5000;
EventLog events[MAX_EVENTS];
int event_count = 0;
bool logging_enabled = true;

void logEvent(uint8_t task_id, char event_type) {
  if (logging_enabled && event_count < MAX_EVENTS) {
    events[event_count].timestamp_us = micros();
    events[event_count].task_id = task_id;
    events[event_count].event_type = event_type;
    event_count++;
  }
}
#else
void logEvent(uint8_t task_id, char event_type) {}  // No-op
#endif

// ========================================
// HANDLES DAS TAREFAS
// ========================================
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;
TaskHandle_t Task3Handle = NULL;
TaskHandle_t Task4Handle = NULL;
TaskHandle_t Task5Handle = NULL;

// ========================================
// ESTATÍSTICAS
// ========================================
struct TaskStats {
  uint32_t executions;
  uint32_t total_time_us;
  uint32_t min_time_us;
  uint32_t max_time_us;
};

TaskStats stats[6];  // 0 = não usado, 1-5 = tasks

// ========================================
// PROTÓTIPOS
// ========================================
void Task1(void *pvParameters);
void Task2(void *pvParameters);
void Task3(void *pvParameters);
void Task4(void *pvParameters);
void Task5(void *pvParameters);
void MonitorTask(void *pvParameters);
void updateStats(uint8_t task_id, uint32_t execution_time_us);
void printStatistics();
void printEventLog();
void simulateWork(uint32_t durationMs);

// ========================================
// SETUP
// ========================================
void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  
  Serial.println(F("\n\n╔══════════════════════════════════════════════════════════╗"));
  Serial.println(F("║       PROJETO SOTR - ESP32 + FreeRTOS + Wokwi          ║"));
  Serial.println(F("║       Demonstração de Escalonamento Preemptivo         ║"));
  Serial.println(F("╚══════════════════════════════════════════════════════════╝\n"));
  
  // Inicializar estatísticas
  for (int i = 1; i <= 5; i++) {
    stats[i].executions = 0;
    stats[i].total_time_us = 0;
    stats[i].min_time_us = UINT32_MAX;
    stats[i].max_time_us = 0;
  }
  
  // Configurar GPIOs
  pinMode(LED_TASK1, OUTPUT);
  pinMode(LED_TASK2, OUTPUT);
  pinMode(LED_TASK3, OUTPUT);
  pinMode(LED_TASK4, OUTPUT);
  pinMode(LED_TASK5, OUTPUT);
  
  Serial.println(F("✓ GPIOs configurados"));
  
  // Informações do sistema
  Serial.println(F("\n─── Informações do Sistema ───"));
  Serial.printf("CPU Frequency: %d MHz\n", getCpuFrequencyMhz());
  Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("Tempo de Coleta: %d segundos\n", RUN_TIME_SEC);
  
  Serial.println(F("\n─── Configuração das Tarefas ───"));
  Serial.println(F("┌──────┬────────────┬──────────┬──────────────┬─────┐"));
  Serial.println(F("│ Task │ Prioridade │ Período  │ Exec. Tempo  │ LED │"));
  Serial.println(F("├──────┼────────────┼──────────┼──────────────┼─────┤"));
  Serial.println(F("│  T1  │  1 (Baixa) │ 1000ms   │    ~50ms     │ 🔴  │"));
  Serial.println(F("│  T2  │  2 (Média) │  500ms   │    ~30ms     │ 🟢  │"));
  Serial.println(F("│  T3  │  3 (Alta)  │  300ms   │    ~20ms     │ 🔵  │"));
  Serial.println(F("│  T4  │ 4 (Crítica)│  200ms   │    ~10ms     │ 🟡  │"));
  Serial.println(F("│  T5  │  2 (Média) │  700ms   │  25-35ms(var)│ 🟠  │"));
  Serial.println(F("└──────┴────────────┴──────────┴──────────────┴─────┘\n"));
  
  // Criar tarefas
  Serial.println(F("─── Criando Tarefas ───"));
  
  xTaskCreatePinnedToCore(Task1, "Task1_P1", 3072, NULL, 1, &Task1Handle, 0);
  Serial.println(F("✓ Task 1 criada"));
  
  xTaskCreatePinnedToCore(Task2, "Task2_P2", 3072, NULL, 2, &Task2Handle, 0);
  Serial.println(F("✓ Task 2 criada"));
  
  xTaskCreatePinnedToCore(Task3, "Task3_P3", 3072, NULL, 3, &Task3Handle, 0);
  Serial.println(F("✓ Task 3 criada"));
  
  xTaskCreatePinnedToCore(Task4, "Task4_P4", 3072, NULL, 4, &Task4Handle, 0);
  Serial.println(F("✓ Task 4 criada"));
  
  xTaskCreatePinnedToCore(Task5, "Task5_P2", 3072, NULL, 2, &Task5Handle, 0);
  Serial.println(F("✓ Task 5 criada"));
  
  // Criar tarefa de monitoramento
  xTaskCreatePinnedToCore(MonitorTask, "Monitor", 4096, NULL, 0, NULL, 0);
  Serial.println(F("✓ Monitor criado"));
  
  Serial.println(F("\n╔══════════════════════════════════════════════════════════╗"));
  Serial.println(F("║              SISTEMA INICIADO COM SUCESSO               ║"));
  Serial.println(F("║         Monitorando execução das tarefas...            ║"));
  Serial.println(F("╚══════════════════════════════════════════════════════════╝\n"));
  
  #if LOG_EVENTS
  Serial.println(F("📊 Logging de eventos HABILITADO (CSV será gerado)\n"));
  #endif
  
  Serial.println(F("Legenda: [T1][T2][T3][T4][T5] | Timestamps em μs\n"));
}

// ========================================
// LOOP (não usado com FreeRTOS)
// ========================================
void loop() {
  vTaskDelay(portMAX_DELAY);
}

// ========================================
// TAREFAS
// ========================================

/**
 * Task 1 - Prioridade 1 (BAIXA)
 * Período: 1000ms | Execução: ~50ms
 */
void Task1(void *pvParameters) {
  const TickType_t xFrequency = pdMS_TO_TICKS(1000);
  TickType_t xLastWakeTime = xTaskGetTickCount();
  
  for(;;) {
    uint32_t start_us = micros();
    
    logEvent(1, 'S');  // START
    digitalWrite(LED_TASK1, HIGH);
    
    if (DEBUG_SERIAL) {
      Serial.printf("[T1] START | #%lu | %lu μs\n", 
                    stats[1].executions + 1, start_us);
    }
    
    // Simular trabalho (~50ms)
    simulateWork(50);
    
    uint32_t end_us = micros();
    uint32_t exec_time = end_us - start_us;
    
    digitalWrite(LED_TASK1, LOW);
    logEvent(1, 'E');  // END
    
    updateStats(1, exec_time);
    
    if (DEBUG_SERIAL) {
      Serial.printf("[T1] END   | Exec: %.2f ms | Jitter: %+.2f ms\n", 
                    exec_time / 1000.0,
                    (int32_t)(exec_time - 50000) / 1000.0);
    }
    
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/**
 * Task 2 - Prioridade 2 (MÉDIA)
 * Período: 500ms | Execução: ~30ms
 */
void Task2(void *pvParameters) {
  const TickType_t xFrequency = pdMS_TO_TICKS(500);
  TickType_t xLastWakeTime = xTaskGetTickCount();
  
  for(;;) {
    uint32_t start_us = micros();
    
    logEvent(2, 'S');
    digitalWrite(LED_TASK2, HIGH);
    
    if (DEBUG_SERIAL) {
      Serial.printf("  [T2] START | #%lu | %lu μs\n", 
                    stats[2].executions + 1, start_us);
    }
    
    simulateWork(30);
    
    uint32_t end_us = micros();
    uint32_t exec_time = end_us - start_us;
    
    digitalWrite(LED_TASK2, LOW);
    logEvent(2, 'E');
    
    updateStats(2, exec_time);
    
    if (DEBUG_SERIAL) {
      Serial.printf("  [T2] END   | Exec: %.2f ms | Jitter: %+.2f ms\n", 
                    exec_time / 1000.0,
                    (int32_t)(exec_time - 30000) / 1000.0);
    }
    
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/**
 * Task 3 - Prioridade 3 (ALTA)
 * Período: 300ms | Execução: ~20ms
 */
void Task3(void *pvParameters) {
  const TickType_t xFrequency = pdMS_TO_TICKS(300);
  TickType_t xLastWakeTime = xTaskGetTickCount();
  
  for(;;) {
    uint32_t start_us = micros();
    
    logEvent(3, 'S');
    digitalWrite(LED_TASK3, HIGH);
    
    if (DEBUG_SERIAL) {
      Serial.printf("    [T3] START | #%lu | %lu μs\n", 
                    stats[3].executions + 1, start_us);
    }
    
    simulateWork(20);
    
    uint32_t end_us = micros();
    uint32_t exec_time = end_us - start_us;
    
    digitalWrite(LED_TASK3, LOW);
    logEvent(3, 'E');
    
    updateStats(3, exec_time);
    
    if (DEBUG_SERIAL) {
      Serial.printf("    [T3] END   | Exec: %.2f ms | Jitter: %+.2f ms\n", 
                    exec_time / 1000.0,
                    (int32_t)(exec_time - 20000) / 1000.0);
    }
    
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/**
 * Task 4 - Prioridade 4 (CRÍTICA)
 * Período: 200ms | Execução: ~10ms
 */
void Task4(void *pvParameters) {
  const TickType_t xFrequency = pdMS_TO_TICKS(200);
  TickType_t xLastWakeTime = xTaskGetTickCount();
  
  for(;;) {
    uint32_t start_us = micros();
    
    logEvent(4, 'S');
    digitalWrite(LED_TASK4, HIGH);
    
    if (DEBUG_SERIAL) {
      Serial.printf("      [T4] START | #%lu | %lu μs ⚡ CRITICAL\n", 
                    stats[4].executions + 1, start_us);
    }
    
    simulateWork(10);
    
    uint32_t end_us = micros();
    uint32_t exec_time = end_us - start_us;
    
    digitalWrite(LED_TASK4, LOW);
    logEvent(4, 'E');
    
    updateStats(4, exec_time);
    
    if (DEBUG_SERIAL) {
      Serial.printf("      [T4] END   | Exec: %.2f ms | Jitter: %+.2f ms\n", 
                    exec_time / 1000.0,
                    (int32_t)(exec_time - 10000) / 1000.0);
    }
    
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/**
 * Task 5 - Prioridade 2 (MÉDIA) - VARIÁVEL
 * Período: 700ms | Execução: 25-35ms (variável)
 */
void Task5(void *pvParameters) {
  const TickType_t xFrequency = pdMS_TO_TICKS(700);
  TickType_t xLastWakeTime = xTaskGetTickCount();
  
  for(;;) {
    uint32_t start_us = micros();
    
    // Tempo variável para demonstrar jitter
    uint32_t work_time = 25 + ((stats[5].executions % 10) + 1);
    
    logEvent(5, 'S');
    digitalWrite(LED_TASK5, HIGH);
    
    if (DEBUG_SERIAL) {
      Serial.printf("  [T5] START | #%lu | %lu μs | Work: %lu ms\n", 
                    stats[5].executions + 1, start_us, work_time);
    }
    
    simulateWork(work_time);
    
    uint32_t end_us = micros();
    uint32_t exec_time = end_us - start_us;
    
    digitalWrite(LED_TASK5, LOW);
    logEvent(5, 'E');
    
    updateStats(5, exec_time);
    
    if (DEBUG_SERIAL) {
      Serial.printf("  [T5] END   | Exec: %.2f ms | Jitter: %+.2f ms 🔀 VARIABLE\n", 
                    exec_time / 1000.0,
                    (int32_t)(exec_time - (work_time * 1000)) / 1000.0);
    }
    
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

/**
 * Monitor Task - Imprime estatísticas periodicamente
 * Prioridade: 0 (mais baixa)
 */
void MonitorTask(void *pvParameters) {
  uint32_t start_time = millis();
  bool final_stats_printed = false;
  
  for(;;) {
    uint32_t elapsed_sec = (millis() - start_time) / 1000;
    
    // A cada 10 segundos, imprimir estatísticas
    if (elapsed_sec > 0 && elapsed_sec % 10 == 0) {
      vTaskDelay(pdMS_TO_TICKS(1000));  // Evitar múltiplas impressões
      printStatistics();
    }
    
    // Após RUN_TIME_SEC, desabilitar logging e imprimir CSV
    if (elapsed_sec >= RUN_TIME_SEC && !final_stats_printed) {
      logging_enabled = false;
      
      Serial.println(F("\n\n╔══════════════════════════════════════════════════════════╗"));
      Serial.println(F("║           COLETA DE DADOS CONCLUÍDA                     ║"));
      Serial.println(F("╚══════════════════════════════════════════════════════════╝\n"));
      
      printStatistics();
      
      #if LOG_EVENTS
      printEventLog();
      #endif
      
      final_stats_printed = true;
      
      Serial.println(F("\n📊 Copie o CSV acima para análise no Python/Excel\n"));
    }
    
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// ========================================
// FUNÇÕES AUXILIARES
// ========================================

void simulateWork(uint32_t durationMs) {
  uint32_t start = millis();
  volatile uint32_t counter = 0;
  
  while (millis() - start < durationMs) {
    counter++;
    if (counter % 1000 == 0) {
      asm volatile ("nop");
    }
  }
}

void updateStats(uint8_t task_id, uint32_t execution_time_us) {
  stats[task_id].executions++;
  stats[task_id].total_time_us += execution_time_us;
  
  if (execution_time_us < stats[task_id].min_time_us) {
    stats[task_id].min_time_us = execution_time_us;
  }
  
  if (execution_time_us > stats[task_id].max_time_us) {
    stats[task_id].max_time_us = execution_time_us;
  }
}

void printStatistics() {
  Serial.println(F("\n╔══════════════════════════════════════════════════════════════╗"));
  Serial.println(F("║                  ESTATÍSTICAS DO SISTEMA                     ║"));
  Serial.println(F("╚══════════════════════════════════════════════════════════════╝"));
  
  Serial.printf("\nUptime: %.1f segundos | Free Heap: %d bytes\n\n", 
                millis() / 1000.0, ESP.getFreeHeap());
  
  Serial.println(F("┌──────┬───────────┬──────────┬──────────┬──────────┬─────────┐"));
  Serial.println(F("│ Task │ Execuções │ Média(ms)│ Min (ms) │ Max (ms) │Jitter(ms)│"));
  Serial.println(F("├──────┼───────────┼──────────┼──────────┼──────────┼──────────┤"));
  
  for (int i = 1; i <= 5; i++) {
    if (stats[i].executions > 0) {
      float avg = stats[i].total_time_us / stats[i].executions / 1000.0;
      float min_time = stats[i].min_time_us / 1000.0;
      float max_time = stats[i].max_time_us / 1000.0;
      float jitter = max_time - min_time;
      
      Serial.printf("│  T%d  │   %5lu   │  %6.2f  │  %6.2f  │  %6.2f  │  %6.2f  │\n",
                    i, stats[i].executions, avg, min_time, max_time, jitter);
    }
  }
  
  Serial.println(F("└──────┴───────────┴──────────┴──────────┴──────────┴──────────┘\n"));
}

#if LOG_EVENTS
void printEventLog() {
  Serial.println(F("\n╔══════════════════════════════════════════════════════════════╗"));
  Serial.println(F("║                   EVENT LOG (CSV FORMAT)                     ║"));
  Serial.println(F("╚══════════════════════════════════════════════════════════════╝\n"));
  
  Serial.println(F("Timestamp_us,Task,Event"));
  
  for (int i = 0; i < event_count; i++) {
    Serial.print(events[i].timestamp_us);
    Serial.print(",");
    Serial.print(events[i].task_id);
    Serial.print(",");
    Serial.println(events[i].event_type);
  }
  
  Serial.printf("\n✓ Total de %d eventos registrados\n", event_count);
}
#endif
