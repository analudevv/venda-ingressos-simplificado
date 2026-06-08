#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "functions.h"

typedef struct {
    int ocupado;
    int idade;
    int ehMeia;
    char formaPagamento[30];
    float valorPago;
} Assento;

Assento sessoes[2][5][6];

void inicializarAssentos(){
    for(int sessao = 0; sessao < 2; sessao++){
        for(int fila = 0; fila < 5; fila++){
            for(int cadeira = 0; cadeira < 6; cadeira++){
                sessoes[sessao][fila][cadeira].ocupado = 0;
                sessoes[sessao][fila][cadeira].idade = 0;
                sessoes[sessao][fila][cadeira].ehMeia = 0;
                sessoes[sessao][fila][cadeira].formaPagamento[0] = '\0';
                sessoes[sessao][fila][cadeira].valorPago = 0.0f;
            }
        }
    }
}

void mostrarAssentos(int sessao)
{
    printf("\n========= T E L A / P A L C O ======== \n\n");
    printf("         1   2   3   4   5   6\n");

    for(int fila = 0; fila < 5; fila++)
    {
        printf("     %c ", 'A' + fila);

        for(int cadeira = 0; cadeira < 6; cadeira++)
        {
            if(sessoes[sessao][fila][cadeira].ocupado == 0)
            {
                printf(" [ ]");
            }
            else
            {
                printf(" [X]");
            }
        }
        printf("\n");
    }
    printf("\n     Legenda: [ ] Livre  [X] Ocupado\n\n");
}

void mostrarSessoes(void){
    int session;

    printf("\n===========SESSÕES DISPONÍVEIS===========\n");
    printf("1 - Mestres do Universo\n");
    printf("2 - Interestelar\n");
    printf("Informe o número da sessão: ");
    scanf("%d", &session);
    getchar();

    //Validação da sessão escolhida
    if(session != 1 && session != 2){
        printf("\nSessao invalida.\n");
        return;
    }

    if(session==1){
        mostrarAssentos(0);
    }else if(session==2){
        mostrarAssentos(1);
    }else{
        printf("\nSessão inválida.\n");
    }
}

void comprarIngresso(void){
    int session;
    printf("\n===========COMPRAR INGRESSO===========\n");
    printf("Sessões disponíveis:\n");
    printf("1 - Mestres do Universo\n");
    printf("2 - Interestelar\n");
    printf("Informe o número da sessão: ");
    scanf("%d", &session);
    getchar();

    if(session != 1 && session != 2){
        printf("\nSessao invalida.\n");
        return;
    }

    int sessaoIdx = session - 1;

    mostrarAssentos(sessaoIdx);

    char filaChar;
    int cadeiraNum;
    int filaIdx, cadeiraIdx;
    int valido = 0;

    // Escolha e validação do assento
    do {
        printf("Digite a fila (A-E) e o número da cadeira (1-6) (Ex: B 4): ");
        scanf(" %c %d", &filaChar, &cadeiraNum);
        getchar();

        // Converte a letra da fila para maiúsculo se necessário
        if (filaChar >= 'a' && filaChar <= 'e') {
            filaChar = filaChar - 'a' + 'A';
        }

        // Verifica se a fila é válida
        if (filaChar >= 'A' && filaChar <= 'E') {
            filaIdx = filaChar - 'A';
        } else {
            printf("\nFila inválida. Escolha de A a E.\n");
            continue;
        }

        // Verifica se a cadeira é válida
        if (cadeiraNum >= 1 && cadeiraNum <= 6) {
            cadeiraIdx = cadeiraNum - 1;
        } else {
            printf("\nCadeira inválida. Escolha de 1 a 6.\n");
            continue;
        }

        // Verifica se o assento já está ocupado
        if (sessoes[sessaoIdx][filaIdx][cadeiraIdx].ocupado == 1) {
            printf("\nEsta cadeira já está ocupada! Escolha outra cadeira.\n");
            mostrarAssentos(sessaoIdx);
        } else {
            valido = 1;
        }
    } while (!valido);

    // Solicita idade
    int idade;
    printf("\nDigite a idade do cliente: ");
    scanf("%d", &idade);
    getchar();

    // Determina se paga meia-entrada (menor ou igual a 15 anos)
    int ehMeia = (idade <= 15);
    float valorTicket = ehMeia ? 15.00f : 30.00f;

    printf("Valor do ingresso: R$ %.2f (%s)\n\n", valorTicket, ehMeia ? "Meia-entrada" : "Ingresso normal");

    int opcaoPagamento;
    char forma[30] = "";

    // Processamento do pagamento
    do {
        printf("===========FORMA DE PAGAMENTO===========\n");
        printf("1 - Pix\n");
        printf("2 - Cartão de Crédito\n");
        printf("3 - Cartão de Débito\n");
        printf("4 - Dinheiro\n");
        printf("Opção: ");
        scanf("%d", &opcaoPagamento);
        getchar();

        switch (opcaoPagamento) {
            case 1:
                strcpy(forma, "Pix");
                printf("\nGerando chave Pix copia e cola...\n");
                printf("Chave Pix: 123.456.789-00-ingresso-c\n");
                printf("Confirmando pagamento...\n");
                printf(">>> Pagamento de R$ %.2f confirmado via Pix!\n\n", valorTicket);
                break;
            case 2:
                strcpy(forma, "Cartão de Crédito");
                printf("\nAproxime ou insira o cartão...\n");
                printf("Processando...\n");
                printf(">>> Transação autorizada! Valor: R$ %.2f\n\n", valorTicket);
                break;
            case 3:
                strcpy(forma, "Cartão de Débito");
                printf("\nAproxime ou insira o cartão...\n");
                printf("Digite a senha do cartão: ****\n");
                printf("Processando...\n");
                printf(">>> Transação autorizada! Valor: R$ %.2f\n\n", valorTicket);
                break;
            case 4:
                strcpy(forma, "Dinheiro");
                printf("\nDinheiro recebido no valor de R$ %.2f!\n", valorTicket);
                printf(">>> Pagamento confirmado!\n\n");
                break;
            default:
                printf("\nOpção de pagamento inválida. Tente novamente.\n");
                break;
        }
    } while (opcaoPagamento < 1 || opcaoPagamento > 4);

    // Salva as informações do ingresso comprado
    sessoes[sessaoIdx][filaIdx][cadeiraIdx].ocupado = 1;
    sessoes[sessaoIdx][filaIdx][cadeiraIdx].idade = idade;
    sessoes[sessaoIdx][filaIdx][cadeiraIdx].ehMeia = ehMeia;
    strncpy(sessoes[sessaoIdx][filaIdx][cadeiraIdx].formaPagamento, forma,
    sizeof(sessoes[sessaoIdx][filaIdx][cadeiraIdx].formaPagamento) - 1);
    sessoes[sessaoIdx][filaIdx][cadeiraIdx].formaPagamento[sizeof(sessoes[sessaoIdx][filaIdx][cadeiraIdx].formaPagamento) - 1] = '\0';
    sessoes[sessaoIdx][filaIdx][cadeiraIdx].valorPago = valorTicket;

    // Nota fiscal exibida no terminal
    printf("========================================\n");
    printf("            NOTA FISCAL\n");
    printf("----------------------------------------\n");
    printf("Sessao:             %d\n", session);
    printf("Assento:            %c-%d\n", 'A' + filaIdx, cadeiraNum);
    printf("Tipo:               %s\n", ehMeia ? "Meia-entrada" : "Ingresso normal");
    printf("Forma de Pagamento: %s\n", forma);
    printf("----------------------------------------\n");
    printf("VALOR TOTAL:        R$ %.2f\n", valorTicket);
    printf("========================================\n");
    printf("  Obrigado pela preferencia! Bom filme!\n");
    printf("========================================\n");
}

void cancelarCompra(void){
    int session;
    printf("\n===========CANCELAR COMPRA===========\n");
    printf("Sessões disponíveis:\n");
    printf("1- Mestres do Universo\n");
    printf("2- Interestelar\n");
    printf("Informe o número da sessão que deseja cancelar: ");

    // Escolha da sessão para cancelar
    scanf("%d", &session);
    getchar();

    if(session != 1 && session != 2){
        printf("\nSessao invalida.\n");
        return;
    }

    int sessaoIdx = session - 1;

    char filaChar;
    int cadeiraNum;
    int filaIdx, cadeiraIdx;

    printf("\nDigite a fila (A-E) e o número da cadeira (1-6) para cancelar (Ex: B 4): ");
    scanf(" %c %d", &filaChar, &cadeiraNum);
    getchar();

    // Converte a fila para maiúsculo
    if (filaChar >= 'a' && filaChar <= 'e') {
        filaChar = filaChar - 'a' + 'A';
    }

    // Validação da fila e cadeira
    if (filaChar >= 'A' && filaChar <= 'E') {
        filaIdx = filaChar - 'A';
    } else {
        printf("\nFila inválida.\n");
        return;
    }

    if (cadeiraNum >= 1 && cadeiraNum <= 6) {
        cadeiraIdx = cadeiraNum - 1;
    } else {
        printf("\nCadeira inválida.\n");
        return;
    }

    // Cancela a reserva caso esteja ocupado
    if (sessoes[sessaoIdx][filaIdx][cadeiraIdx].ocupado == 0) {
        printf("\nEste assento já está livre!\n");
    } else {
        float valorReembolso = sessoes[sessaoIdx][filaIdx][cadeiraIdx].valorPago;
        char formaPagamento[30];
        strcpy(formaPagamento, sessoes[sessaoIdx][filaIdx][cadeiraIdx].formaPagamento);

        sessoes[sessaoIdx][filaIdx][cadeiraIdx].ocupado = 0;
        sessoes[sessaoIdx][filaIdx][cadeiraIdx].idade = 0;
        sessoes[sessaoIdx][filaIdx][cadeiraIdx].ehMeia = 0;
        sessoes[sessaoIdx][filaIdx][cadeiraIdx].formaPagamento[0] = '\0';
        sessoes[sessaoIdx][filaIdx][cadeiraIdx].valorPago = 0.0f;

        printf("===========COMPRA CANCELADA COM SUCESSO===========\n");
        printf("Assento Cancelado: %c-%d\n", 'A' + filaIdx, cadeiraNum);
        printf("Valor Reembolsado: R$ %.2f\n", valorReembolso);
        printf("Forma de Retorno: %s\n", formaPagamento);
    }
}

void relatorioVendas(void){
    printf("\n============== RELATORIO DE VENDAS ==============\n");
    int totalVendidos = 0;
    int totalMeia = 0;
    int totalNormal = 0;
    float totalFaturamento = 0.0f;

    int vendidosPorSessao[2] = {0, 0};
    int meiaPorSessao[2] = {0, 0};
    int normalPorSessao[2] = {0, 0};
    float faturamentoPorSessao[2] = {0.0f, 0.0f};

    // Percorre todas as sessões e assentos
    for (int sessao = 0; sessao < 2; sessao++) {
        for (int fila = 0; fila < 5; fila++) {
            for (int cadeira = 0; cadeira < 6; cadeira++) {
                if (sessoes[sessao][fila][cadeira].ocupado == 1) {
                    vendidosPorSessao[sessao]++;
                    totalVendidos++;
                    faturamentoPorSessao[sessao] += sessoes[sessao][fila][cadeira].valorPago;
                    totalFaturamento += sessoes[sessao][fila][cadeira].valorPago;
                    if (sessoes[sessao][fila][cadeira].ehMeia) {
                        meiaPorSessao[sessao]++;
                        totalMeia++;
                    } else {
                        normalPorSessao[sessao]++;
                        totalNormal++;
                    }
                }
            }
        }
    }

    // Relatório por sessão
    int totalLugares = 5 * 6; // 30 lugares por sessão
    for (int i = 0; i < 2; i++) {
        int livres = totalLugares - vendidosPorSessao[i];
        printf("\n----- Sessão %d -----\n", i + 1);
        printf("Ingressos vendidos: %d\n", vendidosPorSessao[i]);
        printf("Meia-entrada: %d\n", meiaPorSessao[i]);
        printf("Ingresso normal: %d\n", normalPorSessao[i]);
        printf("Lugares livres: %d\n", livres);
        printf("Faturamento: R$ %.2f\n", faturamentoPorSessao[i]);
    }

    // Resumo geral
    printf("\n===========RESUMO GERAL===========\n");
    printf("Total de ingressos vendidos: %d\n", totalVendidos);
    printf("Meia-entrada: %d\n", totalMeia);
    printf("Ingresso normal: %d\n", totalNormal);
    printf("Faturamento total: R$ %.2f\n", totalFaturamento);
    printf("\nSessão mais procurada: \n");
    if (vendidosPorSessao[0] == 0 && vendidosPorSessao[1] == 0) {
        printf("Nenhum ingresso vendido ainda.\n");
    } else if (vendidosPorSessao[0] > vendidosPorSessao[1]) {
        printf("Sessão 1 - Mestres do Universo com %d ingressos vendidos\n", vendidosPorSessao[0]);
    } else if (vendidosPorSessao[1] > vendidosPorSessao[0]) {
        printf("Sessão 2 - Interestelar com %d ingressos vendidos\n", vendidosPorSessao[1]);
    } else {
        printf("Empate! Ambas as sessões com %d ingressos vendidos\n", vendidosPorSessao[0]);
    }

}

void gerenciarReinicializacao(){
    printf("===========REINICIAR SISTEMA===========\n");
    char senha[50];
    printf("Digite a senha de administrador: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0'; // Remove o caractere \n
    if (strcmp(senha, "admin") == 0) {
        inicializarAssentos();
        printf("\nSistema reiniciado com sucesso! Todos os assentos estao livres.\n");
    } else {
        printf("\nSenha incorreta! Acesso negado.\n");
    }
}

void aguardarEnter() {
    printf("\nPressione ENTER para voltar ao menu principal...");
    getchar();
    system("clear");
}