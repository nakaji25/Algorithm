#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct cell
{
    /* 文字列関数を扱えるようにする */
    int key;
    int next; /* 構造体 cell の定義 */
};
int allocate_object(struct cell *L, int *f); /* 関数 allocate_object の宣言 */ /* (他の関数も宣言すること) */
void List_Insert(struct cell *L, int *head, int *x);
int List_Minimum(struct cell *L, int *head);
void List_Delete(struct cell *L, int *head, int *x);
void Free_Object(struct cell *L, int *f, int *x);
int main(void)
{
    struct cell List[50]; /* リストは cell の配列，数値数は 50 まで */
    int N;                /* 数値の数は N */
    int Data[50];         /* 数値を格納する配列は Data */
    int i;
    int head, freeL; /* リスト List の先頭，空きアドレスリストの先頭 */
    int x;
    char fname[128]; /* 読み込むファイルの名前を格納する変数 */
    FILE *fp;        /* ファイル名は 128 文字まで対応可能にする */

    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */

    fp = fopen(fname, "r"); /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d", &N);   /* N をファイルから読み込む */

    if (N > 50)
    {
        printf("N is too large, setting N = 50\n"); /* N が50を超えるときは警告をした上で */

        N = 50; /* N =50 に設定する */
    }
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%d", &Data[i]); /* 整数値を順に読み込み，Data に格納する */
    }
    fclose(fp); /* 開いたファイルを閉じる */

    for (i = 0; i < 49; i++) /* allocate_object, free_object のための初期化 */
    {
        List[i].next = i + 1;
    }
    List[49].next = -1;
    head = -1;
    freeL = 0; /* head freeL の初期化 */

    for (i = 0; i < N; i++)
    {
        x = allocate_object(List, &freeL);
        List_Insert(List, &head, &x);
        List[x].key = Data[i];
    }

    for (i = 0; i < N; i++)
    {
        x = List_Minimum(List, &head);
        Data[i] = List[x].key;
        List_Delete(List, &head, &x);
        Free_Object(List, &freeL, &x);
    }

    for (i = 0; i < N; i++)
    {
        printf("%d\n", Data[i]);
    }
}
/* 主要部分(各自作成) */
/*以下，関数 allocate object のコード*/
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
void List_Insert(struct cell *L, int *head, int *x)
{
    L[*x].next = *head;
    *head = *x;
}
int List_Minimum(struct cell *L, int *head)
{
    int x, y;
    int min = 1000000;
    x = *head;
    y = x;
    while (x != -1)
    {
        if (L[x].key < min)
        {
            min = L[x].key;
            y = x;
        }
        x = L[x].next;
    };
    return y;
}
void List_Delete(struct cell *L, int *head, int *x)
{
    int y;
    y = *head;
    if (*head == *x)
    {
        *head = L[*x].next;
    }
    else
    {
        while (L[y].next != *x)
        {
            y = L[y].next;
        }
        L[y].next = L[*x].next;
    }
}
void Free_Object(struct cell *L, int *f, int *x)
{
    L[*x].next = *f;
    *f = *x;
}