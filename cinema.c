#include "cinema.h"

int obterOpcaoMenu(){
    char entrada[50]; 
    int opcao = -1;

    while (1)
    {
        printf("Digite uma opção do menu: ");
        fgets(entrada, 50, stdin);             
        entrada[strcspn(entrada, "\n")] = '\0'; 

        if (apenasNumeros(entrada))
        {
            opcao = atoi(entrada); 
            break;
        }
        else
        {
            printf("Entrada inválida! Por favor, insira um número.\n");
        }
    }

    return opcao;
}

void obterData(char *data){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int apenasLetras(const char *str){
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]) && str[i] != ' ')
        {
            return 0; 
        }
    }
    return 1;
}

int apenasNumeros(const char *str){
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; 
        }
    }
    return 1; 
}

void obterEntradaApenasCaracteres(char *buffer, int tamanho, const char *prompt) {
    char entradaTemp[tamanho];

    while (1) {
        printf("%s", prompt);
        fgets(entradaTemp, tamanho, stdin);
        entradaTemp[strcspn(entradaTemp, "\n")] = 0; 

        if (strlen(entradaTemp) > 0 && apenasLetras(entradaTemp)) {
            strcpy(buffer, entradaTemp);
            break;
        } else {
            printf("Entrada inválida! Por favor, insira apenas letras.\n");
        }
    }
}


void salvarUsuarioNoArquivo(Usuario* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Usuario* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "ID: %d\n", atual->id);
        fprintf(arquivo, "Nome: %s\n", atual->nome);
        fprintf(arquivo, "Email: %s\n", atual->email);
        fprintf(arquivo, "Senha: %s\n", atual->senha);
        fprintf(arquivo, "Idade: %d\n", atual->idade);
        fprintf(arquivo, "-----------------------------------\n");
        atual = atual->proximo;
    }

    fclose(arquivo); 
}

void carregarUsuariosDoArquivo(Usuario** lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Criando um novo arquivo.\n");
        return; 
    }

    Usuario* novoUsuario;
    while (1) {
        novoUsuario = (Usuario*) malloc(sizeof(Usuario));
        if (fscanf(arquivo, "ID: %d\n", &novoUsuario->id) != 1) {
            free(novoUsuario);
            break; 
        }
        fscanf(arquivo, "Nome: %[^\n]\n", novoUsuario->nome);
        fscanf(arquivo, "Email: %[^\n]\n", novoUsuario->email);
        fscanf(arquivo, "Senha: %[^\n]\n", novoUsuario->senha);
        fscanf(arquivo, "Idade: %d\n", &novoUsuario->idade);
        fscanf(arquivo, "-----------------------------------\n"); 
        novoUsuario->proximo = NULL;
        inserirUsuarioNaLista(lista, novoUsuario);
    }
    fclose(arquivo);
}


void inserirUsuarioNaLista(Usuario** lista, Usuario* novoUsuario) {
    if (*lista == NULL) {
        *lista = novoUsuario; 
    } else {
        Usuario* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;  
        }
        atual->proximo = novoUsuario;  
    }
}

void cadastrarUsuario(Usuario ** lista){
    Usuario * novoUsuario = (Usuario*)malloc(sizeof(Usuario));
    if (novoUsuario == NULL){
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    printf("Digite seu nome de usuario: ");
    fgets(novoUsuario->nome, sizeof(novoUsuario->nome), stdin);
    novoUsuario->nome[strcspn(novoUsuario->nome, "\n")] = '\0';

 printf("Digite o e-mail do usuário: ");
    fgets(novoUsuario->email, sizeof(novoUsuario->email), stdin);
    novoUsuario->email[strcspn(novoUsuario->email, "\n")] = '\0';

    printf("Digite a senha do usuário: ");
    fgets(novoUsuario->senha, sizeof(novoUsuario->senha), stdin);
    novoUsuario->senha[strcspn(novoUsuario->senha, "\n")] = '\0';

    printf("Digite a idade do usuário: ");
    scanf("%d", &novoUsuario->idade);
    getchar(); // Limpar o buffer

    novoUsuario->proximo = NULL;

    // Atribuir um ID ao novo usuário
    if (*lista == NULL) {
        novoUsuario->id = 1;
        *lista = novoUsuario;
    } else {
        Usuario* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        novoUsuario->id = atual->id + 1;
        atual->proximo = novoUsuario;
    }

    printf("Usuário criado com sucesso! ID do usuário: %d\n", novoUsuario->id);
}

void exibirUsuarios(Usuario *lista) {
    Usuario *atual = lista;
    if (atual == NULL) {
        printf("\nNenhum pedido armazenado.\n");
        return;
    }

    printf("\n-----------------------------\n");

    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Nome: %s\n", atual->nome);
        printf("Email: %s\n", atual->email);
        printf("Idade: %d\n", atual->idade);
        printf("-----------------------------\n");
        atual = atual->proximo;
    }
}
