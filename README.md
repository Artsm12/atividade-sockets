# 📦 Servidor e Cliente de Echo Multi-threaded

> Atividade de Redes de Computadores desenvolvida utilizando C++20.

## 🛠️ Pré-requisitos

Antes de compilar o projeto, certifique-se de ter **make** instalado no seu sistema, caso não tenha, rode:

```bash
sudo apt update && sudo apt install -y make # Ubuntu / Debian
sudo dnf install -y make # Fedora
sudo pacman -S make # Arch
brew install make # MacOS (precisa do homebrew)
winget install ezwinports.make # Windows
```

## 💻 Como Compilar

1. **Limpe arquvos de build antigos (opcional)**

```bash
make clean
```

2. **Compile o Projeto**

```bash
make
```

## 🚀 Como Executar

1. **Execute a aplicação do servidor**

```bash
./server
```

2. **Execute a aplicação do cliente**

```bash
./client
```

## Como Funciona

**O comando "echo", executado na aplicação do cliente, manda a mensagem escrita logo em seguida para o servidor, que devolve exatamente a mesma mensagem para a aplicação do cliente, da forma:**

```bash
echo <mensagem>
Servidor: <mensagem>
```

**O comando "quit" encerra a conexão do servidor com o cliente e libera a thread utilizado por aquele cliente**

## 📁 Estrutura do Projeto

```text
atividade-sockets/
|
├── include/
│   ├── client.hpp
│   ├── server.hpp
│   ├── thread_pool.hpp
│
├── src/
│   ├── client/
│       ├── client.cpp
│       ├── main.cpp
│   ├── server/
│       ├── server.cpp
│       ├── main.cpp
│   ├── thread_pool.cpp
│
├── .gitignore
├── Makefile
└── README.md
```
