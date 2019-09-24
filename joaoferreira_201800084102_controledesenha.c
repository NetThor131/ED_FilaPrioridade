#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente
{
    char nome[51];
    int ordem;
    struct cliente* proximo;
} Cliente;

typedef struct orgao
{
    int caixas;
    char orgao[51];
    int qntdprio;
    int qntdnormal;
    Cliente *prio;
    Cliente *normal;
} Orgao;

Cliente* cria(char nome[51])
{
    Cliente* x = (Cliente*)malloc(sizeof(Cliente));
    x->proximo = (Cliente*)malloc(sizeof(Cliente));
    strcpy(x->nome, nome);
    return x;
}

int main(int argc, char *argv[])
{
    int trees, range, idade;
    char pessoa[51], local[51];
    char c[1];
    Orgao *lstorgao;

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    fscanf(input, "%i", &trees);
    lstorgao = (Orgao *)malloc(trees * sizeof(Orgao));

    for (int i = 0; i < trees; i++)
    {
        fscanf(input, "%s %i", lstorgao[i].orgao, &lstorgao[i].caixas);
        lstorgao[i].qntdnormal = 0;
        lstorgao[i].qntdprio = 0;
        lstorgao[i].normal = NULL;
        lstorgao[i].prio = NULL;
    }

    fscanf(input, "%i", &range);
    for (int i = 0; i < range; i++)
    {
        fscanf(input, "%c %50[^|]%*c %50[^|]%*c %i", c, local, pessoa, &idade);
        for (int x = 0; x < trees; x++)
        {
            if (!((strcmp(local, lstorgao[x].orgao))))
            {
                if (idade < 60)
                {
                    lstorgao[x].qntdnormal++;
                    if (lstorgao[x].normal == NULL)
                    {
                        lstorgao[x].normal = cria(pessoa);
                    }
                    else
                    {
                        Cliente *aux = lstorgao[x].normal;
                        while (aux->proximo != NULL)
                        {
                            aux = aux->proximo;
                        }
                        aux->proximo = cria(pessoa);
                    }
                }
                else
                {
                    lstorgao[x].qntdprio++;
                    if (lstorgao[x].prio == NULL)
                    {
                        lstorgao[x].prio = cria(pessoa);
                    }
                    else
                    {
                        Cliente *aux = lstorgao[x].prio;
                        while (aux->proximo != NULL)
                        {
                            aux = aux->proximo;
                        }
                        aux->proximo = cria(pessoa);
                    }
                }
                break;
            }
        }
    }

    Cliente* aux;

    while(range > 0){
        for(int x = 0; x < trees; x++){
            if(lstorgao[x].qntdnormal > 0){
                fprintf(output,"%s:", lstorgao[x].orgao);
            }
            for(int f = 0; f < lstorgao[x].caixas; f++){
                if(lstorgao[x].qntdprio > 0){
                
                    lstorgao[x].qntdprio--;
                    range--;
                    if(f + 1 < lstorgao[x].caixas){
                        fprintf(output,"%s,", lstorgao[x].prio->nome);
                    }
                    else{
                        fprintf(output,"%s", lstorgao[x].prio->nome);
                    }
                    aux = lstorgao[x].prio->proximo->proximo;
                    lstorgao[x].prio = aux;
                    
                }
                else if(lstorgao[x].qntdnormal > 0){
                    
                    lstorgao[x].qntdnormal--;
                    range--;
                    if(f + 1 < lstorgao[x].caixas && lstorgao[x].qntdnormal > 0){
                        fprintf(output,"%s,", lstorgao[x].normal->nome);
                    }
                    else{
                        fprintf(output,"%s", lstorgao[x].normal->nome);
                    }
                    aux = lstorgao[x].normal->proximo->proximo;
                    lstorgao[x].normal = aux; 
                }
            }
            fprintf(output, "\n");
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}
