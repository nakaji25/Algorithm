#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50     /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define inf 1000000 /* 無限大の値を十分大きな整数に設定 */
#define NIL -1      /*NILを-1に設定*/

struct cell /* 構造体 cell の定義 */
{
    int key;
    int vertex;
};

int parent(int i); /* parent関数を宣言 */
/* right, left も宣言すること */
int left(int i);
int right(int i);
void insert(struct cell *H, int *adr, int i, int a, int v);
void decrease_key(struct cell *H, int *adr, int i, int a);
int delete_min(struct cell *H, int *adr, int heapsize);
/* upheap_sort, downheap_sort も宣言すること */
void upheap_sort(struct cell *A, int *adr, int i);
void downheap_sort(struct cell *A, int *adr, int i);
void change(int *x, int *y);

int main(void)
{
    int N, M;               /* 頂点数，辺数 */
    int d[maxN], p[maxN];   /* d[u], p[u] を格納する変数 */
    struct cell Heap[maxN]; /* ヒープに用いる配列の宣言 */
    int Lmat[maxN][maxN];   /* 重み行列を表す変数 */
    int adr[maxN];          /* ヒープに含まれる頂点のアドレスの配列 */
    /* 必要な変数を宣言 */
    int u, v, len, v0, i, hsize;
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp;        /* 入力ファイル */

    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */

    /* 入力ファイルの操作 */
    fp = fopen(fname, "r");      /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d %d", &N, &M); /* ファイルから N, M を読み込む */
    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50;
    }

    for (u = 0; u < N; u++)
    {
        /* 重み行列とd,π,adrの初期化 */
        d[u] = inf;
        p[u] = NIL;
        adr[u] = NIL;
        for (v = 0; v < N; v++)
        {
            Lmat[u][v] = inf;
        }
    }

    for (i = 0; i < M; i++)
    {
        fscanf(fp, " %d %d %d", &u, &v, &len); /* 順番に辺の両端 u, vとその長さを読み込む */
        Lmat[u][v] = Lmat[v][u] = len;
    }
    fscanf(fp, " %d", &v0); /* 始点 v0 を読み込む */
    fclose(fp);             //ファイルを閉じる

    /*Dijkstra法 ヒープver.*/
    d[v0] = 0;
    p[v0] = NIL;
    hsize = 0;
    hsize++;
    insert(Heap, adr, hsize - 1, d[v0], v0);
    while (hsize != 0)
    {
        v = delete_min(Heap, adr, hsize);
        hsize--;
        for (u = 0; u < N; u++)
        {
            if (Lmat[u][v] != inf)
            {
                if (d[u] == inf)
                {
                    d[u] = d[v] + Lmat[v][u];
                    p[u] = v;
                    hsize++;
                    insert(Heap, adr, hsize - 1, d[u], u);
                }
                else if (d[u] > d[v] + Lmat[v][u])
                {
                    d[u] = d[v] + Lmat[v][u];
                    p[u] = v;
                    decrease_key(Heap, adr, u, d[u]);
                }
            }
        }
    }

    /*出力*/
    for (u = 0; u < N; u++)
    {
        printf("vertex %d: d[%d] = %d, p[%d] = %d\n", u, u, d[u], u, p[u]);
    }
}

int parent(int i)
{
    if (i != 0)
        return (i - 1) / 2;
    else
        return 0;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

void insert(struct cell *H, int *adr, int i, int a, int v)
{
    H[i].key = a;
    H[i].vertex = v;
    adr[v] = i;
    upheap_sort(H, adr, i);
}

void decrease_key(struct cell *H, int *adr, int i, int a)
{
    H[i].key = a;
    upheap_sort(H, adr, i);
}

int delete_min(struct cell *H, int *adr, int hsize)
{
    int v = H[0].vertex;
    adr[v] = NIL;
    if (hsize > 1)
    {
        H[0].key = H[hsize - 1].key;
        H[0].vertex = H[hsize - 1].vertex;
        adr[H[0].vertex] = 0;
        downheap_sort(H, adr, hsize - 2);
    }
    return v;
}

void upheap_sort(struct cell *A, int *adr, int i)
{
    int u = i;
    while (u > 0 && A[parent(u)].key > A[u].key)
    {
        change(&A[u].key, &A[parent(u)].key);
        change(&A[u].vertex, &A[parent(u)].vertex);
        change(&adr[A[u].vertex], &adr[A[parent(u)].vertex]);
        u = parent(u);
    }
}

void downheap_sort(struct cell *A, int *adr, int i)
{
    int u = 0, l, r, f = 1;
    while (f)
    {
        if (left(u) <= i)
            l = left(u);
        else
            l = u;
        if (right(u) <= i)
            r = right(u);
        else
            r = u;
        if (A[l].key <= A[r].key)
        {
            if (A[l].key >= A[u].key)
            {
                f = 0;
                continue;
            }
            change(&A[u].key, &A[l].key);
            change(&A[u].vertex, &A[l].vertex);
            change(&adr[A[u].vertex], &adr[A[l].vertex]);
            u = l;
        }
        else if (A[r].key < A[l].key)
        {
            if (A[r].key >= A[u].key)
            {
                f = 0;
                continue;
            }
            change(&A[u].key, &A[r].key);
            change(&A[u].vertex, &A[r].vertex);
            change(&adr[A[u].vertex], &adr[A[r].vertex]);
            u = r;
        }
        else
            f = 0;
    }
}

void change(int *x, int *y)
{
    int z = *x;
    *x = *y;
    *y = z;
}
