#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50

int main(void)
{
    int N, M;
    int Adj[maxN][maxN];
    int u, v;
    int i;

    char fname[128];
    FILE *fp;

    printf("input filename: ");
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);

    fp = fopen(fname, "r");
    fscanf(fp, "%d %d", &N, &M);

    for (u = 0; u < N; u++)
    {
        for (v = 0; v < N; v++)
        {
            Adj[u][v] = 0;
        }
    }

    for (i = 0; i < M; i++)
    {
        fscanf(fp, " %d %d", &u, &v);
        Adj[u][v] = 1;
        Adj[v][u] = 1;
    }

    fclose(fp);
    printf("Adjacency matrix\n");
    for (u = 0; u < N; u++)
    {
        for (v = 0; v < N; v++)
        {
            printf("%d", Adj[v][u]);
        }
        printf("\n");
    }
}