#include <stdio.h>
#include "guitarras.h"
#include "structs.h"
#include "outros.h"

Guitarra *carregaVetor(Guitarra *g, int *tam) {
    *tam = 0;
    Guitarra aux, *vetor, *temp;
    FILE *f = fopen("guitarras.txt", "rt");

    if (f == NULL) {
        printf("ERRO ACEDER AO FICHEIRO!\n");
        return NULL;
    }

    vetor = malloc(sizeof (Guitarra)); //VERIFICAR ESTE MALLOC, DEVE SER COM O TAM
    if (vetor == NULL) {
        printf("Erro alocar memoria!!\n");
        return NULL;
    }

    if (verifica_ficheiro(f) == 1) {
        return NULL;
    } else {
        while (fscanf(f, "%d %f %d %d %49[^\n]", &aux.id, &aux.preco, &aux.valor, &aux.estado, aux.nome) == 5) {
            (*tam)++;
            temp = realloc(vetor, sizeof (Guitarra)*(*tam));
            vetor = temp;
            *(vetor + (*tam) - 1) = aux;
        }
    }
    fclose(f);
    return vetor;
}

void escreve_ficheiro_guitarras(Guitarra *g, int total) {
    FILE *f = fopen("guitarras.txt", "wt");
    int i;

    if (f == NULL) {
        printf("erro a abrir ficheiro %s", f);
        return;
    }

    if (g == NULL) {
        printf("Nao existem guitarras a mostrar!\n");
        return;
    }
    for (i = 0; i < total; i++) {
        fprintf(f, " %d %.2f %d %d %s\n", (g + i)->id, (g + i)->preco, (g + i)->valor,
                (g + i)->estado, (g + i)->nome);
    }

    fclose(f);
    return;
}

Guitarra *adiciona_guitarra(Guitarra *g, int *total) {
    Guitarra *aux;
    aux = (Guitarra*) realloc(g, (*total + 1) * sizeof (Guitarra));
    if (aux == NULL)
        return g;

    printf("ID da guitarra: ");
    scanf(" %d", &aux[*total].id);
    printf("Nome da guitarra: ");
    scanf(" %99[^\n]s", aux[*total].nome);
    printf("Preco diario da guitarra: ");
    scanf(" %f", &aux[*total].preco);
    printf("Valor: ");
    scanf(" %d", &aux[*total].valor);
    printf("Estado: ");
    scanf(" %d", &aux[*total].estado);
    (*total)++;
    g = aux;
    return g;
}

void mostra_guitarras(Guitarra g[], int total) {
    int i;
    Guitarra *aux;
    aux = g;

    if (aux == NULL) {
        printf("Nao existem guitarras!\n");
    } else {
        for (i = 0; i < total; i++) {
            printf("ID: %d\tPreco dia: %.2f\tValor: %d\tEstado: %d\tNome: %s\n", (aux + i)->id, (aux + i)->preco,
                    (aux + i)->valor, (aux + i)->estado, (aux + i)->nome);
        }
    }
}

void mostrar_guitarras_alugadas(Cliente *c, Guitarra *g, int total) {
    int i;
    Guitarra *aux;
    Cliente *aux1;
    Aluguer *aux2;
    aux1 = c;
    aux = g;

    if (aux == NULL) {
        printf("Nao existem guitarras!\n");
        return;
    }
    if (aux1 == NULL) {
        printf("Nao existem clientes!\n");
        return;
    }

    while (aux1) {
        aux2 = aux1->lista;
        while (aux2) {
            if (aux2->estado == 0) {
                for (i = 0; i < total; i++) {
                    if (((aux + i)->estado == 1) && ((aux + i)->id == aux2->id)) {
                        printf("Nome do Cliente: %s\tNIF Cliente: %d\nID: %d\tPreco dia: %.2f\tValor: %d\tEstado: %d\n",
                                aux1->nome, aux1->nif, (aux + i)->id, (aux + i)->preco, (aux + i)->valor, (aux + i)->estado);
                    }
                }
            } else {
                printf("Nao existem guitarras alugadas no momento!\n");
            }
            aux2 = aux2->prox;
        }
        aux1 = aux1->prox;
    }
}

void historico_guitarras(Cliente *c, int id) {
    Cliente *aux;
    Aluguer *aux1;
    aux = c;

    while (aux) {
        aux1 = aux->lista;
        while (aux1) {
            if (aux1->id == id) {
                if (aux1->fim.dia == 0) {
                    printf("Aluguer ainda a decorrer!\n");
                    printf("Nome do Cliente: %s\tData Inicial do Aluguer: %d/%d/%d", aux->nome, aux1->inicio.dia,
                            aux1->inicio.mes, aux1->inicio.ano);
                } else {
                    printf("Nome do Cliente: %s\tData Inicial do Aluguer: %d/%d/%d\tData Final do Aluguer: %d/%d/%d\n", aux->nome, aux1->inicio.dia,
                            aux1->inicio.mes, aux1->inicio.ano, aux1->fim.dia, aux1->fim.mes, aux1->fim.ano);
                }
            } else {
                printf("Historico inexistente para Guitarra com ID dado!\n");
                return;
            }
            aux1 = aux1->prox;
        }
        aux = aux->prox;
    }
}

int verifica_guitarras(Guitarra *g, int total, int id) {
    Guitarra aux;
    FILE *f = fopen("guitarras.txt", "rt");

    if (f == NULL) {
        printf("erro a abrir %s", f);
        return -1;
    }

    if (verifica_ficheiro(f) == 1) {
        return -1;
    } else {
        while (fscanf(f, "%d %f %d %d %49[^\n]", &aux.id, &aux.preco, &aux.valor, &aux.estado, aux.nome) == 5) {
            if (aux.id == id) {
                return 0; //EXISTEM A GUITARRA COM O ID DADO
            } else {
                return -1;
            }
        }
    }
}

int verifica_guitarra_danificada(Guitarra *g, int total, int id) {
    for (int i = 0; i < total; i++) {
        if ((g + i)->id == id) {
            if ((g + i)->estado == 2)
                return -1; //GUITARRA DANIFICADA, NAO PODE SER ALUGADA!
        }
    }
    return 0; //QUALQUER GUITARRA PODE SER ALUGADA!
}

float multa_guitarra(Guitarra *g, int id, int total) {
    Guitarra *aux = g;
    for (int i = 0; i < total; i++) {
        if ((g + i)->id == id) {
            return (g + i)->preco;
        }
    }
}

Guitarra *actualiza_estado_guitarra(Guitarra *g, int total, int estado, int id) {
    for (int i = 0; i < total; i++) {
        if ((g + i)->id == id) {
            (g + i)->estado = estado;
        }
    }
    escreve_ficheiro_guitarras(g, total);
    return g;
}

