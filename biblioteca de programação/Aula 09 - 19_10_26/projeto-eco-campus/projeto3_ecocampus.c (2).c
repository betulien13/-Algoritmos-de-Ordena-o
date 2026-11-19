#include <stdio.h>
#include <stdlib.h>

/* Imprime o resumo em qualquer destino: terminal (stdout) ou arquivo. */
void imprimirRelatorio(FILE *destino, int qtdLocais, float total, float media,
                       float maior, char nomeMaior[], int qtdAlertas)
{
    fprintf(destino, "========== ECOCAMPUS ==========\n");
    fprintf(destino, "Locais analisados: %d\n", qtdLocais);
    fprintf(destino, "Consumo total: %.2f litros\n", total);
    fprintf(destino, "Consumo medio: %.2f litros\n", media);
    fprintf(destino, "Maior consumo: %s - %.2f litros\n", nomeMaior, maior);
    fprintf(destino, "Locais em alerta: %d\n", qtdAlertas);
    fprintf(destino, "================================\n");
}

int main(void)
{
    FILE *entrada;   /* arquivo de leitura */
    FILE *saida;     /* arquivo de escrita */

    char  nome[50];
    char  nomeMaior[50] = "";
    float consumo, limite;
    float total = 0.0f, media = 0.0f, maior = 0.0f;
    int   qtdLocais = 0, qtdAlertas = 0;

    /* Abre o arquivo de entrada e verifica se deu certo */
    entrada = fopen("consumo_campus.txt", "r");
    if (entrada == NULL)
    {
        printf("Erro: nao foi possivel abrir o arquivo consumo_campus.txt\n");
        return 1;
    }

    /* Le todos os registros ate o fim do arquivo.
       fscanf devolve quantos campos leu; 3 = linha completa e valida. */
    while (fscanf(entrada, "%49s %f %f", nome, &consumo, &limite) == 3)
    {
        qtdLocais++;
        total += consumo;

        /* O primeiro registro inicia o maior; depois so troca se for superado */
        if (qtdLocais == 1 || consumo > maior)
        {
            maior = consumo;
            sprintf(nomeMaior, "%s", nome);
        }

        if (consumo > limite)
        {
            qtdAlertas++;
        }
    }

    fclose(entrada);

    /* Media so e calculada se existe pelo menos um registro valido */
    if (qtdLocais == 0)
    {
        printf("Nenhum registro valido encontrado em consumo_campus.txt\n");
        return 1;
    }

    media = total / qtdLocais;

    /* Exibe no terminal */
    imprimirRelatorio(stdout, qtdLocais, total, media, maior, nomeMaior, qtdAlertas);

    /* Cria o relatorio em arquivo */
    saida = fopen("relatorio_consumo.txt", "w");
    if (saida == NULL)
    {
        printf("Erro: nao foi possivel criar o arquivo relatorio_consumo.txt\n");
        return 1;
    }

    imprimirRelatorio(saida, qtdLocais, total, media, maior, nomeMaior, qtdAlertas);
    fclose(saida);

    printf("\nRelatorio salvo em relatorio_consumo.txt\n");
    return 0;
}