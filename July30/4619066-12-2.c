#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50  /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define maxM 500 /* 扱う辺数の最大値，ここでは 500 に設定 */
struct edge_data /* 構造体 edge_data の定義 */
{
    int end1;
    int end2;
    int weight;
};
void quicksort(int *A, int *ednum, int p, int r);
int partition(int *A, int *ednum, int p, int r);
/* quicksort関連の関数の宣言 */
int main(void)
{
    int N, M;                    /* 頂点数，辺数 */
    struct edge_data edge[maxM]; /* 辺データを表す変数 */
    int W[maxM];                 /* 辺の重みを格納する配列 */
    int ednum[maxM];             /* 昇順における辺の番号を格納する配列 */
    int u, v, w;                 /* 頂点番号，重みを表す変数 */
    /* 必要な変数を宣言 */
    int i, k;
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
        fscanf(fp, " %d %d %d", &u, &v, &w); /* 順番に辺の両端 u, v を読み込む */
        edge[i].end1 = u;                    /* 配列 edge に格納 */
        edge[i].end2 = v;
        edge[i].weight = w;
    }
    fclose(fp);
    for (i = 0; i < M; i++)
    {
        W[i] = edge[i].weight; /* 配列 W と ednum にデータを格納 */
        ednum[i] = i;
    }
    quicksort(W, ednum, 0, M - 1);

    for (i = 0; i < M; i++)
    {
        k = ednum[i];
        printf("edge %2d: (%2d, %2d)", k, edge[k].end1, edge[k].end2);
        printf(" weight = %d\n", edge[k].weight);
    }
}
void quicksort(int *A, int *e, int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(A, e, p, r);
        quicksort(A, e, p, q);
        quicksort(A, e, q + 1, r);
    }
}
int partition(int *A, int *e, int p, int r)
{
    int x, y, j, i;
    x = A[p];
    j = r;
    i = p;
    while (1)
    {
        while (A[j] > x)
        {
            j--;
        }
        while (A[i] < x)
        {
            i++;
        }
        if (i < j)
        {
            y = A[i];
            A[i] = A[j];
            A[j] = y;

            y = e[i];
            e[i] = e[j];
            e[j] = y;
            j--;
            i++;
        }
        else
        {
            break;
        }
    }
    return j;
}