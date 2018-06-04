#include "funcoes.h"

int main(int argc, char **argv) {
    Cliente *lista = NULL;
    Aluguer *lista_aluguer = NULL;
    Guitarra *g = NULL;
    int tam = 0;
    g = carregaVetor(g,&tam); 
    mostra_guitarras(g, &tam);

    return (EXIT_SUCCESS);
}
