/* 
 * File:   cliente.h
 * Author: Joao
 *
 * Created on 23 de Abril de 2017, 04:53
 */
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
    int id;
    Data inicio;
    Data fim;
    int estado;
    struct aluguer *prox;
} Aluguer;

typedef struct cliente {
    char nome[100];
    int nif;
    int cont_estado; //contador para nº de guitarras danificadas
    int n_alugueres; //contador para o nº de alugueres
    struct cliente *prox; //ponteiro para o proximo nó da lista
    Aluguer *lista; //ponteiro para a lista dos alugueres
}Cliente;

#endif /* STRUCTS_H */

