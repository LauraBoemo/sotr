# Guia Completo: Wokwi Simulator para ESP32

## 📖 Índice

1. [Introdução ao Wokwi](#introdução)
2. [Criando Conta](#criando-conta)
3. [Criando o Projeto](#criando-projeto)
4. [Configurando o Código](#configurando-código)
5. [Configurando o Circuito](#configurando-circuito)
6. [Executando a Simulação](#executando-simulação)
7. [Usando Serial Monitor](#serial-monitor)
8. [Recursos Avançados](#recursos-avançados)
9. [Dicas e Truques](#dicas-e-truques)
10. [Troubleshooting](#troubleshooting)

---

## 🎯 Introdução

**Wokwi** é um simulador online de microcontroladores que suporta:
- ESP32, Arduino, Raspberry Pi Pico, e mais
- Componentes eletrônicos virtuais
- FreeRTOS nativo no ESP32
- Debugging em tempo real
- Compartilhamento de projetos via link

### Por que Wokwi é Ideal para Este Projeto?

✅ **Sem Hardware Necessário** - Tudo roda no navegador  
✅ **Gratuito** - Recursos básicos são de graça  
✅ **FreeRTOS Nativo** - Suporte completo ao RTOS  
✅ **macOS Friendly** - Funciona perfeitamente no Mac  
✅ **Compartilhável** - Fácil demonstrar para o professor  
✅ **Serial Monitor** - Debug em tempo real  

---

## 🚀 Criando Conta

### Passo 1: Acessar o Site
```
https://wokwi.com
```

### Passo 2: Sign Up
1. Clique em **"Sign Up"** (canto superior direito)
2. Escolha uma opção:
   - **Google** (recomendado - mais rápido)
   - **GitHub**
   - **Email** (crie senha)

### Passo 3: Confirmar Email
- Se usou email, verifique inbox
- Clique no link de confirmação

### Passo 4: Login
- Faça login com suas credenciais
- Você verá o dashboard do Wokwi

---

## 📝 Criando o Projeto

### Método 1: Novo Projeto do Zero

1. **Clique em "New Project"**
2. **Escolha "ESP32"** na lista de templates
3. **Nomeie o projeto**: "SOTR_FreeRTOS_Escalonamento"
4. **Clique em "Create"**

### Método 2: Importar Projeto Compartilhado (se disponível)

1. Se você tiver um link de projeto Wokwi
2. Abra o link
3. Clique em **"Copy and Edit"**
4. O projeto será copiado para sua conta

---

## 💻 Configurando o Código

### Passo 1: Entender a Interface

Quando abrir seu projeto, você verá 4 áreas principais:

```
┌─────────────────────────────────────────────┐
│  [sketch.ino]  [diagram.json]  [wokwi.toml] │  ← Abas
├──────────────────┬──────────────────────────┤
│                  │                          │
│   CÓDIGO         │      DIAGRAMA            │
│   (editor)       │      (circuito)          │
│                  │                          │
├──────────────────┴──────────────────────────┤
│        [Start Simulation]  [Serial]         │  ← Controles
└─────────────────────────────────────────────┘
```

### Passo 2: Deletar Código Padrão

1. Clique na aba **"sketch.ino"**
2. Selecione todo o código (Cmd+A no Mac)
3. Delete

### Passo 3: Cola o Código do Projeto

Cole o código `esp32_freertos_wokwi.ino` que vou fornecer depois.

### Passo 4: Salvar

O Wokwi salva automaticamente, mas você pode forçar:
- **Cmd+S** (Mac)
- Ou espere o ícone de "Saving..." desaparecer

---

## 🔌 Configurando o Circuito

### Passo 1: Acessar diagram.json

1. Clique na aba **"diagram.json"**
2. Você verá um JSON com a configuração do circuito

### Passo 2: Entender o diagram.json

O arquivo diagram.json define:
- **parts**: Componentes (ESP32, LEDs, resistores)
- **connections**: Fios conectando componentes

### Passo 3: Configurar LEDs

Cole este diagram.json:

```json
{
  "version": 1,
  "author": "Projeto SOTR",
  "editor": "wokwi",
  "parts": [
    {
      "type": "wokwi-esp32-devkit-v1",
      "id": "esp",
      "top": 0,
      "left": 0,
      "attrs": {}
    },
    {
      "type": "wokwi-led",
      "id": "led1",
      "top": -60,
      "left": 250,
      "attrs": { "color": "red", "label": "Task 1" }
    },
    {
      "type": "wokwi-led",
      "id": "led2",
      "top": -20,
      "left": 250,
      "attrs": { "color": "green", "label": "Task 2" }
    },
    {
      "type": "wokwi-led",
      "id": "led3",
      "top": 20,
      "left": 250,
      "attrs": { "color": "blue", "label": "Task 3" }
    },
    {
      "type": "wokwi-led",
      "id": "led4",
      "top": 60,
      "left": 250,
      "attrs": { "color": "yellow", "label": "Task 4" }
    },
    {
      "type": "wokwi-led",
      "id": "led5",
      "top": 100,
      "left": 250,
      "attrs": { "color": "orange", "label": "Task 5" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r1",
      "top": -50,
      "left": 190,
      "attrs": { "value": "220" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r2",
      "top": -10,
      "left": 190,
      "attrs": { "value": "220" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r3",
      "top": 30,
      "left": 190,
      "attrs": { "value": "220" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r4",
      "top": 70,
      "left": 190,
      "attrs": { "value": "220" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r5",
      "top": 110,
      "left": 190,
      "attrs": { "value": "220" }
    }
  ],
  "connections": [
    [ "esp:TX0", "$serialMonitor:RX", "", [] ],
    [ "esp:RX0", "$serialMonitor:TX", "", [] ],
    [ "esp:D2", "r1:1", "green", [] ],
    [ "r1:2", "led1:A", "green", [] ],
    [ "led1:C", "esp:GND.1", "black", [] ],
    [ "esp:D4", "r2:1", "green", [] ],
    [ "r2:2", "led2:A", "green", [] ],
    [ "led2:C", "esp:GND.1", "black", [] ],
    [ "esp:D5", "r3:1", "green", [] ],
    [ "r3:2", "led3:A", "green", [] ],
    [ "led3:C", "esp:GND.1", "black", [] ],
    [ "esp:D18", "r4:1", "green", [] ],
    [ "r4:2", "led4:A", "green", [] ],
    [ "led4:C", "esp:GND.1", "black", [] ],
    [ "esp:D19", "r5:1", "green", [] ],
    [ "r5:2", "led5:A", "green", [] ],
    [ "led5:C", "esp:GND.1", "black", [] ]
  ],
  "dependencies": {}
}
```

### Passo 4: Visualizar Circuito

- Depois de colar o JSON, volte para aba "sketch.ino"
- Olhe a área do diagrama
- Você deve ver o ESP32 com 5 LEDs conectados!

### Mapa de Conexões:

| LED | Cor | Pino ESP32 | Tarefa |
|-----|-----|-----------|--------|
| LED1 | 🔴 Vermelho | D2 (GPIO2) | Task 1 |
| LED2 | 🟢 Verde | D4 (GPIO4) | Task 2 |
| LED3 | 🔵 Azul | D5 (GPIO5) | Task 3 |
| LED4 | 🟡 Amarelo | D18 (GPIO18) | Task 4 |
| LED5 | 🟠 Laranja | D19 (GPIO19) | Task 5 |

---

## ▶️ Executando a Simulação

### Passo 1: Iniciar Simulação

1. Clique no botão verde **"Start Simulation"**
2. Ou pressione **F1**

### Passo 2: O que Observar

Quando a simulação iniciar:
- ✅ LEDs começam a piscar
- ✅ Serial Monitor mostra logs
- ✅ ESP32 virtual "liga"

### Passo 3: Controles da Simulação

```
[⏸️ Pause]  - Pausar simulação
[⏹️ Stop]   - Parar e resetar
[⏩ Speed]  - Ajustar velocidade (1x, 2x, 4x)
```

### Passo 4: Pausar e Inspecionar

Você pode pausar a simulação para:
- Inspecionar valores de variáveis
- Ver estado dos pinos
- Analisar código linha por linha (debugging)

---

## 📟 Usando Serial Monitor

### Passo 1: Abrir Serial Monitor

1. Clique no ícone **"Serial Monitor"** (parte inferior da tela)
2. Ou clique em "Serial" na barra de ferramentas

### Passo 2: Configurar Baud Rate

- Geralmente já vem configurado em 115200
- Se precisar mudar: clique na engrenagem ⚙️ e ajuste

### Passo 3: Ver Logs

Você verá logs como:
```
========================================
Sistema Operacional de Tempo Real
Demonstração FreeRTOS + ESP32
========================================

[T1] Iniciando execução #1 @ 1000ms
  [T2] Iniciando execução #1 @ 500ms
    [T3] Iniciando execução #1 @ 300ms
      [T4] Iniciando execução #1 @ 200ms
...
```

### Passo 4: Copiar Logs

1. Clique com botão direito no Serial Monitor
2. **"Copy All"** - copia tudo
3. Cole em arquivo de texto para análise

### Passo 5: Limpar Serial Monitor

- Clique no ícone da lixeira 🗑️ para limpar

---

## 🔬 Recursos Avançados

### 1. Debugging

#### Breakpoints:
1. Clique à esquerda do número da linha no código
2. Aparece um ponto vermelho
3. Simulação pausa quando chegar lá

#### Inspecionar Variáveis:
- Passe mouse sobre variável
- Veja valor em tempo real

#### Step Through:
- **F10**: Próxima linha (step over)
- **F11**: Entrar em função (step into)
- **Shift+F11**: Sair de função (step out)

### 2. Visualizar Pins

1. Clique em qualquer pino do ESP32
2. Veja estado (HIGH/LOW)
3. Veja voltagem

### 3. Adicionar Componentes Extras

Arraste componentes da biblioteca:
- Botões
- Sensores
- Displays
- E mais!

### 4. Compartilhar Projeto

1. Clique em **"Share"** (canto superior direito)
2. Copie o link
3. Qualquer um com link pode ver e copiar

**Exemplo de link:**
```
https://wokwi.com/projects/123456789012345678
```

### 5. Salvar Screenshots

1. Clique em **"Screenshot"**
2. Ou **Cmd+Shift+3** (Mac) para screenshot manual
3. Use para documentação!

---

## 💡 Dicas e Truques

### 1. Atalhos de Teclado (macOS)

| Ação | Atalho |
|------|--------|
| Iniciar/Parar Simulação | F1 |
| Salvar | Cmd+S |
| Buscar no código | Cmd+F |
| Comentar linha | Cmd+/ |
| Duplicar linha | Cmd+D |
| Abrir Serial Monitor | Ctrl+Shift+M |

### 2. Performance

**Simulação Lenta?**
- Feche outras abas do navegador
- Reduza velocidade para 1x
- Use Chrome (mais rápido que Safari/Firefox)

### 3. Simulação Determinística

- Wokwi é determinística
- Mesmos inputs = mesmos outputs
- Ótimo para debugging reproduzível

### 4. Logs Detalhados

Adicione mais prints para debug:
```cpp
Serial.printf("[DEBUG] Variável x = %d\n", x);
```

### 5. Cores no Serial Monitor

Wokwi suporta cores ANSI:
```cpp
Serial.println("\033[31mErro!\033[0m");  // Vermelho
Serial.println("\033[32mOK!\033[0m");     // Verde
```

---

## 🐛 Troubleshooting

### Problema 1: "Compilation Error"

**Sintomas:**
```
Error: 'xTaskCreate' was not declared in this scope
```

**Solução:**
- Certifique-se de ter `#include <Arduino.h>` no topo
- FreeRTOS já está incluído automaticamente no ESP32

---

### Problema 2: Serial Monitor Vazio

**Soluções:**
1. Verifique `Serial.begin(115200)` no setup()
2. Confirme conexão TX0/RX0 no diagram.json
3. Limpe e reinicie simulação

---

### Problema 3: LEDs Não Acendem

**Checklist:**
- [ ] Pinos corretos no código (D2, D4, D5, D18, D19)
- [ ] `pinMode()` configurado como OUTPUT
- [ ] Resistores conectados
- [ ] GND conectado

---

### Problema 4: Simulação Muito Lenta

**Soluções:**
- Reduza frequência de prints no Serial
- Use menos componentes
- Feche outras abas do navegador
- Tente navegador diferente (Chrome recomendado)

---

### Problema 5: "Stack Overflow" no ESP32

**Sintomas:**
```
***ERROR*** A stack overflow in task Task1 has been detected.
```

**Solução:**
Aumente stack size na criação da tarefa:
```cpp
xTaskCreate(Task1, "Task1", 4096, ...);  // Era 2048
                              ^^^^
```

---

### Problema 6: Projeto Não Salva

**Soluções:**
- Certifique-se de estar logado
- Verifique conexão internet
- Tente forçar save (Cmd+S)
- Copie código para arquivo local (backup!)

---

## 📊 Capturando Dados para Análise

### 1. Screenshots

**Do Circuito:**
1. Pause a simulação
2. Clique em "Screenshot"
3. Salve a imagem

**Do Serial Monitor:**
1. Copie texto
2. Cole em arquivo .txt
3. Ou tire screenshot da tela

### 2. Vídeo da Simulação

**macOS:**
1. **QuickTime Player** → File → New Screen Recording
2. Selecione área do Wokwi
3. Grave 30-60 segundos
4. Salve como .mov

**Ou use OBS:**
- Software gratuito de gravação de tela
- Mais recursos de edição

### 3. Dados Temporais

Copie logs do Serial e analise em Excel/Python:
```
Timestamp,Tarefa,Evento
1000,Task1,START
1010,Task1,END
500,Task2,START
530,Task2,END
...
```

---

## 🎓 Usando Wokwi na Apresentação

### Setup Ideal:

1. **Abra 2 Abas:**
   - Aba 1: Código (sketch.ino)
   - Aba 2: Diagrama + Serial

2. **Prepare Demonstração:**
   - Resete simulação
   - Posicione janelas
   - Teste antes!

3. **Durante Apresentação:**
   - Mostre código brevemente
   - Foque em diagrama + Serial
   - Aponte preempções nos logs

---

## 📚 Recursos Extras

### Documentação Oficial:
- https://docs.wokwi.com

### Tutoriais:
- https://docs.wokwi.com/guides/esp32

### Comunidade:
- Discord: https://wokwi.com/discord
- Forum: https://forum.wokwi.com

### Exemplos:
- https://wokwi.com/projects

---

## ✅ Checklist Final Wokwi

Antes da apresentação:

- [ ] Projeto salvo e funcionando
- [ ] Link compartilhável copiado
- [ ] Screenshots do circuito salvos
- [ ] Logs do Serial copiados
- [ ] Vídeo da simulação gravado (opcional)
- [ ] Backup local do código
- [ ] Testado em apresentação simulada

---

**Próximo Passo:** Leia GUIA_SEGGER_SYSTEMVIEW.md para aprender a capturar e analisar traces profissionais!

---

**Wokwi é uma ferramenta PROFISSIONAL** - empresas usam para prototipação rápida! 🚀
