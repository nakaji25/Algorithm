/* bucket_sort のプログラム */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#include <math.h>
int i = 0, j = 0;
void merge_sort(int *A, int p, int r);
void merge(int *A, int p, int q, int r);
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
    fscanf(fp, "%d", &N);
    /* N, l, u, m をファイルから読み込む */
    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50;
    }

    for (i = 0; i < N; i++) /* 整数をファイルから読み込む */
    {
        fscanf(fp, "%d", &Data[i]);
    }
    fclose(fp);
    printf("ソート前の配列:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]);
    }
    printf("\n");

    merge_sort(Data, 0, N - 1);

    printf("ソート後の配列:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]);
    }
    printf("\n");
}
void merge_sort(int *A, int p, int r)
{
    int q;
    if (p < r)
    {
        q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}
void merge(int *A, int p, int q, int r)
{
    int i, j, k,a;
    i = p, j = q + 1, k = p;
    int B[r + 1];
    while (1)
    {
        if (A[i] <= A[j])
        {
            B[k++] = A[i++];
        }
        else
        {
            B[k++] = A[j++];
        }
        if (i > q || j > r)
        {
            break;
        }
    }
    while (i <= q)
    {
        B[k++] = A[i++];
    }
    while (j <= r)
    {
        B[k++] = A[j++];
    }
    for (a = p; a <= r; a++)
    {
        A[a] = B[a];
    }
}