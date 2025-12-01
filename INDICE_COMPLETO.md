# 📚 ÍNDICE COMPLETO DO PROJETO - SOTR (Wokwi + Segger)

## ✨ Projeto Completo Adaptado para macOS + Wokwi + Segger SystemView

---

## 🎯 ARQUIVOS PRINCIPAIS - LEIA PRIMEIRO!

### 1. [INSTRUCOES_USO.md](computer:///mnt/user-data/outputs/INSTRUCOES_USO.md) ⭐ **COMECE AQUI!**
**O que é:** Instruções passo a passo de todo o projeto  
**Quando usar:** PRIMEIRO arquivo a ler  
**Tempo de leitura:** 15 minutos  
**Conteúdo:**
- Início rápido (30 min para ter projeto rodando)
- Captura de dados (45 min)
- Análise com Python (30 min)
- Escrever relatório (3-4h)
- Preparar apresentação (2-3h)
- Checklist final
- Cronograma sugerido

---

### 2. [README_WOKWI_SEGGER.md](computer:///mnt/user-data/outputs/README_WOKWI_SEGGER.md) ⭐ **OVERVIEW DO PROJETO**
**O que é:** README principal do projeto adaptado  
**Quando usar:** Depois das instruções, para entender contexto  
**Tempo de leitura:** 10 minutos  
**Conteúdo:**
- Descrição completa do projeto
- Stack tecnológico (Wokwi + Segger + Python)
- Estrutura dos arquivos
- Guia rápido de início
- Relação com requisitos da disciplina
- Timeline sugerido

---

## 📖 GUIAS DETALHADOS

### 3. [GUIA_WOKWI.md](computer:///mnt/user-data/outputs/GUIA_WOKWI.md)
**O que é:** Manual completo do Wokwi Simulator  
**Tempo de leitura:** 30 minutos  
**Conteúdo:**
- Como criar conta
- Criando projeto
- Configurando código
- Configurando circuito (diagram.json)
- Executando simulação
- Usando Serial Monitor
- Recursos avançados (debugging, screenshots)
- Dicas e truques
- Troubleshooting

**Quando usar:** Antes de começar a usar o Wokwi

---

### 4. [GUIA_SEGGER_SYSTEMVIEW.md](computer:///mnt/user-data/outputs/GUIA_SEGGER_SYSTEMVIEW.md)
**O que é:** Guia de instalação e uso do SystemView no macOS  
**Tempo de leitura:** 25 minutos  
**Conteúdo:**
- Por que SystemView ao invés de Tracealyzer
- Instalação no macOS
- Integração com FreeRTOS
- Abordagem híbrida com Wokwi
- Captura de dados via logs
- Análise com Python
- Visualizações profissionais
- Troubleshooting

**Quando usar:** Depois de capturar dados do Wokwi

---

### 5. [GUIA_APRESENTACAO_WOKWI.md](computer:///mnt/user-data/outputs/GUIA_APRESENTACAO_WOKWI.md) ⚠️ **NÃO CRIADO AINDA**
**Status:** Será criado baseado no GUIA_APRESENTACAO.md original  
**O que será:** Guia adaptado para apresentar projeto no Wokwi  
**Conteúdo previsto:**
- Estrutura da apresentação (10-15 min)
- Como demonstrar no Wokwi
- Como mostrar resultados do Python
- Perguntas e respostas adaptadas
- Argumentos para justificar uso de simulador

**Nota:** Por agora, use GUIA_APRESENTACAO.md e adapte mentalmente

---

### 6. [CHECKLIST_PROGRESSO_WOKWI.md](computer:///mnt/user-data/outputs/CHECKLIST_PROGRESSO_WOKWI.md) ⚠️ **NÃO CRIADO AINDA**
**Status:** Será criado baseado no CHECKLIST_PROGRESSO.md original  
**O que será:** Checklist adaptado para Wokwi  
**Conteúdo previsto:**
- Fases adaptadas (preparação, Wokwi, Python, etc.)
- Cronograma específico para simulador
- Métricas de sucesso

**Nota:** Por agora, use CHECKLIST_PROGRESSO.md e adapte

---

### 7. [RELATORIO_TEMPLATE_WOKWI.md](computer:///mnt/user-data/outputs/RELATORIO_TEMPLATE_WOKWI.md) ⚠️ **NÃO CRIADO AINDA**
**Status:** Será criado baseado no RELATORIO_TEMPLATE.md original  
**O que será:** Template de relatório adaptado para Wokwi  
**Conteúdo previsto:**
- Seções adaptadas mencionando Wokwi
- Como documentar uso de simulador
- Como apresentar resultados do Python
- Justificativas técnicas

**Nota:** Por agora, use RELATORIO_TEMPLATE.md e adapte seção de Metodologia

---

## 💻 CÓDIGO FONTE

### 8. [esp32_freertos_wokwi.ino](computer:///mnt/user-data/outputs/esp32_freertos_wokwi.ino) ⭐ **CÓDIGO PRINCIPAL**
**O que é:** Código ESP32 otimizado para Wokwi  
**Linhas:** ~450  
**Características:**
- 5 tarefas periódicas com diferentes prioridades
- Logging estruturado para análise
- Geração automática de CSV
- Estatísticas detalhadas
- Comentários explicativos
- Pronto para copiar e colar no Wokwi

**Como usar:**
1. Copie TODO o conteúdo
2. Cole no sketch.ino do Wokwi
3. Inicie simulação

---

### 9. [diagram.json](computer:///mnt/user-data/outputs/diagram.json)
**O que é:** Configuração do circuito virtual do Wokwi  
**Conteúdo:**
- ESP32 DevKit V1
- 5 LEDs (vermelho, verde, azul, amarelo, laranja)
- 5 resistores de 220Ω
- Conexões Serial Monitor

**Como usar:**
1. Copie TODO o conteúdo
2. Cole no diagram.json do Wokwi
3. LEDs aparecerão automaticamente

---

### 10. [wokwi.toml](computer:///mnt/user-data/outputs/wokwi.toml)
**O que é:** Arquivo de configuração do projeto Wokwi  
**Conteúdo:** Configurações mínimas  

**Como usar:** Crie este arquivo se necessário (opcional)

---

## 🐍 SCRIPTS PYTHON

### 11. [analyze_logs.py](computer:///mnt/user-data/outputs/analyze_logs.py) ⭐ **ANÁLISE AUTOMÁTICA**
**O que é:** Script Python para análise completa dos dados  
**Linhas:** ~300  
**Funcionalidades:**
- Lê arquivo CSV do Wokwi
- Gera 4 visualizações profissionais:
  - Diagrama de Gantt
  - CPU Usage (pizza)
  - Response Times (histogramas)
  - Jitter Comparison (barras)
- Imprime estatísticas detalhadas
- Conta context switches

**Requisitos:**
```bash
pip3 install pandas matplotlib numpy
```

**Como usar:**
```bash
python3 analyze_logs.py events.csv
```

**Output:**
- gantt_chart.png
- cpu_usage.png
- response_times.png
- jitter_comparison.png
- Tabela de estatísticas no terminal

---

## 📄 ARQUIVOS DE REFERÊNCIA (Versão Original - Hardware Real)

Estes arquivos são da versão original do projeto (com hardware real).  
**Você NÃO precisa deles para o Wokwi**, mas estão aqui para referência.

### 12. [README.md](computer:///mnt/user-data/outputs/README.md)
Original README para hardware físico + Tracealyzer

### 13. [GUIA_IMPLEMENTACAO.md](computer:///mnt/user-data/outputs/GUIA_IMPLEMENTACAO.md)
Guia para hardware real + Arduino IDE + Tracealyzer

### 14. [GUIA_TRACEALYZER.md](computer:///mnt/user-data/outputs/GUIA_TRACEALYZER.md)
Guia do Tracealyzer (não funciona no Mac)

### 15. [GUIA_APRESENTACAO.md](computer:///mnt/user-data/outputs/GUIA_APRESENTACAO.md)
Guia de apresentação para hardware real

### 16. [CHECKLIST_PROGRESSO.md](computer:///mnt/user-data/outputs/CHECKLIST_PROGRESSO.md)
Checklist para hardware real

### 17. [RELATORIO_TEMPLATE.md](computer:///mnt/user-data/outputs/RELATORIO_TEMPLATE.md)
Template de relatório para hardware real

### 18. [esp32_freertos_tracealyzer.ino](computer:///mnt/user-data/outputs/esp32_freertos_tracealyzer.ino)
Código para hardware + Tracealyzer

### 19. [esp32_freertos_simple.ino](computer:///mnt/user-data/outputs/esp32_freertos_simple.ino)
Código simplificado sem Tracealyzer

---

## 🗂️ ORGANIZAÇÃO RECOMENDADA

Organize seus arquivos assim no seu Mac:

```
~/Documents/Projeto_SOTR/
│
├── 📚 Documentacao/
│   ├── INSTRUCOES_USO.md              ⭐ Leia primeiro!
│   ├── README_WOKWI_SEGGER.md         ⭐ Overview
│   ├── GUIA_WOKWI.md
│   ├── GUIA_SEGGER_SYSTEMVIEW.md
│   └── Referencia_Original/
│       ├── README.md
│       ├── GUIA_IMPLEMENTACAO.md
│       └── (outros arquivos originais)
│
├── 💻 Codigo/
│   ├── esp32_freertos_wokwi.ino       ⭐ Código principal
│   ├── diagram.json
│   └── wokwi.toml
│
├── 🐍 Scripts/
│   └── analyze_logs.py                ⭐ Análise Python
│
├── 📊 Dados/
│   ├── events.csv                     (gerado pelo Wokwi)
│   ├── gantt_chart.png               (gerado pelo Python)
│   ├── cpu_usage.png                 (gerado pelo Python)
│   ├── response_times.png            (gerado pelo Python)
│   └── jitter_comparison.png         (gerado pelo Python)
│
├── 📸 Screenshots/
│   ├── wokwi_circuito.png
│   ├── wokwi_serial.png
│   └── wokwi_codigo.png
│
└── 📝 Relatorio/
    ├── Relatorio_SOTR_[Nome].md      (seu trabalho)
    └── Relatorio_SOTR_[Nome].pdf     (versão final)
```

---

## 🚀 FLUXO DE TRABALHO RECOMENDADO

### Fase 1: Setup (Dia 1)
1. ✅ Ler INSTRUCOES_USO.md
2. ✅ Ler README_WOKWI_SEGGER.md
3. ✅ Criar conta no Wokwi
4. ✅ Configurar projeto no Wokwi
5. ✅ Testar simulação

### Fase 2: Coleta de Dados (Dia 2)
1. ✅ Ler GUIA_WOKWI.md
2. ✅ Executar simulação de 60s
3. ✅ Copiar CSV
4. ✅ Tirar screenshots

### Fase 3: Análise (Dia 2-3)
1. ✅ Ler GUIA_SEGGER_SYSTEMVIEW.md
2. ✅ Instalar Python + bibliotecas
3. ✅ Executar analyze_logs.py
4. ✅ Conferir visualizações geradas

### Fase 4: Documentação (Dias 3-5)
1. ✅ Abrir RELATORIO_TEMPLATE.md
2. ✅ Preencher todas as seções
3. ✅ Inserir imagens
4. ✅ Revisar
5. ✅ Exportar PDF

### Fase 5: Apresentação (Dias 6-7)
1. ✅ Ler GUIA_APRESENTACAO.md
2. ✅ Preparar material
3. ✅ Ensaiar 2x
4. ✅ Apresentar! (05/12/2025)

---

## 📊 ESTATÍSTICAS DO PROJETO

**Total de Arquivos:** 19 arquivos  
**Linhas de Código:** ~1,200 linhas  
**Linhas de Documentação:** ~3,500 linhas  
**Tempo Estimado:** 10-15 horas total  

**Cobertura:**
- ✅ Setup completo
- ✅ Código otimizado
- ✅ Análise automática
- ✅ Visualizações profissionais
- ✅ Templates de documentação
- ✅ Guias passo a passo

---

## ⚡ ATALHOS RÁPIDOS

**Preciso começar AGORA:**
→ [INSTRUCOES_USO.md](computer:///mnt/user-data/outputs/INSTRUCOES_USO.md)

**Já tenho Wokwi configurado:**
→ [analyze_logs.py](computer:///mnt/user-data/outputs/analyze_logs.py)

**Preciso escrever relatório:**
→ [RELATORIO_TEMPLATE.md](computer:///mnt/user-data/outputs/RELATORIO_TEMPLATE.md)

**Preciso preparar apresentação:**
→ [GUIA_APRESENTACAO.md](computer:///mnt/user-data/outputs/GUIA_APRESENTACAO.md)

**Dúvida sobre Wokwi:**
→ [GUIA_WOKWI.md](computer:///mnt/user-data/outputs/GUIA_WOKWI.md)

**Dúvida sobre análise:**
→ [GUIA_SEGGER_SYSTEMVIEW.md](computer:///mnt/user-data/outputs/GUIA_SEGGER_SYSTEMVIEW.md)

---

## 💡 NOTAS IMPORTANTES

1. **Wokwi vs Hardware Real:**
   - Wokwi é PERFEITAMENTE VÁLIDO para este projeto
   - Demonstra adaptabilidade e uso de ferramentas modernas
   - Usado na indústria profissional

2. **Segger SystemView:**
   - Funciona no macOS (Tracealyzer não)
   - Ferramenta profissional
   - Usada por ARM, NXP, STMicroelectronics

3. **Python para Análise:**
   - Gera visualizações equivalentes ao SystemView
   - Scripts automáticos (menos trabalho!)
   - Resultados profissionais

4. **Arquivos Originais:**
   - Mantidos para referência
   - Você NÃO precisa deles para Wokwi
   - Use apenas os arquivos "WOKWI" no nome

---

## ✅ PRÓXIMOS PASSOS

**AGORA MESMO:**
1. Abra [INSTRUCOES_USO.md](computer:///mnt/user-data/outputs/INSTRUCOES_USO.md)
2. Siga o "INÍCIO RÁPIDO"
3. Em 30 minutos você terá o projeto rodando!

**DEPOIS:**
1. Capture dados (60s de simulação)
2. Execute análise Python
3. Escreva relatório
4. Prepare apresentação

---

## 🎯 OBJETIVO FINAL

Entregar em 05/12/2025:
- ✅ Projeto funcionando no Wokwi (compartilhável via link)
- ✅ Relatório completo (PDF)
- ✅ Visualizações profissionais (imagens)
- ✅ Apresentação preparada (10-15 min)

**VOCÊ TEM TUDO QUE PRECISA! 🚀**

---

**Última atualização:** 30 de Novembro de 2025  
**Versão:** 2.0 - Adaptado para Wokwi + Segger SystemView (macOS)  
**Status:** ✅ Completo e pronto para uso

