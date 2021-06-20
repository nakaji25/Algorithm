/* bucket_sort のプログラム */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#include <math.h>

void radix_sort_count(int *A, int n, int k, int d);
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
        if (Data[i] > powk(k, d) || Data[i] < 0) /* [l, u] の範囲内かを判定し，範囲外なら*/
        {
            printf("error:%dは範囲外なので排除します。\n", Data[i]); /* エラーメッセージを表示し，データから外す*/
            i--;
            N--;
        }
    }
    fclose(fp);
    printf("ソート前の配列:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]);
    }
    printf("\n");

    radix_sort_count(Data, N, k, d);

    printf("ソート後の配列:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]);
    }
    printf("\n");
}
void radix_sort_count(int *A, int n, int k, int d)
{
    int r, p;
    int i, j;
    int C[k];
    int B[50];
    for (p = 0; p < d; p++)
    {
        for (i = 0; i < k; i++)
        {
            C[i] = 0;
        }
        for (i = 0; i < n; i++)
        {
            r = powk(k, p);
            j = (A[i] / r) % k;
            C[j]++;
        }
        for (i = 1; i < k; i++)
        {
            C[i] = C[i - 1] + C[i];
        }
        for (i = n - 1; i >= 0; i--)
        {
            r = powk(k, p);
            j = (A[i] / r) % k;
            B[C[j] - 1] = A[i];
            C[j] = C[j] - 1;
        }
        for (i = 0; i < n; i++)
        {
            A[i] = B[i];
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
