#include <stdio.h>
#include "functions.h"

int main(){
    int option;
    inicializarAssentos();

    do{

        printf("\n=================================================\n");
        printf("          SISTEMA DE VENDA DE INGRESSOS          \n");
        printf("=================================================\n");
        printf("  1 | Mostrar sessões e assentos\n");
        printf("  2 | Comprar ingresso\n");
        printf("  3 | Cancelar compra\n");
        printf("  4 | Relatório de vendas\n");
        printf("  5 | Reiniciar assentos\n");
        printf("  0 | Sair do sistema\n");
        printf("=================================================\n");
        printf("Opção: ");

        scanf("%d", &option);
        getchar();
        
        switch (option)
        {
            case 1:
                mostrarSessoes();
                aguardarEnter();
                break;
            case 2:
                comprarIngresso();
                aguardarEnter();
                break;
            case 3:
                cancelarCompra();
                aguardarEnter();
                break;
            case 4:
                relatorioVendas();
                aguardarEnter();
                break;
            case 5:
                gerenciarReinicializacao();
                aguardarEnter();
                break;
            case 0:
                break;
            default:
                printf("\nEssa opção não existe, tente novamente.\n");
                aguardarEnter();
                break;
        }
        
    }
    while(option!=0);

}
