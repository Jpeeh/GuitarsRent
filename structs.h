/* 
 * File:   structs.h
 * Author: Joao
 *
 * Created on 30 de Maio de 2018, 11:28
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int id, valor, estado;
    char nome[100];
    float preco;
} Guitarra;

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct aluguer {
    int id, estado;
    Data inicio, fim;
    struct aluguer *prox; //ponteiro para o próximo nó da lista de alugures
} Aluguer;

typedef struct cliente {
    char nome[100];
    int nif,cont_estado,n_alugueres;
    struct cliente *prox; //ponteiro para o proximo nó da lista
    Aluguer *lista; //ponteiro para a lista dos alugueres
    //cont_estado -> contador para nº de guitarras danificadas
    //n_alugures -> contador para o nº de alugueres
}Cliente;

typedef struct banido {
    char motivo[100]; 
    int nif;
}Banido;

#endif /* STRUCTS_H */