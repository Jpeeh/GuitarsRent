/* 
 * File:   outros.h
 * Author: Joao
 *
 * Created on 13 de Junho de 2018, 15:30
 */
#include "structs.h"
#ifndef OUTROS_H
#define OUTROS_H

//OUTROS
void mostrar_info(Cliente *c);

void escreve_clientes_banidos(Banido ban);

void mostra_clientes_banidos();

void escreve_ficheiro(Cliente *a);

int verifica_cliente(int nif);

int verifica_nif(int nif);

Data verifica_data(Aluguer *aux);

int verifica_cliente_banido(int nif);

int verifica_atraso(Guitarra *g, int total, Aluguer *aux, Data temp);

int verifica_ficheiro(FILE *f);
#endif /* FUNCOES_H */

