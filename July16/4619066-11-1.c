#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000

int main(void)
{
    int N, M; /* N:頂点の数、M:枝の数 */
    int v0;   /* 始点の変数 */
    int u, v, x;
    int i;
    int d[maxN], p[maxN], A[maxN];
    int l[maxN][maxN];

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
            l[u][v] = inf; /* 重み行列の初期化 */
        }
    }

    for (i = 0; i < M; i++)
    {
        fscanf(fp, " %d %d %d", &u, &v, &x); /* 重み行列に値を入力 */
        l[u][v] = x;
        l[v][u] = x;
    }

    fscanf(fp, " %d", &v0);
    fclose(fp);

    for (i = 0; i < N; i++)
    {
        d[i] = inf;
        p[i] = -1;
        A[i] = 0;
    }

    d[v0] = 0;
    p[v0] = -1;
    A[v0] = 1;
    v = v0;
    int point;

    while (1)
    {
        int length = inf;
        for (i = 0; i < N; i++)
        {
            if (A[i] == 1)
            {
                if (d[i] < length)
                {
                    length = d[i];
                    point = i;
                }
            }
        }
        if (length == inf)
        {
            break;
        }

        A[point] = 0;
        for (i = 0; i < N; i++)
        {
            if (l[point][i] != inf)
            {
                if (d[i] == inf)
                {
                    d[i] = d[point] + l[point][i];
                    p[i] = point;
                    A[i] = 1;
                }
                else if (d[i] > d[point] + l[point][i])
                {
                    d[i] = d[point] + l[point][i];
                    p[i] = point;
                }
            }
        }
    }

    for (i = 0; i < N; i++)
    {
        printf("vertex %d: d[%d] = %d,p[%d] = %d\n", i, i, d[i], i, p[i]);
    }

    return 0;
}