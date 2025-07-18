# 💾 Simpletron – Simulador de Computador Didático

## 📘 Descrição

O **Simpletron** é um simulador de um computador educacional criado para fins didáticos. Ele permite entender, na prática, como funciona o processamento de instruções em linguagem de máquina, oferecendo uma experiência próxima do funcionamento real da CPU e da memória.

Inspirado no modelo proposto por J. Glenn Brookshear em *Fundamentos da Programação de Computadores*, o Simpletron simula uma máquina hipotética com um conjunto reduzido de instruções e uma arquitetura extremamente simples.

---

## 🧠 Objetivos Educacionais

- Compreender os fundamentos da execução de programas em linguagem de máquina
- Explorar conceitos como memória RAM, acumulador, registradores e ciclo de instrução
- Praticar lógica computacional em nível baixo
- Visualizar o funcionamento de instruções de entrada, saída, controle e aritmética

---

## 🏗️ Arquitetura da Máquina

A máquina simulada contém:

- **100 posições de memória** (endereçadas de 00 a 99)
- **Acumulador (ACC)**: registrador principal para cálculos
- **Contador de Instrução (PC)**: indica a posição da próxima instrução
- **Registrador de Instrução**: carrega o código atualmente em execução

---

## 🔧 Conjunto de Instruções

As instruções seguem o formato `+XXXX`, sendo:

- `XX` (dois primeiros dígitos) o **código da operação**
- `YY` (dois últimos dígitos) o **endereço de memória**

| Código | Instrução       | Descrição                                        |
|--------|------------------|--------------------------------------------------|
| 10     | `READ`           | Lê valor e armazena na memória                  |
| 11     | `WRITE`          | Exibe valor da memória                          |
| 20     | `LOAD`           | Carrega valor da memória no acumulador         |
| 21     | `STORE`          | Armazena valor do acumulador na memória        |
| 30     | `ADD`            | Soma valor da memória ao acumulador            |
| 31     | `SUBTRACT`       | Subtrai valor da memória do acumulador         |
| 32     | `DIVIDE`         | Divide acumulador pelo valor da memória        |
| 33     | `MULTIPLY`       | Multiplica acumulador pelo valor da memória    |
| 40     | `BRANCH`         | Salta para a posição de memória indicada       |
| 41     | `BRANCHNEG`      | Salta se acumulador for negativo               |
| 42     | `BRANCHZERO`     | Salta se acumulador for zero                   |
| 43     | `HALT`           | Encerra o programa                             |

---

## ✅ Exemplo de Programa

Este programa soma dois números fornecidos pelo usuário:

```txt
10 00   ; Lê primeiro número (memória 00)
10 01   ; Lê segundo número (memória 01)
20 00   ; Carrega o primeiro número para o acumulador
30 01   ; Soma o segundo número ao acumulador
21 02   ; Armazena o resultado na memória 02
11 02   ; Exibe o resultado da soma
43 00   ; Fim da execução

