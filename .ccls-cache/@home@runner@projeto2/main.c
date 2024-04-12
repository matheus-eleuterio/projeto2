#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos = 0; // Inicializa a posição com 0
    ERROS erro = fs[4](tarefas, &pos); // Carrega as tarefas do arquivo
    if (erro != OK) {
        printf("Erro ao carregar as tarefas. Código de erro: %d\n", erro);
        return 1; // Retorna um código de erro para indicar falha
    }

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        if (opcao == 0) {
            printf("Você saiu do programa\n");
            break; // Sai do loop ao digitar 0
        }

        if (opcao < 1 || opcao > 3) {
            printf("Opcao invalida\n");
        } else {
            erro = fs[opcao - 1](tarefas, &pos); // Chama a função correspondente à opção
            if (erro != OK) {
                printf("Erro ao executar a operacao. Código de erro: %d\n", erro);
            }
        }
    } while (1);

    erro = fs[3](tarefas, &pos); // Salva as tarefas no arquivo
    if (erro != OK) {
        printf("Erro ao salvar as tarefas. Código de erro: %d\n", erro);
        return 1; // Retorna um código de erro para indicar falha
    }

    return 0; // Retorna 0 para indicar sucesso
}