#include "tarefas.h"
#include <stdio.h>

int main() {
  funcao fs[] = {criar, deletar, listar, exportar, salvar, carregar};
  Tarefa tarefas[TOTAL];
  int pos = 0;
  ERROS erro = fs[5](tarefas, &pos); // Carregar tarefas do arquivo

  if (erro != OK) {
    const char *msgErro = mensagemErro(erro);
    printf("Erro ao carregar as tarefas. %s\n", msgErro);
  }

  int opcao;
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar tarefa\n");
    printf("2 - Deletar tarefa\n");
    printf("3 - Listar tarefas\n");
    printf("4 - Exportar tarefas\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &opcao);
    getchar(); // Limpar o buffer após a leitura do inteiro

    switch (opcao) {
    case 0:
      printf("Você saiu do programa\n");
      break;
    case 1:
    case 2:
    case 3:
    case 4:
      erro = fs[opcao - 1](tarefas, &pos);
      if (erro != OK) {
        const char *msgErro = mensagemErro(erro);
        printf("Erro ao executar a operacao. %s\n", msgErro);
      }
      break;
    default:
      printf("Opcao invalida\n");
      break;
    }
  } while (opcao != 0);

  erro = fs[4](tarefas, &pos); // Salvar tarefas no arquivo
  if (erro != OK) {
    const char *msgErro = mensagemErro(erro);
    printf("Erro ao salvar as tarefas. %s\n", msgErro);
  }

  return 0;
}
