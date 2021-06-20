#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50  /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define maxM 500 /* 扱う辺数の最大値，ここでは 500 に設定 */
struct edge_data /* 構造体 edge_data の定義 */
{
    int end1;
    int end2;
};
void make_set(int *p, int *rank, int x); /* make_set関数を宣言 */
/* find_set, link も宣言すること */
void set_union(int *p, int *rank, int x, int y); /* set_union関数を宣言 */
int find_set(int *p, int x);
void link(int *p, int *rank, int x, int y);

int main(void)
{
    int N, M;                    /* 頂点数，辺数 */
    struct edge_data edge[maxM]; /* 辺データを表す変数 */
    int p[maxN], rank[maxN];     /* p[x], rank[x]を格納する変数 */
    int component[maxN];         /* 連結成分番号 component[u] を格納する変数 */
    int number_comp;             /* 連結成分数を表す変数 */
    int u, v;                    /* 頂点番号，重みを表す変数 */
    /* 必要な変数を宣言 */
    int i;
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp;        /* 入力ファイル */

    printf("input filename: "); /* ファイル名の入力を要求 */
    /* 入力ファイルの操作 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);
    fp = fopen(fname, "r");      /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d %d", &N, &M); /* ファイルから N, M を読み込む */

    for (i = 0; i < M; i++)
    {
        fscanf(fp, " %d %d", &u, &v); /* 順番に辺の両端 u, v を読み込む */
        edge[i].end1 = u;             /* 配列 edge に格納 */
        edge[i].end2 = v;
    }
    fclose(fp);
    for (u = 0; u < N; u++)
    {
        make_set(p, rank, u); /* 各頂点に対して make_set を実行 */
    }
    for (i = 0; i < M; i++)
    {
        /* 主要部分 */
        set_union(p, rank, edge[i].end1, edge[i].end2);
    }
    number_comp = 0;
    for (i = 0; i < N; i++)
    {
        if (i == p[i])
        {
            number_comp++;
            for (u = 0; u < N; u++)
            {
                v = find_set(p, u);
                if (i == v)
                {
                    component[u] = number_comp;
                }
            }
        }
    }
    printf("number of components = %d\n", number_comp);
    for (i = 0; i < N; i++)
    {
        printf("vertex%d component=%d parent=%d rank=%d\n", i, component[i], p[i], rank[i]);
    }
}
void make_set(int *p, int *rank, int x)
{
    p[x] = x;
    rank[x] = 0;
}
void set_union(int *p, int *rank, int x, int y)
{
    int u, v;
    u = find_set(p, x);
    v = find_set(p, y);
    if (u != v)
    {
        link(p, rank, u, v);
    }
}
int find_set(int *p, int x)
{
    int r, y, z;
    y = x;
    while (y != p[y])
    {
        y = p[y];
    }
    r = y;
    y = x;
    while (y != r)
    {
        z = p[y];
        p[y] = r;
        y = z;
    }
    return y;
}
void link(int *p, int *rank, int x, int y)
{
    if (rank[x] > rank[y])
    {
        p[y] = x;
    }
    else
    {
        p[x] = y;
        if (rank[x] == rank[y])
        {
            rank[y] = rank[y] + 1;
        }
    }
}