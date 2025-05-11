# CallTree
Sobre o Projeto

### O CallTree é um sistema de agenda telefônica desenvolvido em linguagem C, utilizando a estrutura de Árvore Binária de Busca (BST) para armazenar, organizar e gerenciar contatos de forma eficiente. O programa permite cadastrar, buscar, listar e remover contatos, com persistência de dados em arquivo de texto.

Características

 *   Aplicação escrita em C.

 *   Estrutura de dados baseada em **Árvore Binária de Busca (BST).**

 *   Interface de uso via terminal.

 *   Funcionalidades CRUD para contatos telefônicos.

 *  Persistência automática em arquivo listaTelefonica.txt, mantendo os contatos entre execuções.

---

Estrutura de Dados Utilizada

### O projeto utiliza a seguinte estrutura para representar os contatos:

typedef struct Contact {
    char name[20];
    char telephone[20];
    struct Contact* left;
    struct Contact* right;
} Contact;

### Cada contato armazena o nome, telefone e ponteiros para os nós esquerdo e direito da árvore, garantindo que a estrutura permaneça ordenada de acordo com os nomes cadastrados.

#### Principais Funcionalidades

##### Função createContact

Cria e inicializa um novo contato a partir do nome e telefone informados pelo usuário.

##### Função insertContact

* Insere um novo contato na árvore, posicionando-o de forma ordenada pelo nome, respeitando as regras da árvore binária de busca.

##### Função searchContact

* Realiza a busca de um contato pelo nome, retornando o número de telefone correspondente, caso encontrado.

##### Função removeContact

* Remove um contato da árvore, ajustando a estrutura para manter a ordenação e integridade da árvore após a exclusão.

##### Função listContacts

* Percorre a árvore binária em ordem alfabética (in-order) e exibe todos os contatos cadastrados.

##### Função saveContacts

* Salva todos os contatos da árvore no arquivo listaTelefonica.txt, sobrescrevendo o conteúdo anterior e garantindo a persistência dos dados.

##### Função loadContacts

* Carrega os contatos previamente salvos no arquivo listaTelefonica.txt para a estrutura em memória, permitindo continuidade entre execuções.

---

### Menu Principal do Programa

O programa é controlado por um menu interativo via terminal, com as seguintes opções:

* Criar contato

* Buscar contato

* Listar contatos

* Remover contato

* Sair e salvar

Ao encerrar a aplicação, os dados são automaticamente salvos no arquivo de texto.
Estrutura do Arquivo de Dados

O arquivo **database.txt** é utilizado para armazenar os contatos registrados. O formato adotado é simples, onde cada contato ocupa duas linhas consecutivas:

* **nome_do_contato**
* **telefone**

Este padrão se repete para cada contato armazenado.
Compilação e Execução

---

#### Para compilar o projeto, utilize o seguinte comando no terminal:

*gcc listaTelefonica.c -o listaTelefonica*

#### Para executar o programa após a compilação:

*./listaTelefonica*
