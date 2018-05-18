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

Cliente *adiciona_cliente(Cliente *c);
Cliente *remove_cliente_lista(Cliente *c, char *nome);
void remove_cliente_ficheiro(Cliente *c);
Aluguer *carrega_info_aluguer(Aluguer *lista_aluguer,FILE *f);
Cliente *carrega_info_cliente(Cliente *lista, Aluguer *lista_aluguer);
void adiciona_aluguer(Cliente *a, char *nome, int id, int estado);
void adiciona_guitarra(Guitarra *g, int *total);
void mostrar_info(Cliente *c);

#endif /* FUNCOES_H */

