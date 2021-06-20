
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000
struct cell
{
    int key;
    int vertex;
};
int parent(int i);
int left(int i);
int right(int i);
void insert(struct cell *H, int *adr, int i, int a, int v);
void decrease_key(struct cell *H, int *adr, int i, int a);
int delete_min(struct cell *H, int *adr, int i);
void upheap_sort(struct cell *H, int *adr, int i);
void downheap_sort(struct cell *H, int *adr, int i);

int main(void)
{
    int N, M;               /* 頂点数，辺数 */
    int Lmat[maxN][maxN];   /* 重み行列を表す変数 */
    struct cell Heap[maxN]; /* ヒープに用いる配列の宣言 */
    int adr[maxN];          /* ヒープに含まれる頂点のアドレスの配列 */
    int d[maxN], p[maxN];   /* d[u], p[u] を格納する変数 */
    int hsize = 0;          /* ヒープに格納された頂点の数 */
    int v0;                 /* 始点を表す変数 */
    int u, v, len;
    int i;

    char fname[128];
    FILE *fp;

    printf("input filename: ");
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);

    fp = fopen(fname, "r");

    fscanf(fp, "%d %d", &N, &M);
    for (u = 0; u < N; u++)
    {
        for (v = 0; v < N; v++)
        {
            Lmat[u][v] = inf;
        }
    }

    for (i = 0; i < M; i++)
    {
        fscanf(fp, " %d %d %d", &u, &v, &len);
        Lmat[u][v] = len;
        Lmat[v][u] = len;
    }
    fscanf(fp, "%d", &v0);
    fclose(fp);

    for (u = 0; u < N; u++)
    {
        d[u] = inf;
        p[u] = -1;
        adr[u] = -1;
    }

    d[v0] = 0;
    p[v0] = -1;
    hsize++;
    insert(Heap, adr, hsize - 1, d[v0], v0);
    int point;

    while (hsize != 0)
    {
        point = delete_min(Heap, adr, hsize);
        hsize--;

        for (i = 0; i < N; i++)
        {
            if (Lmat[point][i] != inf)
            {
                if (d[i] == inf)
                {
                    d[i] = d[point] + Lmat[point][i];
                    p[i] = point;
                    hsize++;
                    insert(Heap, adr, hsize - 1, d[i], i);
                }
                else if (d[i] > d[point] + Lmat[point][i])
                {
                    d[i] = d[point] + Lmat[point][i];
                    p[i] = point;

                    decrease_key(Heap, adr, i, d[i]);
                }
            }
        }
    }
    for (i = 0; i < N; i++)
    {
        printf("vertex %d: d[%d] = %d,p[%d] = %d\n", i, i, d[i], i, p[i]);
    }
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
void insert(struct cell *H, int *adr, int i, int a, int v)
{
    H[i].key = a;
    H[i].vertex = v;
    adr[H[i].vertex] = i;
    upheap_sort(H, adr, i);
}
void upheap_sort(struct cell *H, int *adr, int i)
{
    int u, a;
    u = i;
    while (u > 0 && H[parent(u)].key > H[u].key)
    {
        a = H[u].key;
        H[u].key = H[parent(u)].key;
        H[parent(u)].key = a;

        a = H[u].vertex;
        H[u].vertex = H[parent(u)].vertex;
        H[parent(u)].vertex = a;

        a = adr[H[u].vertex];
        adr[H[u].vertex] = adr[H[parent(u)].vertex];
        adr[H[parent(u)].vertex] = a;

        u = parent(u);
    }
}
void downheap_sort(struct cell *H, int *adr, int i)
{
    int u = 0;
    int C, l, r;
    int change;
    while (1)
    {
        l = left(u);
        r = right(u);
        if (l <= i && H[l].key < H[u].key)
        {
            change = l;
        }
        else
        {
            change = u;
        }
        if (r <= i && H[r].key < H[change].key)
        {
            change = r;
        }
        if (change == u)
        {
            break;
        }
        else
        {
            C = H[u].key;
            H[u].key = H[change].key;
            H[change].key = C;

            C = H[u].vertex;
            H[u].vertex = H[change].vertex;
            H[change].vertex = C;

            C = adr[H[u].vertex];
            adr[H[u].vertex] = adr[H[change].vertex];
            adr[H[change].vertex] = C;

            u = change;
        }
    }
}
void decrease_key(struct cell *H, int *adr, int i, int a)
{
    H[i].key = a;
    upheap_sort(H, adr, i);
}
int delete_min(struct cell *H, int *adr, int i)
{
    int v;
    v = H[0].vertex;
    adr[v] = -1;
    if (i > 1)
    {
        H[0].key = H[i - 1].key;
        H[0].vertex = H[i - 1].vertex;
        adr[H[0].vertex] = 0;
        downheap_sort(H, adr, i - 2);
    }
    return v;
}