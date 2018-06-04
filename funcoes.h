/* 
 * File:   funcoes.h
 * Author: Joao
 *
 * Created on 26 de Abril de 2018, 17:45
 */

#ifndef FUNCOES_H
#define FUNCOES_H

#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//CLIENTES
Cliente *adiciona_cliente(Cliente *c);
Cliente *remove_cliente_lista(Cliente *c, int nif);
Cliente *carrega_info_cliente(Cliente *lista, Aluguer *lista_aluguer);
void adiciona_aluguer(Cliente *a, char *nome, int id, int estado);
void remove_cliente_ficheiro(Cliente *c);
int verifica_cliente(int nif);
void escreve_clientes_banidos(Cliente *aux);

//ALUGUERES
Aluguer *carrega_info_aluguer(Aluguer *lista_aluguer,FILE *f);
void alugueres_activos(Cliente *c);
void conclui_aluguer(Cliente *c, char *nome);

//GUITARRAS
Guitarra *criaVetor(Guitarra *g);
Guitarra *carregaVetor(Guitarra *g, int *tam);
Guitarra *adiciona_guitarra(Guitarra *g, int *total);
void mostra_guitarras(Guitarra *g, int *tam);
void mostrar_guitarras_alugadas(Guitarra *g, int *tam);
void escreve_ficheiro_guitarras(Guitarra g[], int *total);

//OUTROS
void escreve_ficheiro(Cliente *a);
void mostrar_info(Cliente *c);
int verifica_multa(Aluguer *aux, Data temp);
Data verifica_data(Aluguer *aux);

#endif /* FUNCOES_H */

