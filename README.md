# Problemas Clássicos de IPC em C

> 🎓 **Projeto Acadêmico**
> Repositório destinado aos projetos e atividades desenvolvidos para o curso de **Ciência da Computação da PUC**.

Implementação na linguagem **C** dos principais problemas clássicos de **Comunicação Interprocessos (IPC - Inter-Process Communication)** e Sincronização. 

Este projeto tem como foco o estudo prático de concorrência e paralelismo (tópicos fundamentais de Sistemas Operacionais). A base das implementações envolve o controle de seções críticas e a prevenção de impasses (*deadlocks*) e inanição (*starvation*), utilizando primitivas de sincronização como **Mutexes** e **Semáforos**.

## 📂 Estrutura do Projeto

Os códigos-fonte estão localizados dentro do diretório `Projeto_IPC/`. As implementações abordam simulações de cenários clássicos da literatura da computação, que geralmente incluem:
* O Problema do Produtor-Consumidor
* O Problema dos Leitores-Escritores
* O Problema dos Filósofos Comensais (Jantar dos Filósofos)
* O Problema do Barbeiro Dorminhoco

## 🚀 Como Compilar e Executar

Para compilar e executar os códigos deste projeto, é necessário um ambiente com compilador C (como o `gcc`). Por utilizar bibliotecas de concorrência nativas (como `pthread.h`), a compilação exige uma flag específica de linkagem.

Abra o terminal e siga os passos abaixo:

```bash
# 1. Entre no diretório do projeto
cd Projeto_IPC

# 2. Compile o código-fonte (Importante: utilize a flag -pthread)
gcc barbeiro dorminhoco.c -o exec_ipc -pthread
gcc Filosofos Glutoes.c -o exec_ipc -pthread
gcc leitores e escritores.c -o exec_ipc -pthread
gcc produtor e consumidor.c -o exec_ipc -pthread

# 3. Execute o programa (Linux ou macOS)
./exec_ipc

# 3. Execute o programa (Windows)
exec_ipc.exe
