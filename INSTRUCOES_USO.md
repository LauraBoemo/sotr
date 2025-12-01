# 🚀 INSTRUÇÕES DE USO - Projeto SOTR (Wokwi + SystemView)

## 📦 Arquivos Recebidos

Você recebeu o seguinte pacote completo:

### 📚 Documentação:
1. **README_WOKWI_SEGGER.md** - Leia PRIMEIRO!
2. **GUIA_WOKWI.md** - Como usar o Wokwi
3. **GUIA_SEGGER_SYSTEMVIEW.md** - Análise de dados
4. **CHECKLIST_PROGRESSO_WOKWI.md** - Acompanhe seu progresso
5. **GUIA_APRESENTACAO_WOKWI.md** - Prepare a apresentação
6. **RELATORIO_TEMPLATE_WOKWI.md** - Template do relatório

### 💻 Código:
7. **esp32_freertos_wokwi.ino** - Código principal
8. **diagram.json** - Circuito virtual
9. **wokwi.toml** - Configurações Wokwi

### 🐍 Scripts Python:
10. **analyze_logs.py** - Análise e visualizações

### 📄 Este arquivo:
11. **INSTRUCOES_USO.md** - Você está aqui!

---

## ⚡ INÍCIO RÁPIDO (30 minutos)

### Passo 1: Criar Conta no Wokwi (5 min)

```
1. Acesse: https://wokwi.com
2. Clique em "Sign Up"
3. Use Google ou GitHub (mais rápido)
4. Confirme email se necessário
5. Faça login
```

### Passo 2: Criar Projeto (5 min)

```
1. Clique em "New Project"
2. Escolha "ESP32"
3. Nomeie: "SOTR_FreeRTOS_Projeto"
4. Clique em "Create"
```

### Passo 3: Configurar Código (10 min)

```
1. Delete o código padrão do sketch.ino
2. Copie TUDO de esp32_freertos_wokwi.ino
3. Cole no sketch.ino do Wokwi
4. Aguarde salvar automaticamente
```

### Passo 4: Configurar Circuito (5 min)

```
1. Clique na aba "diagram.json"
2. Delete o conteúdo
3. Copie TUDO de diagram.json (fornecido)
4. Cole no diagram.json do Wokwi
5. Volte para aba "sketch.ino"
6. Veja os LEDs aparecerem no diagrama!
```

### Passo 5: Testar (5 min)

```
1. Clique em "Start Simulation" (botão verde)
2. Aguarde compilação (~30s)
3. Abra "Serial Monitor" (ícone inferior)
4. Veja logs aparecendo!
5. Veja LEDs piscando!
```

✅ **Parabéns! Você tem o projeto rodando!**

---

## 📊 CAPTURA DE DADOS (45 minutos)

### Passo 1: Executar Simulação Completa (60s)

```
1. No Wokwi, inicie simulação
2. Aguarde EXATAMENTE 60 segundos
   (o código está configurado para isso)
3. O sistema irá:
   - Executar tarefas
   - Coletar dados
   - Gerar CSV automaticamente
4. Aguarde mensagem:
   "COLETA DE DADOS CONCLUÍDA"
```

### Passo 2: Copiar CSV (5 min)

```
1. No Serial Monitor, role PARA BAIXO
2. Encontre a seção "EVENT LOG (CSV FORMAT)"
3. Copie TUDO desde "Timestamp_us,Task,Event" até o final
4. Cole em arquivo de texto
5. Salve como: events.csv
```

**Exemplo do CSV:**
```
Timestamp_us,Task,Event
1000234,1,S
1050678,1,E
500123,2,S
530456,2,E
...
```

### Passo 3: Salvar Screenshots (10 min)

**Screenshot 1: Circuito com LEDs**
```
1. Pause simulação
2. Cmd+Shift+4 (Mac) ou use ferramenta de screenshot
3. Selecione área do circuito
4. Salve como: wokwi_circuito.png
```

**Screenshot 2: Serial Monitor**
```
1. Capture tela do Serial Monitor
2. Salve como: wokwi_serial.png
```

**Screenshot 3: Código**
```
1. Capture código principal (setup + tasks)
2. Salve como: wokwi_codigo.png
```

### Passo 4: Gravar Vídeo (10 min) - OPCIONAL

```
1. QuickTime Player → File → New Screen Recording
2. Selecione área do Wokwi
3. Inicie gravação
4. Inicie simulação
5. Grave por 30-60 segundos
6. Pare gravação
7. Salve como: wokwi_demo.mov
```

---

## 🐍 ANÁLISE COM PYTHON (30 minutos)

### Passo 1: Instalar Python (se necessário)

**Verificar se já tem:**
```bash
python3 --version
```

**Se não tiver, instalar no Mac:**
```bash
# Via Homebrew
brew install python3
```

### Passo 2: Instalar Bibliotecas

```bash
pip3 install pandas matplotlib numpy
```

### Passo 3: Executar Análise

```bash
# No terminal, navegue até a pasta do projeto
cd ~/Downloads/Projeto_SOTR

# Execute o script
python3 analyze_logs.py events.csv
```

### Passo 4: Visualizar Resultados

O script irá gerar 4 imagens:

```
✓ gantt_chart.png          - Diagrama de Gantt
✓ cpu_usage.png            - Uso da CPU (pizza)
✓ response_times.png       - Histogramas de tempos
✓ jitter_comparison.png    - Comparação de jitter
```

Abra as imagens geradas para conferir!

---

## 📝 ESCREVER RELATÓRIO (3-4 horas)

### Passo 1: Abrir Template

```
1. Abra RELATORIO_TEMPLATE_WOKWI.md
2. Leia TODO o template
3. Entenda estrutura
```

### Passo 2: Preencher Seções

**Ordem recomendada:**

1. **Introdução** (30 min)
   - Objetivos
   - Justificativa do uso de Wokwi

2. **Fundamentação Teórica** (45 min)
   - FreeRTOS
   - Conceitos de RTOS
   - ESP32

3. **Metodologia** (45 min)
   - Ambiente (Wokwi + SystemView)
   - Estrutura das tarefas
   - Configurações

4. **Implementação** (30 min)
   - Explicar código
   - Decisões de design

5. **Resultados** (1 hora)
   - Inserir TODAS as imagens
   - Preencher tabelas
   - Descrever observações

6. **Discussão** (45 min)
   - Análise crítica
   - Comparar com teoria
   - Lições aprendidas

7. **Conclusão** (15 min)
   - Resumir conquistas
   - Aprendizados

8. **Referências** (15 min)
   - Adicionar todas as fontes

### Passo 3: Revisar

```
1. Ortografia e gramática
2. Todas as imagens inseridas?
3. Todas as tabelas preenchidas?
4. Referências completas?
5. Numeração de seções OK?
```

### Passo 4: Exportar PDF

```
1. Use Typora, Markdown Preview ou similar
2. Ou converta para Word e depois PDF
3. Verifique formatação no PDF
4. Salve como: Relatorio_SOTR_[SeuNome].pdf
```

---

## 🎤 PREPARAR APRESENTAÇÃO (2-3 horas)

### Passo 1: Ler Guia

```
1. Abra GUIA_APRESENTACAO_WOKWI.md
2. Leia completamente
3. Tome notas
```

### Passo 2: Organizar Material

**Prepare:**
- [ ] Link do Wokwi (copie URL do projeto)
- [ ] PDF do relatório
- [ ] Todas as imagens
- [ ] Vídeo (se fez)
- [ ] Notas de apresentação

### Passo 3: Criar Roteiro

Escreva roteiro de 10-15 minutos:

```
Minuto 1-2: Introdução
   - Apresentação
   - Objetivos do projeto
   
Minuto 3-5: Demonstração Wokwi
   - Mostrar circuito
   - Iniciar simulação
   - Logs no Serial
   
Minuto 6-9: Análise de Resultados
   - Gantt chart
   - CPU usage
   - Jitter
   - Preempções
   
Minuto 10-12: Discussão
   - Conceitos de RTOS
   - Aprendizados
   
Minuto 13-15: Conclusão e Perguntas
```

### Passo 4: Ensaiar

```
1. Ensaio solo (cronometrar!)
2. Ensaio para amigo/familiar
3. Ajustar timing
4. Preparar respostas para perguntas comuns
```

---

## ✅ CHECKLIST FINAL

Antes de entregar/apresentar:

### Arquivos para Entregar:
- [ ] Relatorio_SOTR_[Nome].pdf
- [ ] esp32_freertos_wokwi.ino
- [ ] diagram.json
- [ ] events.csv
- [ ] Link_Wokwi.txt (com URL do projeto)
- [ ] Pasta Screenshots/ com todas as imagens

### Preparação da Apresentação:
- [ ] Link do Wokwi testado
- [ ] Projeto funcionando
- [ ] Screenshots salvos
- [ ] Laptop carregado
- [ ] Roteiro pronto
- [ ] Ensaiado 2x

### Conhecimento:
- [ ] Sei explicar preempção
- [ ] Sei explicar prioridades
- [ ] Sei explicar jitter
- [ ] Sei explicar FreeRTOS
- [ ] Sei justificar uso de Wokwi

---

## 🆘 PROBLEMAS COMUNS

### Wokwi não compila?
```
✓ Verifique se copiou TODO o código
✓ Não modificou nada por engano
✓ Tente criar projeto novo e copiar de novo
```

### CSV não está gerando?
```
✓ Aguarde 60 segundos completos
✓ Verifique se LOG_EVENTS está true no código
✓ Role para BAIXO no Serial Monitor
```

### Python dá erro?
```
✓ Instalou pandas, matplotlib, numpy?
✓ Arquivo events.csv está na mesma pasta?
✓ Formato do CSV está correto?
```

### Imagens não geram?
```
✓ Verifique instalação das bibliotecas
✓ Tente executar linha por linha no Python
✓ Copie CSV corretamente (sem caracteres extras)
```

---

## 📅 CRONOGRAMA SUGERIDO

### HOJE (Dia 1):
- [x] Leu este arquivo
- [ ] Criou conta no Wokwi
- [ ] Testou projeto básico
- [ ] Capturou primeiro CSV

### Amanhã (Dia 2):
- [ ] Instalou Python + bibliotecas
- [ ] Gerou visualizações
- [ ] Tirou todos os screenshots

### Dias 3-4:
- [ ] Escreveu rascunho do relatório
- [ ] Preencheu todas as seções

### Dia 5:
- [ ] Revisou relatório
- [ ] Exportou PDF final

### Dias 6-7:
- [ ] Preparou apresentação
- [ ] Ensaiou 2x

### Dia da Apresentação (05/12):
- [ ] Chegou 15min antes
- [ ] Testou tudo
- [ ] APRESENTOU! 🎯

---

## 💡 DICAS DE OURO

1. **Salve TUDO em múltiplos locais**
   - Google Drive
   - iCloud
   - Pen drive
   - Email para si mesmo

2. **Documente conforme avança**
   - Não deixe relatório para última hora
   - Tire screenshots "extras"
   - Anote observações interessantes

3. **Teste antes da apresentação**
   - Link do Wokwi funciona?
   - PDF abre corretamente?
   - Laptop está carregado?

4. **Seja honesto na apresentação**
   - "Usei simulador porque X"
   - Demonstra adaptabilidade!
   - É uma escolha técnica válida

5. **Mostre entusiasmo**
   - Você aprendeu muito!
   - Este é um projeto profissional
   - Wokwi + SystemView são ferramentas reais da indústria

---

## 🎓 ARGUMENTOS PARA O PROFESSOR

Se o professor perguntar "Por que Wokwi?":

> "Optei por usar o Wokwi por três razões principais:
> 
> 1. **Compatibilidade:** O Tracealyzer não funciona nativamente no macOS, 
>    e o Wokwi me permitiu desenvolver sem limitações de hardware.
> 
> 2. **Profissionalismo:** O Wokwi é usado na indústria para prototipação 
>    rápida e testes. Empresas como Espressif (fabricante do ESP32) o recomendam.
> 
> 3. **Reprodutibilidade:** Qualquer pessoa pode abrir meu projeto via link 
>    e ver exatamente o mesmo comportamento, o que é ideal para validação 
>    acadêmica.
> 
> Para análise, utilizei o Segger SystemView em conjunto com scripts Python 
> para gerar visualizações profissionais equivalentes às obtidas com hardware real."

---

## 📧 CONTATO E SUPORTE

**Dúvidas sobre o Projeto:**
- Professor Frederico Schaf

**Problemas com Wokwi:**
- Discord: https://wokwi.com/discord
- Docs: https://docs.wokwi.com

**Problemas com Python/Scripts:**
- Stack Overflow
- ChatGPT/Claude para debug

---

## 🎉 PALAVRAS FINAIS

Você tem em mãos um projeto completo e profissional!

- ✅ Código de qualidade industrial
- ✅ Ferramentas profissionais (Wokwi + SystemView)
- ✅ Documentação extensa
- ✅ Visualizações impactantes

**Não é porque está em simulador que é menos válido!**

Empresas Fortune 500 usam simuladores para desenvolver sistemas críticos 
(aeronaves, carros, satélites) antes de testar em hardware.

Você demonstra:
- 📚 Conhecimento de RTOS
- 🛠️ Adaptabilidade (usou ferramentas disponíveis)
- 💻 Competência técnica
- 🎯 Capacidade de entrega

---

## ✨ BOA SORTE!

Agora é só seguir o passo a passo e você terá um projeto excelente!

Qualquer dúvida, consulte os guias detalhados fornecidos.

**VOCÊ CONSEGUE! 🚀**

---

**Última atualização:** Novembro 2025  
**Versão:** 1.0 - Wokwi + Segger SystemView
