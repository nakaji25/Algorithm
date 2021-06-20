#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000

int main(void)
{
    int N, M;                          /* N:頂点の数、M:枝の数 */
    int Adj[maxN][maxN];               /* 隣接行列 */
    int d[maxN], p[maxN], color[maxN]; /* 配列変数 d, p, color */
    int v0;                            /* 始点の変数 */
    int Q[maxN];
    int head, tail;
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
    fscanf(fp, " %d", &v0);
    fclose(fp);

    for (i = 0; i < N; i++)
    {
        color[i] = 0;
        d[i] = inf;
        p[i] = -1;
    }
    head = 0;
    tail = 0;

    /*Enqueue*/
    Q[tail] = v0;
    tail++;
    if (tail == N)
    {
        tail = 0;
    }
    if (tail == head)
    {
        printf("overflow\n");
    }

    color[v0] = 1;
    d[v0] = 0;
    p[v0] = 0;

    do
    {
        /*Dequeue(*Q, *head, *tail, N);*/
        int a;
        if (head == tail)
        {
            printf("error:underflow");
        }
        else
        {
            a = Q[head];
            head++;
            if (head == N)
            {
                head = 0;
            }
        }
        v = a;

        for (u = 0; u < N; u++)
        {
            if (Adj[u][v] == 1)
            {
                if (color[u] == 0)
                {
                    /*Enqueue*/
                    Q[tail] = u;
                    tail++;
                    if (tail == N)
                    {
                        tail = 0;
                    }
                    if (tail == head)
                    {
                        printf("overflow\n");
                    }

                    color[u] = 1;
                    d[u] = d[v] + 1;
                    p[u] = v;
                }
                color[v] = 2;
            }
        }
    } while (head != tail);

    for (i = 0; i < N; i++)
    {
        printf("vertex: d[%d] = %d,p[%d] = %d\n", i, d[i], i, p[i]);
    }
}
