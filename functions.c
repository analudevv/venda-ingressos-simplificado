#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
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
    // Cria a pasta vendas caso não exista
    mkdir("vendas", 0777);

    // Apaga os arquivos de venda anteriores para reiniciar os assentos no disco
    system("rm -f vendas/*.txt");

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
    printf("   ========= T E L A / P A L C O ======== \n\n");
    printf("          1   2   3   4   5   6\n");

    for(int fila = 0; fila < 5; fila++)
    {
        printf("     %c |", 'A' + fila);

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
        printf(" |\n");
    }
    printf("       +-----------------------+\n");
    printf("       Legenda: [ ] Livre  [X] Ocupado\n\n");
}

void mostrarSessoes(void){
    int session;

    printf("\n=================================================\n");
    printf("               SESSÕES DISPONÍVEIS               \n");
    printf("=================================================\n");
    printf("  1 | Sessão 1\n");
    printf("  2 | Sessão 2\n");
    printf("=================================================\n");
    scanf("%d", &session);
    getchar();

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
    printf("\n=================================================\n");
    printf("                COMPRAR INGRESSO                 \n");
    printf("=================================================\n");
    printf("Sessões disponíveis:\n");
    printf("  1 | Sessão 1\n");
    printf("  2 | Sessão 2\n");
    printf("=================================================\n");
    
    scanf("%d", &session);
    // limpar o ENTER
    getchar();

    int sessaoIdx = session - 1;

    printf("\n>>> Assentos para a Sessão %d <<<\n", session);
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

    printf("\n-------------------------------------------------\n");
    printf("Valor do ingresso: R$ %.2f (%s)\n", valorTicket, ehMeia ? "Meia-entrada" : "Ingresso normal");
    printf("-------------------------------------------------\n");

    int opcaoPagamento;
    char forma[30] = "";

    // Processamento do pagamento
    do {
        printf("\n=================================================\n");
        printf("               FORMA DE PAGAMENTO                \n");
        printf("=================================================\n");
        printf("  1 | Pix\n");
        printf("  2 | Cartão de Crédito\n");
        printf("  3 | Cartão de Débito\n");
        printf("  4 | Dinheiro\n");
        printf("=================================================\n");
        printf("Opção: ");
        scanf("%d", &opcaoPagamento);
        getchar();

        switch (opcaoPagamento) {
            case 1:
                strcpy(forma, "Pix");
                printf("\nGerando chave Pix copia e cola...\n");
                printf("Chave Pix: 123.456.789-00-ingresso-c\n");
                printf("Confirmando pagamento...\n");
                printf(">>> Pagamento de R$ %.2f confirmado via Pix!\n", valorTicket);
                break;
            case 2:
                strcpy(forma, "Cartão de Crédito");
                printf("\nAproxime ou insira o cartão...\n");
                printf("Processando...\n");
                printf(">>> Transação autorizada! Valor: R$ %.2f\n", valorTicket);
                break;
            case 3:
                strcpy(forma, "Cartão de Débito");
                printf("\nAproxime ou insira o cartão...\n");
                printf("Digite a senha do cartão: ****\n");
                printf("Processando...\n");
                printf(">>> Transação autorizada! Valor: R$ %.2f\n", valorTicket);
                break;
            case 4:
                strcpy(forma, "Dinheiro");
                printf("\nDinheiro recebido no valor de R$ %.2f!\n", valorTicket);
                printf(">>> Pagamento confirmado!\n");
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

    printf("\n=================================================\n");
    printf("          COMPRA REALIZADA COM SUCESSO!          \n");
    printf("=================================================\n");
    printf("  Sessão             : %d\n", session);
    printf("  Assento            : %c-%d\n", 'A' + filaIdx, cadeiraNum);
    printf("  Idade              : %d anos\n", idade);
    printf("  Tipo               : %s\n", ehMeia ? "Meia-entrada" : "Ingresso normal");
    printf("  Forma de Pagamento : %s\n", forma);
    printf("  Valor Pago         : R$ %.2f\n", valorTicket);
    printf("=================================================\n");

    // Salva as informações do ingresso em um arquivo .txt na pasta "vendas"
    char nomeArquivo[50];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "vendas/%c%d.txt", tolower(filaChar), cadeiraNum);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "=========================================\n");
        fprintf(arquivo, "            CINESTAR CINEMAS             \n");
        fprintf(arquivo, "          CNPJ: 12.345.678/0001-90       \n");
        fprintf(arquivo, "=========================================\n");
        fprintf(arquivo, "             CUPOM FISCAL                \n");
        fprintf(arquivo, "-----------------------------------------\n");
        fprintf(arquivo, "Sessão: %d\n", session);
        fprintf(arquivo, "Assento: %c-%d\n", 'A' + filaIdx, cadeiraNum);
        fprintf(arquivo, "-----------------------------------------\n");
        fprintf(arquivo, "Idade: %d anos\n", idade);
        fprintf(arquivo, "Tipo: %s\n", ehMeia ? "Meia-entrada" : "Ingresso normal");
        fprintf(arquivo, "-----------------------------------------\n");
        fprintf(arquivo, "Forma de Pagamento: %s\n", forma);
        fprintf(arquivo, "VALOR TOTAL: R$ %.2f\n", valorTicket);
        fprintf(arquivo, "=========================================\n");
        fprintf(arquivo, "   Obrigado pela preferência! Bom filme! \n");
        fprintf(arquivo, "=========================================\n");
        fclose(arquivo);
        printf("Informações salvas em: %s\n", nomeArquivo);
    } else {
        printf("Erro ao salvar arquivo de registro de venda em %s!\n", nomeArquivo);
    }
}

void cancelarCompra(void){
    int session;
    printf("\n=================================================\n");
    printf("                 CANCELAR COMPRA                 \n");
    printf("=================================================\n");
    printf("Sessões disponíveis:\n");
    printf("  1 | Sessão 1\n");
    printf("  2 | Sessão 2\n");
    printf("=================================================\n");

    // Escolha da sessão para cancelar
    scanf("%d", &session);
    getchar();

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

        // Remove o arquivo .txt correspondente da pasta vendas
        char nomeArquivo[50];
        snprintf(nomeArquivo, sizeof(nomeArquivo), "vendas/%c%d.txt", tolower(filaChar), cadeiraNum);
        remove(nomeArquivo);

        printf("\n=================================================\n");
        printf("         COMPRA CANCELADA COM SUCESSO!           \n");
        printf("=================================================\n");
        printf("  Assento Cancelado : %c-%d\n", 'A' + filaIdx, cadeiraNum);
        printf("  Valor Reembolsado : R$ %.2f\n", valorReembolso);
        printf("  Forma de Retorno  : %s\n", formaPagamento);
        printf("  Arquivo removido  : %s\n", nomeArquivo);
        printf("=================================================\n");
    }
}

void relatorioVendas(void){
    printf("\n=============================================================================\n");
    printf("                             RELATÓRIO DE VENDAS                             \n");
    printf("=============================================================================\n");
    int totalVendidos = 0;
    int totalMeia = 0;
    int totalNormal = 0;
    float totalFaturamento = 0.0f;

    // Percorre todas as sessões e assentos
    for (int sessao = 0; sessao < 2; sessao++) {
        printf("\nSessão %d:\n", sessao + 1);
        int vendidosSessao = 0;
        int cabecalhoMostrado = 0;

        for (int fila = 0; fila < 5; fila++) {
            for (int cadeira = 0; cadeira < 6; cadeira++) {
                if (sessoes[sessao][fila][cadeira].ocupado == 1) {
                    if (!cabecalhoMostrado) {
                        printf("-----------------------------------------------------------------------------\n");
                        printf(" Assento | Idade | Tipo     | Pagamento | Valor\n");
                        printf("-----------------------------------------------------------------------------\n");
                        cabecalhoMostrado = 1;
                    }
                    vendidosSessao++;
                    totalVendidos++;
                    if (sessoes[sessao][fila][cadeira].ehMeia) {
                        totalMeia++;
                    } else {
                        totalNormal++;
                    }
                    totalFaturamento += sessoes[sessao][fila][cadeira].valorPago;
                    printf("  %c-%d    | %-5d | %-8s | %-9s | R$ %.2f\n",
                           'A' + fila, cadeira + 1,
                           sessoes[sessao][fila][cadeira].idade,
                           sessoes[sessao][fila][cadeira].ehMeia ? "Meia" : "Normal",
                           sessoes[sessao][fila][cadeira].formaPagamento,
                           sessoes[sessao][fila][cadeira].valorPago);
                }
            }
        }
        if (vendidosSessao == 0) {
            printf("  Nenhum ingresso vendido para esta sessão.\n");
        } else {
            printf("-----------------------------------------------------------------------------\n");
        }
    }

    // Exibe resumo geral das vendas
    printf("\n=============================================================================\n");
    printf("                                RESUMO GERAL                                 \n");
    printf("=============================================================================\n");
    printf("  Total de ingressos vendidos : %d\n", totalVendidos);
    printf("  Meia-entrada                : %d\n", totalMeia);
    printf("  Ingresso normal             : %d\n", totalNormal);
    printf("  Faturamento total           : R$ %.2f\n", totalFaturamento);
    printf("=============================================================================\n");
}

void gerenciarReinicializacao(){
    int ehAdmin;
    printf("\n=== REINICIAR SISTEMA ===\n");
    char senha[50];
    printf("Digite a senha de administrador: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0'; // Remove o caractere \n

    if (strcmp(senha, "admin") == 0) {
        inicializarAssentos();
        printf("\nSistema reiniciado com sucesso! Todos os assentos estão livres e os arquivos de vendas foram apagados.\n");
    } else {
        printf("\nSenha incorreta! Acesso negado.\n");
    }
}

void aguardarEnter() {
    printf("\nPressione ENTER para voltar ao menu principal...");
    getchar();
}

