#ifndef TAREFAS_H
#define TAREFAS_H

#define TAMANHO_CATEGORIA 100
#define TAMANHO_DESCRICAO 300

#define TOTAL 100

typedef struct {
    int prioridade;
    char descricao[TAMANHO_DESCRICAO];
    char categoria[TAMANHO_CATEGORIA];
} Tarefa;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos);
ERROS exportar(Tarefa tarefas[], int *pos);

void clearBuffer();

const char* mensagemErro(ERROS erro);

#endif
