#include "menus.h"
#include <stdio.h>

int menu(){
    int op;
    
    printf("\n1 - Clientes");
    printf("\n2 - Guitarras");
    printf("\n3 - Aluguer");
    printf("\n4 - Terminar");
    do{
        printf("\nOpcao: ");
        scanf("%d",&op);
    }while(op<1 || op>4);
    return op;
}

int submenu1(){
    int op;
    
    printf("\n1 - Adicionar Cliente");
    printf("\n2 - Remover Cliente(Ativo)");
    printf("\n3 - Lista de Clientes Ativos");
    printf("\n4 - Lista de Clientes Banidos");
    printf("\n5 - Voltar Atras");
    do{
        printf("\nOpcao: ");
        scanf("%d",&op);
    }while(op<1 || op>5);
    return op;
}

int submenu2(){
    int op;
    
    printf("\n1 - Adicionar Guitarra");
    printf("\n2 - Historico de Guitarras");
    printf("\n3 - Listagem de Guitarras");
    printf("\n4 - Listagem de Guitarras Alugadas");
    printf("\n5 - Voltar Atras");
    do{
        printf("\nOpcao: ");
        scanf("%d",&op);
    }while(op<1 || op>5);
    return op;
}

int submenu3(){
    int op;
    
    printf("\n1 - Criar Aluguer");
    printf("\n2 - Concluir Aluguer");
    printf("\n3 - Lista de Alugueres");
    printf("\n4 - Voltar Atras");
    do{
        printf("\nOpcao: ");
        scanf("%d",&op);
    }while(op<1 || op>4);
    return op;
}
