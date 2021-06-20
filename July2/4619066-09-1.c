/* bucket_sort のプログラム */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#include <math.h>
int i = 0, j = 0;
void quicksort(int *A, int p, int r);
int partition(int *A, int p, int r);
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

    quicksort(Data, 0, N - 1);

    printf("ソート後の配列:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]);
    }
    printf("\n");
}
void quicksort(int *A, int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(A, p, r);
        quicksort(A, p, q);
        quicksort(A, q + 1, r);
    }
}
int partition(int *A, int p, int r)
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