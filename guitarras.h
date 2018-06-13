/* 
 * File:   guitarras.h
 * Author: Joao
 *
 * Created on 13 de Junho de 2018, 15:28
 */
#include "structs.h"
#ifndef GUITARRAS_H
#define	GUITARRAS_H

//GUITARRAS
Guitarra *carregaVetor(Guitarra *g, int *tam);

void escreve_ficheiro_guitarras(Guitarra *g, int total);

Guitarra *adiciona_guitarra(Guitarra *g, int *total);

void mostra_guitarras(Guitarra *g, int tam);

void mostrar_guitarras_alugadas(Cliente *c, Guitarra *g, int tam);

void historico_guitarras(Cliente *c, int id);

int verifica_guitarras(Guitarra *g, int total, int id);

int verifica_guitarra_danificada(Guitarra *g, int total, int id);

float multa_guitarra(Guitarra *g, int id, int total);

Guitarra *actualiza_estado_guitarra(Guitarra *g, int total, int estado, int id);
#endif	/* GUITARRAS_H */

