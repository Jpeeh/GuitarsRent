#ifndef CLIENTES_ALUGUERES_H
#define	CLIENTES_ALUGUERES_H
#include "structs.h"

//CLIENTES
Cliente *adiciona_cliente(Cliente *c);
Cliente *remove_cliente_lista(Cliente *c, int nif);
Cliente *carrega_info_cliente(Cliente *lista, Aluguer *lista_aluguer);
void remove_cliente_ficheiro(Cliente *c);

//ALUGUERES
void adiciona_aluguer(Cliente *a, Guitarra *g, int total, int nif, int id);
Aluguer *carrega_info_aluguer(Aluguer *lista_aluguer, FILE *f);
void alugueres_activos(Cliente *c);
void conclui_aluguer(Cliente *c,Guitarra *g, int total, int nif);

#endif	/* CLIENTES_ALUGUERES_H */