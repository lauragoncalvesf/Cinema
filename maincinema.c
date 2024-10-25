#include "cinema.h"

int main(){
    Usuario * listaUsuario = NULL;
    const char* nomeArquivo = "usuarios.txt";
    int opcao;

    carregarUsuariosDoArquivo(&listaUsuario, nomeArquivo);


    do{
        printf("\n----- | Cadastramento de Usuários | -----\n\n");
        printf("1. Cadastrar usuário\n");
        printf("2. Listar usuários\n");
        printf("0. Sair\n\n");

        opcao = obterOpcaoMenu();

        switch(opcao){
            case 1:
                cadastrarUsuario(&listaUsuario);
                salvarUsuarioNoArquivo(listaUsuario, nomeArquivo);
                break;
            case 2:
                exibirUsuarios(listaUsuario);
                break;
            case 0:
                salvarUsuarioNoArquivo(listaUsuario, nomeArquivo);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }while(opcao != 0);
    return 0;
}