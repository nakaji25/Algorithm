/*以下，内部ハッシュ法のプログラムの構造体宣言と main 関数の冒頭部分*/
/* 内部ハッシュ法 */
/*(ライブラリの読み込み等，外部ハッシュ法と同様に宣言する) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define W 10
#define m 97
#define n 50
struct cell /* 構造体 cell の定義 */
{
    char key[W + 1];
    unsigned int state : 2;
};
int hash_search(struct cell *A, char *a); /* 関数 hash_search の宣言 */
/* (他の関数も宣言すること) */
void hash_insert(struct cell *A, char *a);
int hash_val(char *a);
void hash_delete(struct cell *A, char *a);
int main(void)
{
    struct cell A[m]; /* ハッシュ表を表すの配列 */
    int N;            /* 数値の数は N */
    char word[W + 1]; /* ファイルから読み込んだ文字列を格納する変数 */
                      /* 必要な変数を宣言 */
    char fname[128];  /* 読み込むファイルの名前 */
    FILE *fp;         /* 入力ファイル */
    int y, i;
    for (i = 0; i < m; i++)
    {
        A[i].state = 0;
    }                           /* ハッシュ表のの初期化 */
    printf("input filename: "); /* ファイル名の入力を要求 */
    /* 主要部分(各自作成) */
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
        fscanf(fp, "%s", word);   /* 文字列をファイルから読み込み，word に格納 */
        y = hash_search(A, word); /* ハッシュ表の中で文字列 word を探索 */
        if (y == -1)
        {
            hash_insert(A, word); /* 挿入手続き */
        }
    }
    fclose(fp); /* 開いたファイルを一旦閉じる */
    for (i = 0; i < m; i++)
    {
        if (A[i].state == 1)
        {
            printf("A[%d]のアドレスは%d,文字列は%s\n", i, i, A[i].key);
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
        hash_delete(A, word); /* 挿入手続き */
    }
    fclose(fp); /* 開いたファイルを閉じる */
    for (i = 0; i < m; i++)
    {
        if (A[i].state == 1)
        {
            printf("A[%d]のアドレスは%d,文字列は%s\n",i, i, A[i].key);
        }
    }
}
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
void hash_insert(struct cell *A, char *a)
{
    int x = -1;
    char h = hash_val(a);
    int i = 0;
    while (x == -1 && i < m)
    {
        if (A[(h + i) % m].state != 1)
        {
            x = (h + i) % m;
        }
        else
        {
            i = i + 1;
        }
    }
    if (x == -1)
    {
        printf("error: out of space\n");
    }
    else
    {
        strcpy(A[x].key, a);
        A[x].state = 1;
    }
}
int hash_search(struct cell *A, char *a)
{
    int h = hash_val(a);
    int i = 0;
    while (i < m)
    {
        if (A[h].state == 1 && strcmp(A[h].key, a) == 0)
        {
            return h;
        }
        else if (A[h].state == 0)
        {
            return -1;
        }
        else
        {
            i++;
            h = (h+1) % m;
        }
    }
    return -1;
}
void hash_delete(struct cell *A, char *a)
{
    int x = hash_search(A, a);
    if (x != -1)
    {
        strcpy(A[x].key, " ");
        A[x].state = 2;
    }
}
