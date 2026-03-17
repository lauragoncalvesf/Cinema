# 🎬 Sistema de Cinema em C

Projeto desenvolvido em linguagem C com o objetivo de simular um sistema básico de gerenciamento de cinema, utilizando manipulação de arquivos para armazenamento de dados.

---

## 📌 Sobre o projeto

Este sistema permite gerenciar informações de usuários e filmes por meio de arquivos `.txt`, funcionando como um banco de dados simples. O projeto foi estruturado de forma modular, separando responsabilidades em diferentes arquivos `.c` e `.h`.

---

## 🚀 Funcionalidades

- Cadastro de usuários  
- Armazenamento de dados em arquivos `.txt`  
- Gerenciamento de filmes  
- Leitura e escrita de dados persistentes  
- Estrutura modular com uso de headers (.h)  

---

## 🛠️ Tecnologias utilizadas

- Linguagem C  
- Manipulação de arquivos (stdio.h)  
- Organização modular (arquivos `.c` e `.h`)  

---

## 📂 Estrutura do projeto
/cinema

├── cinema.c

├── cinema.h

├── filme.c

├── filme.h

├── maincinema.c

├── usuarios.txt

├── filmes.txt


---

## ▶️ Como compilar e executar

No terminal, dentro da pasta do projeto:

```bash
gcc maincinema.c cinema.c filme.c -o cinema
./cinema
```

## 📸 Exemplo de uso
```bash

1 - Cadastrar usuário
2 - Listar filmes
3 - Sair
Escolha uma opção:
```
## 🎯 Objetivo

Este projeto foi desenvolvido como prática acadêmica para reforçar conceitos de:
- Programação em C
- Modularização de código
- Manipulação de arquivos
- Organização de projetos
