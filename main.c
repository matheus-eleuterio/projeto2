#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos = 0; 
    ERROS erro = fs[4](tarefas, &pos); 
    if (erro != OK) {
        const char *msgErro = mensagemErro(erro);
        printf("Erro ao carregar as tarefas. %s\n", msgErro);
        return 1; 
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
            break; 
        }

        if (opcao < 1 || opcao > 3) {
            printf("Opcao invalida\n");
        } else {
            erro = fs[opcao - 1](tarefas, &pos); 
            if (erro != OK) {
                const char *msgErro = mensagemErro(erro);
                printf("Erro ao executar a operacao. %s\n", msgErro);
            }
        }
    } while (1);

    erro = fs[3](tarefas, &pos); 
    if (erro != OK) {
        const char *msgErro = mensagemErro(erro);
        printf("Erro ao salvar as tarefas. %s\n", msgErro);
        return 1; 
    }

    return 0; 
}
