#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"


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

void obterEntradaApenasNumeros(int *valor, int tamanho, const char *prompt) {
    char entradaTemp[tamanho];

    while (1) {
        printf("%s", prompt);
        fgets(entradaTemp, tamanho, stdin);
        entradaTemp[strcspn(entradaTemp, "\n")] = 0;

        if (strlen(entradaTemp) > 0 && apenasNumeros(entradaTemp)) {
            *valor = atoi(entradaTemp); 
            break;
        } else {
            printf("Entrada inválida! Por favor, insira apenas números.\n");
        }
    }
}

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

// Função para salvar a lista de filmes no arquivo
void salvarFilmesNoArquivo(Filme* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Filme* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "ID: %d\n", atual->id);
        fprintf(arquivo, "Nome: %s\n", atual->nome);
        fprintf(arquivo, "Genero: %s\n", atual->genero);
        fprintf(arquivo, "Ano: %d\n", atual->ano);
        fprintf(arquivo, "Classificacao: %d\n", atual->classificacao);
        fprintf(arquivo, "-----------------------------------\n");
        atual = atual->proximo;
    }

    fclose(arquivo);
}

// Função para carregar os filmes do arquivo para a lista encadeada
void carregarFilmesDoArquivo(Filme** lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Criando um novo arquivo.\n");
        return;
    }

    Filme* novoFilme;
    while (1) {
        novoFilme = (Filme*)malloc(sizeof(Filme));
        if (fscanf(arquivo, "ID: %d\n", &novoFilme->id) != 1) {
            free(novoFilme);
            break;
        }
        fscanf(arquivo, "Nome: %[^\n]\n", novoFilme->nome);
        fscanf(arquivo, "Genero: %[^\n]\n", novoFilme->genero);
        fscanf(arquivo, "Ano: %d\n", &novoFilme->ano);
        fscanf(arquivo, "Classificacao: %d\n", &novoFilme->classificacao);
        fscanf(arquivo, "-----------------------------------\n");
        novoFilme->proximo = NULL;
        inserirFilmeNaLista(lista, novoFilme);
    }

    fclose(arquivo);
}

// Função para inserir o filme na lista encadeada
void inserirFilmeNaLista(Filme** lista, Filme* novoFilme) {
    if (*lista == NULL) {
        *lista = novoFilme;
    } else {
        Filme* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoFilme;
    }
}

// Função para adicionar um novo filme
void adicionarFilme(Filme** lista) {
    Filme* novoFilme = (Filme*)malloc(sizeof(Filme));
    if (novoFilme == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    obterEntradaApenasCaracteres(novoFilme->nome, sizeof(novoFilme->nome), "Título do filme: ");

    obterEntradaApenasCaracteres(novoFilme->genero, sizeof(novoFilme->genero), "Gênero do filme: ");

    obterEntradaApenasNumeros(&novoFilme->ano, 10, "Ano do filme: ");

    obterEntradaApenasNumeros(&novoFilme->classificacao, 10, "Classificação indicativa do filme: ");

    novoFilme->proximo = NULL;

    // Atribuir um ID ao novo filme
    if (*lista == NULL) {
        novoFilme->id = 1;
        *lista = novoFilme;
    } else {
        Filme* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        novoFilme->id = atual->id + 1;
        atual->proximo = novoFilme;
    }

    printf("Filme cadastrado com sucesso! ID do filme: %d\n", novoFilme->id);
}

// Função para exibir os filmes cadastrados
void exibirFilmes(Filme* lista) {
    Filme* atual = lista;
    int count = 0;
    
    if (atual == NULL) {
        printf("\nNenhum filme armazenado.\n");
        return;
    }
    
    printf("\n-----------------------------\n");
    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Título: %s\n", atual->nome);
        printf("Gênero: %s\n", atual->genero);
        printf("Ano: %d\n", atual->ano);
        printf("Classificação indicativa: %d\n", atual->classificacao);
        printf("-----------------------------\n");
        atual = atual->proximo;
        count++;
    }
    printf("Total de filmes cadastrados: %d\n", count);
}

// Função para excluir um filme da lista
void excluirFilme(Filme** lista, int id) {
    if (*lista == NULL) {
        printf("Nenhum filme para excluir.\n");
        return;
    }

    Filme* atual = *lista;
    Filme* anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Filme com ID %d não encontrado.\n", id);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Filme com ID %d excluído com sucesso!\n", id);
}

// Função para editar um filme
void editarFilme(Filme* lista, int id) {
    Filme* atual = lista;
    while (atual != NULL && atual->id != id) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Filme com ID %d não encontrado.\n", id);
        return;
    }

    printf("Editando filme com ID %d:\n", id);

    // Usando a função de entrada apenas caracteres para o nome
    printf("Novo título (atual: %s): ", atual->nome);
    obterEntradaApenasCaracteres(atual->nome, sizeof(atual->nome), "");

    // Usando a função de entrada apenas caracteres para o gênero
    printf("Novo gênero (atual: %s): ", atual->genero);
    obterEntradaApenasCaracteres(atual->genero, sizeof(atual->genero), "");

    // Usando a função de entrada apenas números para o ano
    printf("Novo ano (atual: %d): ", atual->ano);
    obterEntradaApenasNumeros(&atual->ano, 4, "");

    // Usando a função de entrada apenas números para a classificação
    printf("Nova classificação indicativa (atual: %d): ", atual->classificacao);
    obterEntradaApenasNumeros(&atual->classificacao, 3, "");

    printf("Filme com ID %d editado com sucesso!\n", id);
}

