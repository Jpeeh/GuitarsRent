#include "clientes_alugueres.h"
#include "structs.h"
#include "guitarras.h"
#include "outros.h"

//FUNÇÕES DOS ALUGUERES
void conclui_aluguer(Cliente *c, Guitarra *g, int total, int nif) {
    float pagamento;
    Data temp;
    Banido ban;
    Cliente *aux = c;
    int estado;

    while (aux) {
        Aluguer *aux1 = aux->lista;
        while (aux1) {
            if (aux->nif == nif) {
                aux1->estado = 1;
                printf("Data de Entrega: ");
                scanf(" %d %d %d", &temp.dia, &temp.mes, &temp.ano);
                aux1->fim.dia = temp.dia;
                aux1->fim.mes = temp.mes;
                aux1->fim.ano = temp.ano;
                pagamento = verifica_atraso(g, total, aux1, temp);

                printf("Estado da Guitarra: ");
                scanf(" %d", &estado);

                if (estado == 2 && aux->cont_estado <= 3) { //SE ENTREGAR GUITARRA DANIFICADA PELA 4ªVEZ
                    g = actualiza_estado_guitarra(g, total, estado, aux1->id);
                    printf("CLIENTE BANIDO POR DANOS MATERIAIS!\n");
                    c = remove_cliente_lista(c, aux->nif);
                    //Passar os dados do cliente que está no nó para uma estrutura de clientes banidos auxiliar
                    ban.nif = aux->nif;
                    strcpy(ban.motivo, "Guitarras Danificadas!");
                    escreve_clientes_banidos(ban);
                    escreve_ficheiro(c);
                    return;
                }

                if (estado == 2) {
                    aux->n_alugueres--;
                    aux1->estado = 2;
                    for (int i = 0; i < total; i++) { //SE ENTREGAR A GUITARRA DANIFICADA, A MULTA É O VALOR DA GUITARRA
                        if ((g + i)->id == aux1->id) {
                            g = actualiza_estado_guitarra(g, total, estado, aux1->id);
                            printf("Valor a pagar e de: %d", (g + i)->valor);
                        }
                    }
                }

                if (estado == 1) {
                    aux->n_alugueres--;
                    aux1->estado = 1;
                    g = actualiza_estado_guitarra(g, total, estado, aux1->id);
                    if (pagamento != -1) {
                        printf("Cliente tem a pagar: %.2f\n", pagamento);
                    } else {
                        printf("CLIENTE BANIDO POR ATRASO!\n");
                        c = remove_cliente_lista(c, aux->nif);
                        //Passar os dados do cliente que está no nó para uma estrutura de clientes banidos auxiliar
                        ban.nif = aux->nif;
                        strcpy(ban.motivo, "Mais de 20 dias de atraso de entrega!");
                        escreve_clientes_banidos(ban);
                    }
                }
            }
            aux1 = aux1->prox;
        }
        aux = aux-> prox;
    }

    escreve_ficheiro(c);
}

void alugueres_activos(Cliente *c) {
    Cliente *aux = c;

    while (aux) {
        Aluguer *aux1 = aux->lista;
        if(aux1 != NULL){
            while (aux1) {
                if (aux1->estado == 0) {
                    printf("NIF do Cliente: %d\tID da Guitarra :%d\nData Inicial: %d/%d/%d\n",
                            aux->nif, aux1->id, aux1->inicio.dia, aux1->inicio.mes, aux1->inicio.ano);
                }
                aux1 = aux1->prox;
            }
        }else{
            printf("Nao existem alugueres de momento activos!\n");
            return;
        }
        aux = aux-> prox;
    }
}

void adiciona_aluguer(Cliente *a, Guitarra *g, int total, int nif, int id) {
    Cliente *temp = a;
    Aluguer *novo;
    Data aux;

    if (temp->n_alugueres < 5) {
        while (temp != NULL && temp->nif != nif)
            temp = temp->prox;

        if (temp != NULL) {
            novo = malloc(sizeof (Aluguer));
            if (novo == NULL)
                return;

            novo->id = id;
            novo->estado = 0;
            g = actualiza_estado_guitarra(g, total, 1, novo->id);

            printf("Data Inicial do Aluguer: ");
            scanf(" %d %d %d", &novo->inicio.dia, &novo->inicio.mes, &novo->inicio.ano);
            novo->fim.dia = 0; // METER A ZERO POR QUE O ALUGUER ESTÁ A DECORRER
            novo->fim.mes = 0;
            novo->fim.ano = 0;

            aux = verifica_data(novo);
            printf("Data Final do Aluguer: %d / %d / %d\n", aux.dia, aux.mes, aux.ano);
            novo->prox = temp->lista; /*insere no inicio*/
            temp->lista = novo;
            temp->n_alugueres = temp->n_alugueres + 1;
        }
        escreve_ficheiro(a);
    } else {
        printf("Nao pode alugar mais guitarras de momento!\n");
        return;
    }
}

Aluguer *carrega_info_aluguer(Aluguer *lista_aluguer, FILE *f) {
    char buf[150];
    Aluguer *aux = NULL;

    while (fgets(buf, sizeof (buf), f)) {
        if (strcmp(buf, "\n") == 0 || strcmp(buf, " ") == 0)
            return lista_aluguer;
        if ((!(aux = malloc(sizeof (Aluguer)))))
            printf("Erro na Alocacao de Memoria\n");

        if (sscanf(buf, "%d %d %d %d %d %d %d %d", &aux->id, &aux->estado, &aux->inicio.dia, &aux->inicio.mes,
                &aux->inicio.ano, &aux->fim.dia, &aux->fim.mes, &aux->fim.ano) != 8) {
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

//FUNÇÕES DOS CLIENTES
Cliente *carrega_info_cliente(Cliente *lista, Aluguer *lista_aluguer) {
    FILE *f = fopen("clientes.txt", "rt");
    Cliente *aux = NULL;
    char buffer[300], c;

    if (f == NULL)
        printf("erro a abrir ficheiro %s", f);

    while ((c = getc(f)) != EOF) { // ler até ao final do ficheiro
        if (!(aux = malloc(sizeof (Cliente))))
            printf("Erro na alocacao de memoria\n");

        aux->lista = NULL;
        //LEITURA DOS DADOS DOS CLIENTES
        fgets(buffer, sizeof (buffer), f); //Passar a linha toda do .txt para o buffer
        sscanf(buffer, " %d %d %99[^\n]s", &aux->nif, &aux->n_alugueres, aux->nome); //separa a linha do buffer para as varíaveis 

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

void remove_cliente_ficheiro(Cliente *c) {
    escreve_ficheiro(c);
    return;
}

Cliente *remove_cliente_lista(Cliente *c, int nif) {
    Cliente *actual, *anterior = NULL;
    actual = c;

    while (actual != NULL && (actual->nif != nif)) {
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

Cliente *adiciona_cliente(Cliente *c) {
    Cliente *aux;
    aux = malloc(sizeof (Cliente));

    if (aux == NULL) {
        printf("\nErro na alocacao de memoria\n");
        return aux;
    } else {
        do {
            printf("Nome do Cliente: ");
            scanf(" %99[^\n]", aux->nome);
            printf("NIF do Cliente: ");
            scanf(" %d", &aux->nif);
        } while ((verifica_nif(aux->nif) != 0) || (verifica_cliente(aux->nif) != -1) || (verifica_cliente_banido(aux->nif) != 0));

        aux->n_alugueres = 0;
        aux->lista = NULL;
        aux->prox = c;
        c = aux;
    }
    escreve_ficheiro(aux);
    return aux;
}
