#include "funcoes.h"

int main(int argc, char **argv) {
    Cliente *lista = NULL;
    Aluguer *lista_aluguer = NULL;
    Guitarra *g = NULL;
    int tam = 0, i, j, nif, id, id_historico, nif_aluguer;

    g = carregaVetor(g, &tam);
    lista = carrega_info_cliente(lista, lista_aluguer);

    do {
        printf(" | ALUGUER DE GUITARRAS |\n");
        i = menu();
        system("cls");
        switch (i) {
            case 1:
                do {
                    j = submenu1();
                    system("cls");
                    switch (j) {
                        case 1: lista = adiciona_cliente(lista);
                            break;
                        case 2:
                            printf("NIF do Cliente a remove: ");
                            scanf(" %d", &nif);
                            lista = remove_cliente_lista(lista, nif);
                            remove_cliente_ficheiro(lista);
                            mostrar_info(lista);
                            break;
                        case 3:puts("Falta Funcao");
                            break;
                        case 4:
                            mostrar_info(lista);
                            break;
                        case 5:mostra_clientes_banidos();
                            break;
                        case 6:break;
                    }
                } while (j != 6);
                break;
            case 2:
                do {
                    j = submenu2();
                    system("cls");
                    switch (j) {
                        case 1: g = adiciona_guitarra(g, &tam);
                            escreve_ficheiro_guitarras(g, tam);
                            break;
                        case 2:
                            printf("ID da Guitarra a consultar: ");
                            scanf(" %d", &id_historico);
                            historico_guitarras(lista, id_historico);
                            break;
                        case 3: mostra_guitarras(g, tam);
                            break;
                        case 4: mostrar_guitarras_alugadas(lista, g, tam);
                            break;
                        case 5:break;
                    }
                } while (j != 5);
                break;
            case 3:
                do {
                    j = submenu3();
                    system("cls");
                    switch (j) {
                        case 1: printf("NIF do Cliente: ");
                            scanf(" %d", &nif_aluguer);
                            printf("ID da Guitarra: ");
                            scanf(" %d", &id);
                            adiciona_aluguer(lista, nif_aluguer, id);
                            break;
                        case 2:printf("NIF do cliente: ");
                            scanf(" %d", &nif);
                            conclui_aluguer(lista, nif);
                            break;
                        case 3:
                            alugueres_activos(lista);
                            break;
                        case 4:break;
                    }
                } while (j != 4);
                break;
        }
    } while (i != 4);
    return (EXIT_SUCCESS);
}