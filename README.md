# Agenda Telefonica

### Sobre o Projeto

O CallTree é um sistema de agenda telefônica desenvolvido em *linguagem C*, utilizando a estrutura de Árvore Binária de Busca (BST) para armazenar, organizar e gerenciar contatos de forma eficiente. O programa permite cadastrar, buscar, listar, editar, contar e remover contatos, com persistência de dados em arquivo de texto.

### Características

 *   Aplicação escrita em C.

 *   Estrutura de dados baseada em **Árvore Binária de Busca (BST).**

 *   Interface de uso via terminal.

 *   Funcionalidades CRUD para contatos telefônicos.

 *  Persistência automática em arquivo database.txt, mantendo os contatos entre execuções.

---

### Estrutura de Dados Utilizada

#### O projeto utiliza a seguinte estrutura para representar os contatos:


 ```c
typedef struct Contact {                                                                                    
    char name[20];                                                                                         
    char telephone[20];                                                                                    
    struct Contact* left;                                                                                  
    struct Contact* right;                                                                              
} Contact;
 ```



  Cada contato armazena o nome, telefone e ponteiros para os nós esquerdo e direito da árvore, garantindo que a estrutura permaneça ordenada de acordo com os nomes cadastrados.

---
### Menu Principal do Programa

O programa é controlado por um menu interativo *via terminal*, com as seguintes opções:
 
![image](https://github.com/user-attachments/assets/07493e1c-eb7f-47b7-84a8-70e31c6d7b1b)

1.Criar Um Novo Contato.

![image](https://github.com/user-attachments/assets/bcf329f2-d954-441d-b67f-3361244ab20d)

2.Busca o Número De Um Contato Através Do Nome.

![image](https://github.com/user-attachments/assets/388e1f36-81d7-4e86-9257-07777e34ed35)

3.Lista Todos os Contatos seja de A-Z ou de Z-A.

![image](https://github.com/user-attachments/assets/f0b7dba0-0ff3-48bf-8585-37c34a95f813)

4.Removerá Um Contato Com Base No Nome.

![image](https://github.com/user-attachments/assets/10d2c9fd-9c9a-47b1-8b60-caaa5c91e5d0)

5.Limpará o Terminal, deixando apenas as opções.

![image](https://github.com/user-attachments/assets/6e44fc2a-da56-45d7-9a06-9f24ffe1543d)

6.Irá Contar Todos Os Contatos Presentes Na Lista De Contatos.

![image](https://github.com/user-attachments/assets/baa5dfd2-2d36-4e74-a72e-343ee1bec87c)

7.Irá Editar o Telefone De Um Contato.

![image](https://github.com/user-attachments/assets/bb26074c-67e1-4e7d-ad10-92ec6092139a)


0.Salva os Contatos em Ordem A-Z no Arquivo database.txt e Finaliza a Aplicação·

Ao encerrar a aplicação, os dados são automaticamente salvos no arquivo de texto.

O arquivo **database.txt** é utilizado para armazenar os contatos registrados. O formato adotado é simples, onde cada contato ocupa duas linhas consecutivas:

* **nome do contato**
* **telefone**

Este padrão se repete para cada contato armazenado.
Compilação e Execução

---

#### Para compilar o projeto, utilize o seguinte comando no terminal:

`gcc listaTelefonica.c -o listaTelefonica`

#### Para executar o programa após a compilação:

`./listaTelefonica`
