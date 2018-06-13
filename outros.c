#include "outros.h"
#include "guitarras.h"

//FUNÇÕES PARA MOSTRAR OU ESCREVER NO FICHEIRO!
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

//FUNÇÕES DE VERIFICAÇÃO
int verifica_cliente(int nif) {
    FILE *f = fopen("clientes.txt", "rt");
    Cliente aux;

    if (f == NULL)
        printf("erro a abrir ficheiro %s", f);

    while (fscanf(f, " %d %d %99[^\n]s", &aux.nif, &aux.n_alugueres, &aux.nome) == 3) {
        if (nif == aux.nif) {
            fclose(f);
            printf("Cliente ja existente!\n");
            return 0;
        }
    }
    fclose(f);
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

int verifica_ficheiro(FILE *f) { //VERIFICA SE O FICHEIRO ESTA VAZIO
    int size;
    fseek(f, 0, SEEK_END);

    size = ftell(f);
    if (size == 0)
        return 1;

    rewind(f);
    return 0;
}