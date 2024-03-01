#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int leArquivo(char *inicio, char *fim)
{
    FILE *f = fopen("t.txt", "r");

    if (f == NULL)
    {
        perror("Erro abrindo arquivo");
        return 1;
    }

    char aux[50], comando[20], conteudo[10];

    while (fgets(aux, sizeof(aux), f) != NULL)
    {
        sscanf(aux, "%20[^()]", comando);
        sscanf(aux, "%*[^(](%10[^)])", conteudo);


        if (strcmp(comando, "ponto_inicial") == 0)
        {
            strcpy(inicio, conteudo);
        }
        else if (strcmp(comando, "ponto_final") == 0)
        {
            strcpy(fim, conteudo);
        }
        else if (strcmp(comando, "pode_ir") == 0)
        {
            
        }
        else if (strcmp(comando, "h") == 0)
        {
            
        }
        else
        {
            printf("Comando desconhecido\n");
            return 1;
        }
        memset(aux, 0, sizeof(aux));
        memset(conteudo, 0, sizeof(conteudo));
        memset(comando, 0, sizeof(comando));
    }//

    fclose(f);

    return 0;
}


int main(){
    char pontoInicial[20];
    char pontoFinal[20];
    leArquivo(pontoInicial, pontoFinal);
    printf("pI = %s\n", pontoInicial);
    printf("pF = %s\n", pontoFinal);
}

