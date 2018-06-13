#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>

int verifica_ficheiro(FILE *f) { //VERIFICA SE O FICHEIRO ESTA VAZIO
    int size;
    fseek(f, 0, SEEK_END);

    size = ftell(f);
    if (size == 0)
        return 1;

    rewind(f);
    return 0;
}

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

int verifica_guitarras(Guitarra *g, int *total, int id) {
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

void escreve_ficheiro(Cliente *a) {
    FILE *f = fopen("clientes.txt", "wt");
    Cliente *aux = a; //cliente auxiliar para poder escrever os dados no ficheiro
    Aluguer *aux_aluguer;
    fseek(f, 0, SEEK_SET);

    while (aux != NULL) {
        fprintf(f, " %d %d %s\n", aux->nif, aux->n_alugueres, aux->nome);
        aux_aluguer = aux->lista;
        if (aux_aluguer != NULL) {
            while (aux_aluguer) {
                if (aux_aluguer->fim.dia == 0)
                    fprintf(f, " %d %d %d %d %d\n", aux_aluguer->id, aux_aluguer->estado, aux_aluguer->inicio.dia, aux_aluguer->inicio.mes, aux_aluguer->inicio.ano);
                else {
                    fprintf(f, " %d %d %d %d %d %d %d %d\n", aux_aluguer->id, aux_aluguer->estado,
                            aux_aluguer->inicio.dia, aux_aluguer->inicio.mes, aux_aluguer->inicio.ano,
                            aux_aluguer->fim.dia, aux_aluguer->fim.mes, aux_aluguer->fim.ano);
                }
                aux_aluguer = aux_aluguer->prox;
            }
        }
        aux = aux->prox;
        fprintf(f, "\n");
    }
    fclose(f);
}

int verifica_cliente(int nif) {
    FILE *f = fopen("clientes.txt", "rt");
    Cliente aux;

    if (f == NULL)
        printf("erro a abrir ficheiro %s", f);

    while (fscanf(f, " %d %d %99[^\n]s", &aux.nif, &aux.n_alugueres, &aux.nome) == 3) {
        if (nif == aux.nif) {
            printf("Cliente ja existente!\n");
            return 0;
        }
    }
    return -1; //CLIENTE INEXISTENTE!
}

int verifica_nif(int nif) {
    int contador = 0;

    while (nif != 0) { //PARA O NIF TER 9 DIGITOS
        nif = nif / 10;
        contador++;
    }

    if (contador == 9) {
        return 0; //NIF VÁLIDO!
    } else {
        return -1; //NIF INVÁLIDO!
    }
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

Data verifica_data(Aluguer *aux) {
    Data temp;
    int dia_aux;

    if (aux->inicio.dia > 25) {
        if ((aux->inicio.dia + 7) > 31 && (aux->inicio.mes != 12)) {
            dia_aux = 31 - aux->inicio.dia;
            temp.dia = 7 - dia_aux;
            temp.mes = aux->inicio.mes + 1;
            temp.ano = aux->inicio.ano;
        }
        if ((aux->inicio.dia + 7) > 31 && (aux->inicio.mes == 12)) {
            dia_aux = 31 - aux->inicio.dia;
            temp.dia = 7 - dia_aux;
            temp.mes = 1;
            temp.ano = aux->inicio.ano + 1;
        }
    } else {
        temp.dia = aux->inicio.dia + 7;
        temp.mes = aux->inicio.mes;
        temp.ano = aux->inicio.ano;
    }
    return temp;
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

int verifica_cliente_banido(int nif) {
    FILE *f = fopen("clientes.dat", "rb");
    Banido aux;

    if (f == NULL)
        printf("Erro a abrir ficheiro %s", f);

    while (fread(&aux, sizeof (aux), 1, f) == 1) {
        if (aux.nif == nif) {
            printf("Cliente já banido!\n");
            return -1; //CLIENTE BANIDO, JÁ NAO PODE CRIAR "CONTA"!
        }
    }
    return 0; //CLIENTE PODE CRIAR CONTA!
}

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

void escreve_clientes_banidos(Banido ban) {
    FILE *f = fopen("clientes.dat", "ab+");

    if (f == NULL)
        printf("Erro a abrir ficheiro %s\n", f);

    fwrite(&ban, sizeof (ban), 1, f);
    fclose(f);
}

void mostra_clientes_banidos() {
    FILE *f = fopen("clientes.dat", "rb");
    Banido aux;

    if (f == NULL) {
        printf("erro no acesso ao ficheiro!\n");
        return;
    }

    if (verifica_ficheiro(f) == 1)
        printf("Ficheiro %s vazio!\n", f);

    while (fread(&aux, sizeof (aux), 1, f) == 1) {
        printf("NIF do Cliente: %d\nMotivo: %s\n", aux.nif, aux.motivo);
    }
    fclose(f);
}

void mostrar_info(Cliente *c) {
    Cliente *aux = c;

    if (aux == NULL) {
        printf("Nao existem clientes activos!\n");
        return;
    } else {
        while (aux) { //se a lista não estiver vazia
            printf("NIF: %d\tNo. Alugueres: %d\tNome: %s\n", aux->nif, aux->n_alugueres, aux->nome);
            Aluguer *aux1 = aux->lista;
            if (aux1 != NULL) {
                while (aux1) {
                    if (aux1->fim.dia == 0) {
                        printf("ID da Guitarra: %d\tEstado: %d\tData Inicial de Aluguer: %d/%d/%d\tData Final de Aluguer: A decorrer...\n",
                                aux1->id, aux1->estado, aux1->inicio.dia, aux1->inicio.mes, aux1->inicio.ano);
                    } else {
                        printf("ID da Guitarra: %d\tEstado: %d\tData Inicial de Aluguer: %d/%d/%d\tData Final de Aluguer: %d/%d/%d\n",
                                aux1->id, aux1->estado, aux1->inicio.dia, aux1->inicio.mes, aux1->inicio.ano, aux1->fim.dia, aux1->fim.mes, aux1->fim.ano);
                    }
                    aux1 = aux1->prox;
                }
            }
            printf("\n");
            aux = aux->prox;
        }
    }
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

float multa_guitarra(Guitarra *g, int id, int total) {
    Guitarra *aux = g;
    for (int i = 0; i < total; i++) {
        if ((g + i)->id == id) {
            return (g + i)->preco;
        }
    }
}

int verifica_atraso(Guitarra* g, int total, Aluguer *aux, Data temp) { //CONSIDERO QUE TODOS OS MESES DO ANO TêM 31 DIAS!
    int dias = 0, auxiliar, pagamento;
    Data temp_aux;
    temp_aux = verifica_data(aux); //data final que supostamente o cliente terá que entregar a guitarra (tem 7 dias)
    float guitarra_preco = multa_guitarra(g, aux->id, total);

    if ((temp.mes == aux->inicio.mes) && (temp.ano == aux->inicio.ano)) {
        if (temp.dia <= temp_aux.dia) {
            pagamento = abs(temp_aux.dia - aux->inicio.dia) * guitarra_preco;
            return pagamento;
        } else {
            pagamento = (abs(temp.dia - aux->inicio.dia) * 10) + (abs(temp.dia - aux->inicio.dia) * guitarra_preco);
            return pagamento;
        }
    }

    if (temp.ano == temp_aux.ano && temp.mes > temp_aux.mes) {
        auxiliar = temp_aux.dia;
        while (auxiliar != 31) {
            dias++; //CONTAR OS DIAS DESDE O DIA FINAL DE ENTREGA ATÉ AO FINAL DO MES
            auxiliar++;
        }
        dias = dias + abs(1 - temp.dia); //DIAS EFECTIVOS DESDE O DIA FINAL DE ENTREGA ATE AO DIA ACTUAL
        if (dias > 20) {
            return -1;
        } else {
            pagamento = (dias * 10) + (dias * guitarra_preco);
            return pagamento;
        }
    }

    if ((temp.ano > temp_aux.ano && temp_aux.mes == temp.mes) || (temp.ano > temp_aux.ano && temp_aux.mes != temp.mes))
        return -1; //BANIDO

    if ((temp.dia == temp_aux.dia && temp.ano > temp_aux.ano) || (temp.dia == temp_aux.dia && temp.mes > temp_aux.mes))
        return -1;
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