/* bucket_sort のプログラム */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#include <math.h>
struct cell /* 構造体 cell の定義 */
{
    int key;
    int next;
};

void radix_sort_bucket(int *A, int n, int k, int d);
void insertion_sort(struct cell *L, int *A, int *T, int *B, int m);
int powk(int k, int p);

int main(void)
{
    int Data[50];
    int N, k, d;
    int i, j;

    char fname[128];
    FILE *fp;
    printf("input filename: ");
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);

    fp = fopen(fname, "r");
    fscanf(fp, "%d %d %d ", &N, &k, &d);
    /* N, l, u, m をファイルから読み込む */
    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50;
    }

    for (i = 0; i < N; i++) /* 整数をファイルから読み込む */
    {
        fscanf(fp, "%d", &Data[i]);
        if (Data[i] > pow(k, d)) /* [l, u] の範囲内かを判定し，範囲外なら*/
        {
            printf("error:%dは範囲外なので排除します。\n", Data[i]); /* エラーメッセージを表示し，データから外す*/
            i--;
            N--;
        }
        else if (Data[i] < 0)
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

    radix_sort_bucket(Data, N, k, d);

    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]);
    }
    printf("\n");
}

void radix_sort_bucket(int *A, int n, int k, int d)
{
    int p, i, j, position;
    int B[k];
    struct cell List[50];
    int t, r;
    int T[k + 1];

    for (p = 0; p < d; p++)
    {
        for (i = 0; i < n; i++)
        {
            List[i].key = A[i]; /* あらかじめ n 個の数値をリストに格納 */
            List[i].next = -1;  /* next の値を初期化 */
        }
        for (i = 0; i < k; i++)
        {
            B[i] = -1;
        }
        for (j = n - 1; j >= 0; j--)
        {
            r = powk(k, p);
            i = (A[j] / r) % k;
            List[j].next = B[i];
            B[i] = j;
        }
        j = 0;
        for (i = 0; i < k; i++)
        {
            position = B[i];
            while (position != -1)
            {
                A[j] = List[position].key;
                position = List[position].next;
                j++;
            }
        }
    }
}
int powk(int k, int p)
{
    int i, l;
    l = k;
    for (i = 0; i < p - 1; i++)
    {
        k *= l;
    }
    return k;
}
