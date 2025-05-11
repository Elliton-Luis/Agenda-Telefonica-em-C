#CallTree

##Repositório para o projeto CallTree, um sistema de agenda telefônica desenvolvido em linguagem C, utilizando árvore binária de busca (BST) para armazenamento e organização de contatos.
Características do Programa

    Código desenvolvido em linguagem C

    Estrutura de dados baseada em Árvore Binária de Busca (BST)

    Operações acessadas via terminal

    Funções CRUD (Create, Read, Delete) de contatos telefônicos

    Persistência de dados em arquivo listaTelefonica.txt, garantindo que os contatos sejam mantidos entre execuções

Estrutura de Dados

typedef struct Contact {
    char name[20];
    char telephone[20];
    struct Contact* left;
    struct Contact* right;
} Contact;

    Estrutura que representa um contato, contendo nome, telefone e ponteiros para os nós esquerdo e direito da árvore.

Funções Principais
Contact* createContact(char name[], char telephone[])

Cria e inicializa um novo contato com os dados informados.
Contact* insertContact(Contact* root, char name[], char telephone[])

Insere um contato na árvore binária de forma ordenada pelo nome.
Contact* searchContact(Contact* root, char name[])

Busca um contato pelo nome e exibe o número, caso encontrado.
Contact* removeContact(Contact* root, char name[])

Remove um contato da árvore, reorganizando os ponteiros conforme necessário.
void listContacts(Contact* root)

Percorre a árvore em ordem alfabética e exibe todos os contatos cadastrados.
void saveContacts(Contact* root, const char* archiveName)

Grava os contatos cadastrados no arquivo especificado, sobrescrevendo o conteúdo anterior.
Contact* loadContacts(const char* archiveName, Contact* root)

Lê os contatos salvos no arquivo e os insere na árvore em memória.
Menu Principal

    Criar contato

    Buscar contato

    Listar contatos

    Remover contato

    Sair e salvar

Estrutura do Arquivo de Dados

O arquivo listaTelefonica.txt armazena os contatos no seguinte formato:

nome_do_contato
telefone
nome_do_contato
telefone
...

Cada par de linhas corresponde a um contato.
Compilação e Execução

Para compilar:

gcc listaTelefonica.c -o listaTelefonica

Para executar:

./listaTelefonica
