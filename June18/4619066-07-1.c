/* bucket_sort のプログラム */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
struct cell         /* 構造体 cell の定義 */
{
    int key;
    int next;
};

void bucket_sort(int *A, int n, int l, int u, int m); /* 関数bucket_sort の宣言 */
void insertion_sort(struct cell *L, int *A, int *T, int *B, int m);

int main(void)
{
    int Data[50];
    int N, l, u, m;
    int i, j;
    char fname[128];
    FILE *fp;
    printf("input filename: ");
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);

    fp = fopen(fname, "r");
    fscanf(fp, "%d %d %d %d", &N, &l, &u, &m);
    /* N, l, u, m をファイルから読み込む */
    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50;
    }
    for (i = 0; i < N; i++) /* 整数をファイルから読み込む */
    {
        fscanf(fp, "%d", &Data[i]);
        if (Data[i] < l || Data[i] > u) /* [l, u] の範囲内かを判定し，範囲外なら*/
        {
            printf("error:%dは範囲外なので排除します。\n", Data[i]); /* エラーメッセージを表示し，データから外す*/
            i--;
            N--;
        }
    }

    fclose(fp);
    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]);
    }
    printf("\n");

    bucket_sort(Data, N, l, u, m);

    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]);
    }
    printf("\n");
}

void bucket_sort(int *A, int n, int l, int u, int m)
{
    struct cell List[50]; /* リストを格納する配列 */
    int B[50];            /* バケットを表す配列 */
    int i, j;
    int min, max, range;
    int t = 0;
    int T[m + 1];
    /* 必要な変数を宣言 */

    for (i = 0; i < m + 1; i++)
    {
        T[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        List[i].key = A[i]; /* あらかじめ n 個の数値をリストに格納 */
        List[i].next = -1;  /* next の値を初期化 */
    }
    for (j = 0; j < m; j++) /* バケットを初期化 */
    {
        B[j] = -1;
    }
    /* 主要部分，各自作成 */
    min = l;
    range = (u - l) / m;
    max = l + range;

    for (j = 0; j < m; j++)
    {
        for (i = 0; i < n; i++)
        {
            if (List[i].key >= min && List[i].key < max)
            {
                List[i].next = B[j];
                B[j] = i;
                t++;
            }
        }
        T[j + 1] = t;
        min = max;
        max = min + range;
    }

    insertion_sort(List, A, T, B, m);
}
void insertion_sort(struct cell *L, int *A, int *T, int *B, int m)
{
    int i, j, k;
    int a, b, position;
    for (j = 0; j < m; j++)
    {
        position = B[j];
        for (i = T[j]; i < T[j + 1]; i++)
        {
            a = L[position].key;
            b = i - 1;
            while (b >= 0 && A[b] > a)
            {
                k = A[b + 1];
                A[b + 1] = A[b];
                A[b] = k;
                b = b - 1;
            }
            A[b + 1] = a;
            position = L[position].next;
        }
    }
}