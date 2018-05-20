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
Cliente *remove_cliente_lista(Cliente *c, char *nome);
Cliente *carrega_info_cliente(Cliente *lista, Aluguer *lista_aluguer);
void adiciona_aluguer(Cliente *a, char *nome, int id, int estado);

//ALUGUERES
Aluguer *carrega_info_aluguer(Aluguer *lista_aluguer,FILE *f);
void alugueres_activos(Cliente *c);

//OUTROS
void escreve_ficheiro(Cliente *a);
void mostrar_info(Cliente *c);
int verifica_multa(Aluguer *aux, Data temp);
Data verifica_data(Aluguer *aux);

//GUITARRAS
void adiciona_guitarra(Guitarra *g, int *total);
#endif /* FUNCOES_H */

