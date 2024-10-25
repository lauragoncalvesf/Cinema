#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct filme {
    int id;
    char nome[100];
    char genero[50];
    int ano;
    int classificacao;
    struct filme *proximo; 
} Filme;

int obterOpcaoMenu();

int apenasNumeros(const char *str);

int apenasLetras(const char *str);

void obterEntradaApenasCaracteres(char *buffer, int tamanho, const char *prompt);

void obterEntradaApenasNumeros(int * valor, int tamanho, const char *prompt);

void salvarFilmesNoArquivo(Filme* lista, const char* nomeArquivo);

void carregarFilmesDoArquivo(Filme** lista, const char* nomeArquivo);

void inserirFilmeNaLista(Filme** lista, Filme* novoFilme);

void adicionarFilme(Filme** lista);

void exibirFilmes(Filme* lista);

void excluirFilme(Filme** lista, int id);

void editarFilme(Filme* lista, int id);