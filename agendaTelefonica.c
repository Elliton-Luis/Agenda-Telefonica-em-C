#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct Contact{
    char name[100];
    char phone[20];
    struct Contact* left;
    struct Contact* right;
} Contact;

void formatPhone(char* phone, char* formattedPhone) {
    if (strlen(phone) != 11) {
        printf("\nTelefone no Formato Incorreto!!\n");
        strcpy(formattedPhone, phone);
        return;
    }

    sprintf(formattedPhone, "(%c%c) %c%c%c%c%c-%c%c%c%c",
        phone[0], phone[1],
        phone[2], phone[3], phone[4], phone[5], phone[6],
        phone[7], phone[8], phone[9], phone[10]);
}

void saveInOrder(Contact* root, FILE* archive) {
    if (root != NULL) {
        saveInOrder(root->left, archive);
        fprintf(archive, "%s\n%s\n", root->name, root->phone);
        saveInOrder(root->right, archive);
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

Contact* createContact(char name[],char phone[]){
    Contact* contact = (Contact*) malloc(sizeof(Contact));

    strcpy(contact->name, name);
    strcpy(contact->phone, phone);
    contact->left = contact->right = NULL;
    return contact;
}

Contact* insertContact(Contact* root,char name[],char phone[]){
    if(root == NULL){
        return createContact(name,phone);
    }
    if(strcmp(name,root->name) == 0){
        printf("\nEsse nome já existe na nossa lista!!\n");
        return root;
    }
    if(strcmp(name , root->name) < 0){
        root->left = insertContact(root->left,name, phone);
    }
    if(strcmp(name , root->name) > 0){
        root->right = insertContact(root->right,name, phone);
    }
    return root;
}

Contact* searchContact(Contact* root,char name[]){
    if(root == NULL){
        printf("O contato não foi encontrado\n\n");
        return NULL;
    }
    if(strcmp(root->name,name) == 0){
        char formattedPhone [20];
        formatPhone(root->phone, formattedPhone);
        printf("O Numero de %s é %s\n\n",root->name,formattedPhone);
        return root;
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
            printf("\nContato removido com sucesso!\n");
            root = temp;
            return temp;
        }else if(root->right == NULL){
            temp = root->left;
            free(root);
            printf("\nContato removido com sucesso!\n");
            root = temp;
            return temp;
        }else{
            temp = root->right;
            while (temp->left != NULL) {
            temp = temp->left;
            }
        }
        strcpy(root->name, temp->name);
        strcpy(root->phone, temp->phone);
        root->right = removeContact(root->right, temp->name);
    }
    return root;
}

Contact* editContact(Contact* root, char name []){
    if(root == NULL){
        printf("O contato não foi encontrado\n\n");
        return NULL;
    }
    if(strcmp(root->name,name) == 0){
        char formattedPhone[11];
        formatPhone(root->phone, formattedPhone);
        printf("\nNúmero atual: %s\n",formattedPhone);
        char newphone[11];
        while(1){
                printf("Insira o novo telefone(sem espaços): ");
                fgets(newphone,sizeof(newphone),stdin);
                newphone[strcspn(newphone, "\n")] = '\0';
                if(strlen(newphone) == 11){
                    break;;
                }
                printf("Formato errado, o numero deve ter 11 caracteres!!\n");
            }
            getchar();
        
        newphone[strcspn(newphone, "\n")] = '\0';
        strcpy(root->phone,newphone);
        return NULL;
    }
    if(strcmp(root->name,name) > 0 ){
        return editContact(root->left,name);
    }
    else{
        return editContact(root->right,name);
    }
}



void listContacts(Contact* root){
    if(root != NULL){

        listContacts(root->left);
        char formattedPhone [20];
        formatPhone(root->phone, formattedPhone);
        printf("Nome     : %s\n", root->name);
        printf("Telefone : %s\n", formattedPhone);
        printf("========================================\n");

        listContacts(root->right);
    }
}

void options(){
    printf("\n----- Opções -----\n");
    printf("1. Criar Contato\n");
    printf("2. Buscar Contato\n");
    printf("3. Listar Contatos\n");
    printf("4. Remover Contato\n");
    printf("5. Limpar Terminal\n");
    printf("6. Contar Contatos\n");
    printf("7. Editar Número\n");   
    printf("0. Sair e Salvar\n\n");
}

int countContacts(Contact* root){
    if(root == NULL){
        return 0;
    }
    return 1 + countContacts(root->left) + countContacts(root->right);}

void clearTerminal(){
    system("clear || cls");
}

void listContactsReverse(Contact* root){
    if(root != NULL){
        listContactsReverse(root->right);
        char formattedPhone [20];
        formatPhone(root->phone, formattedPhone);
        printf("Nome     : %s\n", root->name);
        printf("Telefone : %s\n", formattedPhone);
        printf("========================================\n");

        listContactsReverse(root->left);
    }
}

Contact* loadContacts(const char* archiveName, Contact* root){
    FILE* archive = fopen(archiveName, "r");
    if(!archive){
        archive = fopen(archiveName,"w");
        fclose(archive);
        return root;
    }
    char name[100]; 
    char phone[20];

    while (fgets(name, sizeof(name), archive) != NULL) {
        name[strcspn(name, "\n")] = '\0';

        if (fgets(phone, sizeof(phone), archive) != NULL) {
            phone[strcspn(phone, "\n")] = '\0';
            root = insertContact(root, name, phone);
        }
    }
    fclose(archive);
    return root;
}

int main(){
    const char* database = "database.txt";
    int choice;
    Contact* phoneDirectory = NULL;

    phoneDirectory = loadContacts(database,phoneDirectory);
    char name[100];
    char phone[12];
    do{
        options();
        printf("Insira a sua Escolha: ");
        scanf("%d",&choice);
        getchar();
        switch (choice)
        {
        case 1:
            printf("Insira o nome: ");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")] = '\0';
            int start = 0;
            while(name[start] == ' '){
                start++;
            }
            if(start > 0){
                memmove(name, name + start, strlen(name + start) + 1);
            }

            int len = strlen(name);
            while(len > 0 && name[len - 1] == ' '){
                name[len - 1] = '\0';
                len--;
            }
            while(1){
                printf("Insira o telefone(sem espaços): ");
                fgets(phone,sizeof(phone),stdin);
                phone[strcspn(phone, "\n")] = '\0';

                if(strlen(phone) == 11){
                    break;
                }
                printf("Formato errado, o numero deve ter 11 caracteres!!\n");
            }
            getchar();
            for(int i = 0; name[i];i++){
                name[i] = tolower(name[i]);
            }
            phoneDirectory = insertContact(phoneDirectory, name, phone);

            printf("\nPressione Enter para Continuar...");
            fgets(phone,sizeof(phone),stdin);
            phone[strcspn(phone, "\n")] = '\0';
            break; 
        case 2:
            printf("Insira o nome: ");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")] = '\0';

            for(int i = 0; name[i];i++){
                name[i] = tolower(name[i]);
            }

            searchContact(phoneDirectory, name);
            printf("\nPressione Enter para Continuar...");
            fgets(phone,sizeof(phone),stdin);
            phone[strcspn(phone, "\n")] = '\0';
            break;

        case 3:
            if(phoneDirectory == NULL){
                printf("...Nenhum Contato foi Encontrado\n\n");
            }else{
                int option = 0;
                printf("1.A-Z\n");
                printf("2.Z-A\n");
                scanf("%d",&option);
                getchar();

                if (option == 1){
                    printf("\n");
                    listContacts(phoneDirectory);
                    printf("\n");
                }
                else if (option == 2){
                    printf("\n");
                    listContactsReverse(phoneDirectory);
                    printf("\n");
                }
                else{
                    printf("Opção Inválida");
                }
            }
            printf("\nPressione Enter para Continuar...");
            fgets(phone,sizeof(phone),stdin);

            phone[strcspn(phone, "\n")] = '\0';
            break;
        case 4:
            printf("Insira o nome: ");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")] = '\0';

            for(int i = 0; name[i];i++){
                name[i] = tolower(name[i]);
            }
            phoneDirectory = removeContact(phoneDirectory, name);
            
            printf("\nPressione Enter para Continuar...");
            fgets(phone,sizeof(phone),stdin);
            phone[strcspn(phone, "\n")] = '\0';
            break;
        case 5:
            clearTerminal();
            break;
        case 6:
            int count;
            count = countContacts(phoneDirectory);
            printf("A Sua Lista Possui %d Contatos\n",count);
            printf("\nPressione Enter para Continuar...");
            fgets(phone,sizeof(phone),stdin);
            phone[strcspn(phone, "\n")] = '\0';
            break;
        case 7:
            printf("Insira o contato a ser alterado: ");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")] = '\0';
            for(int i = 0; name[i];i++){
                name[i] = tolower(name[i]);
            }

            editContact(phoneDirectory,name);
            printf("Contato Alterado Com Sucesso!\n");
            printf("\nPressione Enter para Continuar...");
            fgets(phone,sizeof(phone),stdin);
            phone[strcspn(phone, "\n")] = '\0';
            break;
        case 0:
            break;
        default:
            printf("Insira uma opção válida\n");
            break;
        }
    }while(choice != 0);
    saveContacts(phoneDirectory, database);
    free(phoneDirectory);
}
