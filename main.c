#include "funcoes.h"

int main(int argc, char **argv) {
    Cliente *lista = NULL;
    Aluguer *lista_aluguer = NULL;
    Guitarra *g = NULL;
    int tam = 0;
    
    g = carregaVetor(g, &tam);
    lista = carrega_info_cliente(lista, lista_aluguer);

    mostrar_info(lista);

    mostra_guitarras(g, &tam);
    mostra_guitarras_alugadas(lista, g, &tam);

    return (EXIT_SUCCESS);
}
