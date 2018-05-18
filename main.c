#include "funcoes.h"

int main(int argc, char **argv) {    
    Cliente *lista = NULL;
    Aluguer *lista_aluguer = NULL;
    
    lista = carrega_info_cliente(lista, lista_aluguer);
    mostrar_info(lista); 
    //lista = adiciona_cliente(lista); 
    adiciona_aluguer(lista,"joao pedro", 0, 1);
        
    return (EXIT_SUCCESS);
}
