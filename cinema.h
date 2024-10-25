#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


// Definição da struct de Pedido
typedef struct Usuario{
    int id;
    char nome[50];
    char senha[50];
    char email[80];
    int idade;
    struct Usuario * proximo;
} Usuario;


int obterOpcaoMenu();

void obterData(char *data);

// Função para verificar se a string contém apenas letras
int apenasLetras(const char *str);

// Função para verificar se a string contém apenas números
int apenasNumeros(const char *str);

// Função para obter uma entrada apenas com caracteres
void obterEntradaApenasCaracteres(char *buffer, int tamanho, const char *prompt);

// Função para salvar pedidos no arquivo
void salvarUsuarioNoArquivo(Usuario* lista, const char* nomeArquivo);

// Carrega os pedidos existentes do arquivo
void carregarUsuariosDoArquivo(Usuario** lista, const char* nomeArquivo);

// Função para inserir um pedido na lista encadeada
void inserirUsuarioNaLista(Usuario** lista, Usuario* novoPedido);

// Função para adicionar um pedido
void cadastrarUsuario(Usuario** lista);

// Função para listar os pedidos
void exibirUsuarios(Usuario *lista);

