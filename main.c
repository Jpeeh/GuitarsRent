#include "funcoes.h"

int main(int argc, char **argv) {
    Cliente *lista = NULL;
    Aluguer *lista_aluguer = NULL;

    lista = carrega_info_cliente(lista, lista_aluguer);
    mostrar_info(lista);
    conclui_aluguer(lista, "joao pedro");


    return (EXIT_SUCCESS);
}
