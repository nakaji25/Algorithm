#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void counting_sort(int *A, int n, int k);
int main(void)
{
    int Data[50];
    int N, k;
    int i, j;

    char fname[128];
    FILE *fp;

    printf("input filename: ");
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);

    fp = fopen(fname, "r");
    fscanf(fp, "%d %d", &N, &k);
    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50;
    }
    for (i = 0; i < N; i++)
    {
        /* (各自作成) */
        fscanf(fp, "%d", &Data[i]);         /* 整数をファイルから読み込む */
        if (Data[i] < 0 || Data[i] > k - 1) /* [0, k-1] の範囲内かを判定し，範囲外なら*/
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
    counting_sort(Data, N, k);
    printf("ソート後の配列:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]);
    }
    printf("\n");
}
void counting_sort(int *A, int n, int k)
{
    int i, j;
    int C[k];
    int B[50];
    for (i = 0; i < k; i++)
    {
        C[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        j = A[i];
        C[j]++;
    }

    for (i = 1; i < k; i++)
    {
        C[i] = C[i - 1] + C[i];
    }
    for (i = n - 1; i >= 0; i--)
    {
        B[C[A[i]] - 1] = A[i];
        C[A[i]] = C[A[i]] - 1;
    }
    for (i = 0; i < n; i++)
    {
        A[i] = B[i];
    }
}