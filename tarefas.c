#include "tarefas.h"
#include <stdio.h>
#include <string.h>

ERROS exportar(Tarefa tarefas[], int *pos) {
  int encontradas = 0;
  FILE *fp = fopen("tarefas.txt", "w");
  if (fp == NULL)
    return 0;

  for (int i = 0; i < *pos; i++) {
      encontradas = 1;

      fprintf(fp, "Pos: %d\t", i + 1);
      fprintf(fp, "Prioridade: %d\t", tarefas[i].prioridade);
      fprintf(fp, "Categoria: %s\t", tarefas[i].categoria);
      fprintf(fp, "Descricao: %s\n", tarefas[i].descricao);
    
  }
  fclose(fp);
  return OK;
}

ERROS listar(Tarefa tarefas[], int *pos) {
  char categoria[TAMANHO_CATEGORIA];
  int listarTodas = 0;

  if (*pos == 0) {
    return SEM_TAREFAS;
  }

  printf("Entre com a categoria que deseja listar (tecle enter para mostrar "
         "todas): ");
  fgets(categoria, TAMANHO_CATEGORIA, stdin);
  categoria[strcspn(categoria, "\n")] = '\0';


  if (strlen(categoria) > 0 && categoria[0] != '\n') {
    int encontradas = 0;
    for (int i = 0; i < *pos; i++) {
      if (strcmp(tarefas[i].categoria, categoria) == 0) {
        encontradas = 1;
        printf("Pos: %d\t", i + 1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
      }
    }

    if (!encontradas) {
      printf("Nenhuma tarefa encontrada para a categoria: %s\n", categoria);
    }
  } else { 
    listarTodas = 1;
  }

  if (listarTodas) {
    for (int i = 0; i < *pos; i++) {
      printf("Pos: %d\t", i + 1);
      printf("Prioridade: %d\t", tarefas[i].prioridade);
      printf("Categoria: %s\t", tarefas[i].categoria);
      printf("Descricao: %s\n", tarefas[i].descricao);
    }
  }

  return OK;
}

ERROS criar(Tarefa tarefas[], int *pos) {
  if (*pos >= TOTAL)
    return MAX_TAREFA;

  printf("Entre com a prioridade (1 até 10): ");
  scanf("%d", &tarefas[*pos].prioridade);
  clearBuffer();

  if (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10) {
    printf("Valor não é válido! Selecione um valor entre 1 e 10.\n");
    return OK;
  }

  printf("Entre com a categoria: ");
  fgets(tarefas[*pos].categoria, TAMANHO_CATEGORIA, stdin);
  tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0';

  printf("Entre com a descricao: ");
  fgets(tarefas[*pos].descricao, TAMANHO_DESCRICAO, stdin);
  tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0';

  *pos = *pos + 1;

  return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos) {

  if (*pos == 0)
    return SEM_TAREFAS;

  int pos_deletar;
  printf("Entre com a posicao da tarefa a ser deletada: ");
  scanf("%d", &pos_deletar);
  pos_deletar--;
  if (pos_deletar >= *pos || pos_deletar < 0)
    return NAO_ENCONTRADO;

  for (int i = pos_deletar; i < *pos; i++) {
    tarefas[i].prioridade = tarefas[i + 1].prioridade;
    strcpy(tarefas[i].categoria, tarefas[i + 1].categoria);
    strcpy(tarefas[i].descricao, tarefas[i + 1].descricao);
  }

  *pos = *pos - 1;

  return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "wb");
  if (f == NULL)
    return ABRIR;

  int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return ESCREVER;

  qtd = fwrite(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return ESCREVER;

  if (fclose(f))
    return FECHAR;

  return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "rb");
  if (f == NULL)
    return ABRIR;

  int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return LER;

  qtd = fread(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return LER;

  if (fclose(f))
    return FECHAR;

  return OK;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

const char *mensagemErro(ERROS erro) {
  switch (erro) {
  case OK:
    return "Operação realizada com sucesso.";
  case MAX_TAREFA:
    return "Número máximo de tarefas atingido.";
  case SEM_TAREFAS:
    return "Não há tarefas para realizar a operação.";
  case NAO_ENCONTRADO:
    return "A tarefa não foi encontrada.";
  case ABRIR:
    return "Erro ao abrir arquivo.";
  case FECHAR:
    return "Erro ao fechar arquivo.";
  case ESCREVER:
    return "Erro ao escrever no arquivo.";
  case LER:
    return "Erro ao ler do arquivo.";
  default:
    return "Erro desconhecido.";
  }
}
