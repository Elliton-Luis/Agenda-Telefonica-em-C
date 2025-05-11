#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct Contact{
    char name[20];
    char telephone[20];
    struct Contact* left;
    struct Contact* right;
} Contact;

Contact* createContact(char name[],char telephone[]){
    Contact* contact = (Contact*) malloc(sizeof(Contact));

    strcpy(contact->name, name);
    strcpy(contact->telephone, telephone);
    contact->left = contact->right = NULL;
    return contact;
}

Contact* insertContact(Contact* root,char name[],char telephone[]){
    if(root == NULL){
        return createContact(name,telephone);
    }
    if(strcmp(name , root->name) < 0){
        root->left = insertContact(root->left,name, telephone);
    }else if(strcmp(name , root->name) > 0){
        root->right = insertContact(root->right,name, telephone);
    }else{
    }
    return root;
}

Contact* searchContact(Contact* root,char name[]){
    if(root == NULL){
        printf("O contato não foi encontrado\n\n");
        return NULL;
    }
    if(strcmp(root->name,name) == 0){
        printf("O Numero de %s é %s\n\n",root->name,root->telephone);
        return NULL;
    }
    if(strcmp(root->name,name) > 0 ){
        return searchContact(root->left,name);
    }
    else{
        return searchContact(root->right,name);
    }
}

Contact* removeContact(Contact* root ,char name[]){
    Contact* temp;
    if(root == NULL){
        printf("Nenhum Contato a ser apagado\n");
        return NULL;
    }
    if(strcmp(root->name,name) > 0 ){
        root->left = removeContact(root->left, name);
    }else if(strcmp(root->name,name) < 0 ){
        root->right = removeContact(root->right, name);
    }else{
        if(root->left == NULL){
            temp = root->right;
            free(root);
            printf("Contato removido com sucesso!\n");
            root = temp;
            return temp;
        }else if(root->right == NULL){
            temp = root->left;
            free(root);
            printf("Contato removido com sucesso!\n");
            root = temp;
            return temp;
        }else{
            temp = root->right;
            while (temp->left != NULL) {
            temp = temp->left;
            }
        }
        strcpy(root->name, temp->name);
        strcpy(root->telephone, temp->telephone);
        root->right = removeContact(root->right, temp->name);
    }
    return root;
}


void listContacts(Contact* root){
    if(root != NULL){
        listContacts(root->left);
        printf("Nome: %s\nTelefone: %s\n", root->name, root->telephone);
        listContacts(root->right);
    }
}

void options(){
    printf("---- Opções -----\n");
    printf("1. Criar contato\n");
    printf("2. Buscar contato\n");
    printf("3. Listar contatos\n");
    printf("4. Remover contato\n");
    printf("0. Sair e Salvar\n\n");
}

void saveInOrder(Contact* node, FILE* archive) {
    if (node != NULL) {
        saveInOrder(node->left, archive);
        fprintf(archive, "%s\n%s\n", node->name, node->telephone);
        saveInOrder(node->right, archive);
    }
}


void saveContacts(Contact* root, const char* archiveName) {
    FILE* archive = fopen(archiveName, "w");
    if (!archive) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    saveInOrder(root, archive);
    fclose(archive);
}

Contact* loadContacts(const char* archiveName, Contact* root){
    FILE* archive = fopen(archiveName, "r");
    if(!archive){
        archive = fopen(archiveName,"w");
        fclose(archive);
        return root;
    }
    char name[20]; 
    char telephone[20];
    char line[25];

    while (fgets(name, sizeof(name), archive) != NULL) {
        name[strcspn(name, "\n")] = '\0';

        if (fgets(line, sizeof(line), archive) != NULL) {
            line[strcspn(line, "\n")] = '\0';
            strcpy(telephone, line);
            root = insertContact(root, name, telephone);
        }
    }
    fclose(archive);
    return root;
}

int main(){
    const char* database = "database.txt";
    int choice;
    Contact* telephoneDirectory = NULL;

    telephoneDirectory = loadContacts(database,telephoneDirectory);
    char name[20];
    char telephone[20];
    do{
        options();
        printf("Insira a sua Escolha: ");
        scanf("%d",&choice);
        if(choice == 1){
            printf("Insira o nome: ");
            scanf("%s",name);
            printf("Insira o Telefone(sem espaços): ");
            scanf("%s",telephone);
            for(int i = 0; name[i];i++){
                name[i] = tolower(name[i]);
            }
            telephoneDirectory = insertContact(telephoneDirectory, name, telephone);
            system("clear||cls"); 
        }
        if(choice == 2){
            printf("Insira o nome: ");
            scanf("%s",name);
            system("clear||cls");
            for(int i = 0; name[i];i++){
                name[i] = tolower(name[i]);
            }
            searchContact(telephoneDirectory, name);
        }
        if(choice == 3){
            if(telephoneDirectory == NULL){
                system("clear||cls");
                printf(".");
                fflush(stdout);
                sleep(1);
                printf(".");
                fflush(stdout);
                sleep(1);
                printf(".");
                fflush(stdout);
                sleep(1);
                printf("Nenhum Contato foi Encontrado\n\n");
                sleep(1);
            }else{
                system("clear||cls");
                listContacts(telephoneDirectory);
                printf("\n");
            }
        }
        if(choice == 4){
            printf("Insira o nome: ");
            scanf("%s",name);
            for(int i = 0; name[i];i++){
                name[i] = tolower(name[i]);
            }
            telephoneDirectory = removeContact(telephoneDirectory, name);
        }
        if(choice < 0 || choice > 4){
            printf("Insira uma opção válida\n");
            choice = 5;
        }
    }while(choice != 0);
    saveContacts(telephoneDirectory, database);
}
