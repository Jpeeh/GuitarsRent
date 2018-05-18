#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>

void adiciona_guitarra(Guitarra *g, int *total) {
    FILE *ficheiro = fopen("guitarras.txt", "at");
    if (ficheiro == NULL)
        printf("erro no ficheiro %s\n", ficheiro);
    else {
        printf("ID da guitarra: ");
        scanf(" %d", &g->id);
        printf("Nome da guitarra: ");
        scanf(" %99[^\n]s", g->nome);
        do {
            printf("Preco diario da guitarra: ");
            scanf(" %f", &g->preco);
        } while (g->preco < 0);
        printf("Valor: ");
        scanf(" %d", &g->valor);
        do {
            printf("Estado: ");
            scanf(" %d", &g->estado);
        } while ((g->estado) < 0 || (g->estado > 2));
        fprintf(ficheiro, "%d\t%.2f\t%d\t%d\t%s\n", g->id, g->preco, g->valor, g->estado, g->nome);
    }
    *(total)++;
    fclose(ficheiro);
}

Cliente *adiciona_cliente(Cliente *c) {
    FILE *f = fopen("clientes.txt", "at");
    int contador = 0;

    Cliente *aux;
    aux = malloc(sizeof (Cliente));

    if (aux == NULL) {
        printf("\nErro na alocacao de memoria\n");
        return aux;
    } else {
        printf("Nome do Cliente: ");
        scanf(" %99[^\n]", aux->nome);
        do { // PARA VERIFICAR SE O NIF TEM 9 DÍGITOS!
            contador = 0;
            printf("NIF do Cliente: ");
            scanf(" %d", &aux->nif);
            int temp = aux->nif;
            do {
                temp /= 10;
                contador++;
            } while (temp != 0);
        } while (contador != 9);

        aux->prox = c;
        c = aux;
    }

    fseek(f, 0, SEEK_END);
    fprintf(f, "%d\t%d\t%s\n", aux->nif, aux->n_alugueres, aux->nome);
    aux = aux->prox;

    fclose(f);
    return aux;
}

void adiciona_aluguer(Cliente *a, char *nome, int id, int estado) {
    FILE *f = fopen("clientes.txt", "at");
    Aluguer *novo;

    while (a != NULL && strcmp(a->nome, nome) != 0)
        a = a->prox;

    if (a != NULL) {
        novo = malloc(sizeof (Aluguer));
        if (novo == NULL)
            return;

        if (a->n_alugueres < 5) { //1 cliente só pode ter até 5 alugueres
            novo->id = id;
            novo->estado = estado;
            printf("Data Inicial do Aluguer: ");
            scanf(" %d %d %d", &novo->inicio.dia, &novo->inicio.mes, &novo->inicio.ano);
            printf("Data Final do Aluguer: ");
            scanf(" %d %d %d", &novo->fim.dia, &novo->fim.mes, &novo->fim.ano);

            novo->prox = a->lista; /*insere no inicio*/
            a->lista = novo;
            a->n_alugueres++;
        } else {
            printf("No. maximo de alugueres possiveis de efectuar!\n");
        }
    }
    fprintf(f, "\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", novo->id, novo->estado, novo->inicio.dia, novo->inicio.mes, novo->inicio.ano,
            novo->fim.dia, novo->fim.mes, novo->fim.ano);
    fclose(f);
}

Cliente *remove_cliente_lista(Cliente *c, char *nome) {
    Cliente *actual, *anterior = NULL;
    actual = c;

    while (actual != NULL && (strcmp(actual->nome, nome) != 0)) {
        anterior = actual;
        actual = actual->prox;
    }

    if (actual == NULL)
        return c;
    if (anterior == NULL)
        c = actual->prox;
    else {
        anterior->prox = actual->prox;
    }

    free(actual);
    return c;
}

void remove_cliente_ficheiro(Cliente *c) {
    FILE *f = fopen("clientes.txt", "wt");

    while (c != NULL) {
        fprintf(f, "%d\t%d\t%s\n", c->nif, c->n_alugueres, c->nome);
        c = c->prox;
    }
    fclose(f);
}

Aluguer *carrega_info_aluguer(Aluguer *lista_aluguer, FILE *f) {
    char buf[150];
    Aluguer *aux = NULL;
    
    while (fgets(buf, sizeof (buf), f)) {
        if (strcmp(buf, "\n") == 0 || strcmp(buf, " ") == 0)
            return lista_aluguer; 
        if((!(aux = malloc(sizeof(Aluguer)))))
            printf("Erro na Alocacao de Memoria\n");
        
        if(sscanf(buf, "%d %d %d %d %d %d %d %d", &aux->id, &aux->estado, &aux->inicio.dia, &aux->inicio.mes, 
                &aux->inicio.ano, &aux->fim.dia, &aux->fim.mes, &aux->fim.ano) != 8){
                    aux->fim.dia = 0;
                    aux->fim.mes = 0;
                    aux->fim.ano = 0;
                }
        aux->prox = NULL;
        
        if (lista_aluguer == NULL)
            lista_aluguer = aux;
        else {
            Aluguer *current = lista_aluguer;
            while (current->prox != NULL)
                current = current->prox;
            current->prox = aux;
        }
    }
    return lista_aluguer;
}

Cliente *carrega_info_cliente(Cliente *lista, Aluguer *lista_aluguer) {
    FILE *f = fopen("clientes.txt", "rt");
    Cliente *aux = NULL;
    char buffer[150], c;

    if (f == NULL)
        printf("erro a abrir ficheiro %s", f);

    while ((c = getc(f)) != EOF) { // ler até ao final do ficheiro
        if (!(aux = malloc(sizeof (Cliente))))
            printf("Erro na alocacao de memoria\n");

        aux->lista = NULL;
        //LEITURA DOS DADOS DOS CLIENTES
        fgets(buffer, sizeof (buffer), f); //Passar a linha toda do .txt para o buffer
        sscanf(buffer, "%d %d %99[^\n]s", &aux->nif, &aux->n_alugueres, aux->nome); //separa a linha do buffer para as varíaveis 
        //LEITURA DOS DADOS DOS ALUGUERES
        aux->lista = carrega_info_aluguer(lista_aluguer, f); //carrega para memoria a info dos alugueres
        aux->prox = NULL;

        if (lista == NULL)
            lista = aux;
        else {
            Cliente *current = lista;
            while (current->prox != NULL)
                current = current->prox;
            current->prox = aux;
        }
    }
    fclose(f);
    return lista;
}

void mostrar_info(Cliente *c) {
    Cliente *aux = c;

    if (c == NULL) {
        printf("A Lista esta vazia\n");
        return;
    } else {
        while (aux) { //se a lista não estiver vazia
            printf("NIF: %d\tNo. Alugueres: %d\tNome: %s\n", aux->nif, aux->n_alugueres, aux->nome);
            Aluguer *aux1 = aux->lista;
            if (aux1 != NULL) {
                while (aux1) {
                    if(aux1->fim.dia == 0){
                    printf("ID da Guitarra: %d\tEstado: %d\tData Inicial de Aluguer: %d/%d/%d\tData Final de Aluguer: A decorrer...\n",
                            aux1->id, aux1->estado, aux1->inicio.dia, aux1->inicio.mes, aux1->inicio.ano);
                    }
                    else{
                        printf("ID da Guitarra: %d\tEstado: %d\tData Inicial de Aluguer: %d/%d/%d\tData Final de Aluguer: %d/%d/%d\n",
                            aux1->id, aux1->estado, aux1->inicio.dia, aux1->inicio.mes, aux1->inicio.ano, aux1->fim.dia, aux1->fim.mes, aux1->fim.ano);
                    }
                    aux1 = aux1->prox;
                }
                printf("\n");
            }
            aux = aux->prox;
        }
    }
}