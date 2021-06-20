#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */

/* 関数 parent, heapsort の宣言，他の関数も宣言すること */
int parent(int i);
int left(int i);
int right(int i);
void heap_sort(int *H, int *A, int n);
void insert(int *H, int i, int a);
void build_heap(int *H, int *A, int n);
void upheap_sort(int *H, int i);
void downheap_sort(int *H, int i);
int i, j;
int main(void)
{
    int Data[50]; /* 数値を格納する配列， 50まで */
    int Heap[50]; /* ヒープを表す補助配列 */
    int N;        /* N やループで用いる int型変数 */

    char fname[128]; /* 読み込むファイルの名前を格納する変数 */
    FILE *fp;        /* ファイル名の変数など必要なものを宣言 */

    printf("input filename: ");         /* ファイル名の入力を要求 */
                                        /* ファイル名を取得して開き， */
                                        /* N などを読み込む */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */
    fp = fopen(fname, "r");             /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d", &N);               /* N をファイルから読み込む */

    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50; /* N が 50 を超えるときは警告をした上で */
    }           /* N =50 に設定する */
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%d", &Data[i]);
    }
    fclose(fp); /* 開いたファイルを閉じる */

    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]); /* ソート前の数値の出力 */
    }
    printf("\n");

    heap_sort(Heap, Data, N); /* ヒープソートを呼ぶ */

    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]); /* ソート後の数値の出力 */
    }
    printf("\n");
}

int parent(int i)
{
    return (i - 1) / 2;
}
int left(int i)
{
    return 2 * i + 1;
}
int right(int i)
{
    return 2 * i + 2;
}
void upheap_sort(int *H, int i)
{
    int u, a;
    u = i;
    while (u > 0 && H[parent(u)] < H[u])
    {
        a = H[u];
        H[u] = H[parent(u)];
        H[parent(u)] = a;
        u = parent(u);
    }
}
void insert(int *H, int i, int a)
{
    H[i] = a;
    upheap_sort(H, i);
}
void build_heap(int *H, int *A, int n)
{
    for (i = 0; i < n; i++)
    {
        insert(H, i, A[i]);
    }
}
void downheap_sort(int Heap[], int i)
{
    int u = 0;
    int C, l, r;
    int change;
    while (1)
    {
        l = left(u);
        r = right(u);
        if (l <= i && Heap[l] > Heap[u])
        {
            change = l;
        }
        else
        {
            change = u;
        }
        if (r <= i && Heap[r] > Heap[change])
        {
            change = r;
        }
        if (change == u)
        {
            break;
        }
        else
        {
            C = Heap[u];
            Heap[u] = Heap[change];
            Heap[change] = C;
            u = change;
        }
    }
}
void heap_sort(int *H, int *A, int n)
{
    build_heap(H, A, n);
    for (i = 1; i < n; i++)
    {
        A[n - i] = H[0];
        H[0] = H[n - i];
        downheap_sort(H, n - i - 1);
        A[0] = H[0];
    }
}

