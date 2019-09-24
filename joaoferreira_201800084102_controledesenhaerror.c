#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    char orgao[51];
    int caixas;
    int acertos;
    int prio;
    char nome[51];
} No;

typedef struct trees
{
    char orgao[51];
    int caixas;
    int pos;
} Trees;

void heapifymax(No *V, int T, int i)
{
    No ajuda;
    int P = i, E = 2 * i + 1, D = 2 * i + 2;
    if (E < T && V[E].prio >= V[P].prio)
    {
        if (V[E].acertos < V[P].acertos)
        {
            P = E;
        }
        if (V[E].prio > V[P].prio)
        {
            P = E;
        }
    }
    if (D < T && V[D].prio >= V[P].prio)
    {
        if (V[D].acertos < V[P].acertos)
        {
            P = D;
        }
        if (V[D].prio > V[P].prio)
        {
            P = D;
        }
    }
    if (P != i)
    {
        ajuda = V[i];
        V[i] = V[P];
        V[P] = ajuda;
        heapifymax(V, T, P);
    }
}

int main(int argc, char *argv[])
{
    int trees, range, idade;
    char c[1];
    No *fila;

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    fscanf(input, "%i", &trees);

    Trees *filas = (Trees *)malloc(trees * sizeof(Trees));

    for (int i = 0; i < trees; i++)
    {
        fscanf(input, "%s %i", filas[i].orgao, &filas[i].caixas);
        filas[i].pos = 0;
    }

    fscanf(input, "%i", &range);
    for (int i = 0; i < trees; i++)
    {
        fila = (No *)malloc(range * sizeof(No));
    }

    for (int i = 0; i < range; i++)
    {
        fscanf(input, "%c %50[^|]%*c %50[^|]%*c %i", c, fila[i].orgao, fila[i].nome, &idade);
        fila[i].acertos = i;
        if (idade >= 60)
        {
            fila[i].prio = 1;
        }
        else
        {
            fila[i].prio = 0;
        }
    }

    for (int i = range - 1; i >= 0; i--)
    {
        heapifymax(fila, range, i);
    }

    while (1)
    {
        if (fila[0].prio != -1)
        {
            for (int i = 0; i < trees; i++)
            {
                for (int x = 0; x < range; x++)
                {
                    if (strcmp(filas[i].orgao, fila[x].orgao) == 0)
                    {
                        fprintf(output, "%s:", filas[i].orgao);
                        fprintf(output, "%s", fila[x].nome);
                        fila[x] = fila[range - 1];
                        fila[range - 1].prio = -1;
                        for (int i = range - 1; i >= 0; i--)
                        {
                            heapifymax(fila, range, i);
                        }
                        break;
                    }
                }
                for (int z = 1; z < filas[i].caixas; z++)
                {
                    for (int w = 0; w < range; w++)
                    {
                        if (strcmp(filas[i].orgao, fila[w].orgao) == 0 && fila[w].prio != -1)
                        {
                            fprintf(output, ",%s", fila[w].nome);
                            fila[w] = fila[range - 1];
                            fila[range - 1].prio = -1;
                            for (int i = range - 1; i >= 0; i--)
                            {
                                heapifymax(fila, range, i);
                            }
                            break;
                        }
                    }
                }
                fprintf(output, "\n");
            }
        }
        else
        {
            break;
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}