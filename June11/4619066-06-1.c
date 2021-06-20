#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define W 10        /* W = 文字列の最大長さ，ここでは10に設定 */
#define m 97        /* m = ハッシュ表のサイズ，ここでは 97 に設定 */
#define n 50        /* n = 扱う文字列の最大数，ここでは 50 に設定 */
struct cell         /* 構造体 cell の定義 */
{
    char key[W + 1];
    int next;
};
int allocate_object(struct cell *L, int *f);              /* 関数 allocate_object の宣言 */
int chained_hash_search(int *A, struct cell *L, char *a); /* 関数 chained_hash_search の宣言 */
/* (他の関数も宣言すること) */
int hash_val(char *a);
void chained_hash_insert(int *A, struct cell *L, int x);
void chained_hash_delete(int *A, struct cell *L, int x);
int hash_length(int *A, struct cell *L, int h);
void Free_Object(struct cell *L, int *f, int *x);
int main(void)
{
    struct cell List[n]; /* リストは cell の配列，数値数は nまで */
    int A[m];            /* ハッシュ表を表す配列 */
    int N;               /* 数値の数は N */
    int freeL;           /* 空きアドレスのリストの先頭*/
    int i, h;
    char word[W + 1]; /* ファイルから読み込んだ文字列を格納する変数 */
    int y, x, length;
    int zero;
    /* 必要な変数を宣言 */

    char fname[128];            /* 読み込むファイルの名前 */
    FILE *fp;                   /* 入力ファイル */
    for (i = 0; i < n - 1; i++) /* allocate_object, free_object のための初期化 */
    {
        List[i].next = i + 1;
    }
    List[n - 1].next = -1;
    freeL = 0;              /* 空きリストの初期化 */
    for (h = 0; h < m; h++) /* ハッシュ表の初期化 */
    {
        A[h] = -1;
    }
    /* 入力ファイルの操作 */
    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */

    fp = fopen(fname, "r"); /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d", &N);   /* N をファイルから読み込む */
    if (N > n)
    {
        printf("N is too large, setting N = %d\n", n);
        N = n;
    }
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%s", word);                 /* 文字列をファイルから読み込み，word に格納 */
        y = chained_hash_search(A, List, word); /* ハッシュ表の中で文字列 word を探索 */
        if (y == -1)
        {
            x = allocate_object(List, &freeL);
            strcpy(List[x].key, word);
            chained_hash_insert(A, List, x); /* 挿入手続き */
        }
    }
    fclose(fp); /* 開いたファイルを一旦閉じる */
    for (h = 0; h < m; h++)
    {
        /* ハッシュ表のアドレス h が指す*/
        length = hash_length(A, List, h);
        /* リスト A[h] の長さを出力 */
        if (length != 0)
        {
            printf("A[%d]の長さは%d\n", h, length);
        }
    }
    fp = fopen(fname, "r"); /* ファイルを再度読み込みモードで開く */
    fscanf(fp, "%d", &N);   /* N をファイルから読み込む */
    if (N > n)
    {
        N = n;
    }
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%s\n", word); /* 文字列をファイルから読み込み，word に格納 */
        /* データを削除する部分 */
        y = chained_hash_search(A, List, word);
        if (y != -1)
        {
            chained_hash_delete(A, List, y); /* 挿入手続き */
            Free_Object(List, &freeL, &y);
        }
    }
    fclose(fp); /* 開いたファイルを閉じる */
    for (h = 0; h < m; h++)
    {
        /* ハッシュ表のアドレス h が指す*/
        length = hash_length(A, List, h);
        /* リスト A[h] の長さを出力 */
        if (length != 0)
        {
            printf("A[%d]の長さは%d\n", h, length);
        }
    }
}

/*以下，関数 hash val のコード*/

int hash_val(char *a) /* 文字列はポインタ渡し */
{
    int h, i;
    h = 0;
    i = 0;
    while (a[i] != 0 && i < W) /* 文字の整数コードの和を計算 */
    {
        h = h + (int)a[i];
        i = i + 1;
    }
    h = h % m; /* m で割った余りを取る */
    return h;
}
int allocate_object(struct cell *L, int *f) /* リスト配列と空きアドレスリスト先頭はポインタ渡し */
{
    int x;
    if (*f == -1)
    {
        printf("error'out of space'\n");
    }
    else
    {
        x = *f;
        *f = L[x].next;
    }
    /* 空きアドレスがなければエラーメッセージを表示 */
    return x;
}
int chained_hash_search(int *A, struct cell *L, char *a)
{
    int x, h;
    h = hash_val(a);
    x = A[h];
    while (x != -1 && strcmp(L[x].key, a) != 0)
    {
        x = L[x].next;
    }
    return x;
}
void chained_hash_insert(int *A, struct cell *L, int x)
{
    int h;
    h = hash_val(L[x].key);
    L[x].next = A[h];
    A[h] = x;
}
int hash_length(int *A, struct cell *L, int i)
{
    int x, l = 0;
    if (A[i] != -1)
    {
        x = A[i];
        l++;
        while (L[x].next != -1)
        {
            l++;
            x = L[x].next;
        }
    }
    return l;
}
void chained_hash_delete(int *A, struct cell *L, int x)
{
    int h, z;
    h = hash_val(L[x].key);
    z = A[h];
    while (z != -1)
    {
        if (L[z].next == x)
        {
            L[z].next = L[x].next;
            break;
        }
        z = L[z].next;
    }
    if (z == -1)
    {
        A[h] = L[x].next;
    }
}
void Free_Object(struct cell *L, int *f, int *x)
{
    L[*x].next = *f;
    *f = *x;
}