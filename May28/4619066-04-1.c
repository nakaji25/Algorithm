#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */

struct node /* 構造体 node の定義 */
{
    int key;
    struct node *parent;
    struct node *left;
    struct node *right;
};
/* 関数 tree_search, tree_minimum, tree_insert の宣言 */
struct node *tree_search(struct node *x, int a);
struct node *tree_minimum(struct node *x);
struct node *tree_maximum(struct node *x);
struct node *tree_insert(struct node *Tree, struct node *x);
void inorder_tree_walk(struct node *x);
struct node *tree_delete(struct node *Tree, struct node *z);
/* (他の関数も宣言すること) */
int main(void)
{
    struct node *Tree;      /* 2分探索木を表す変数は Tree */
    struct node *x, *y, *z; /* 挿入，削除等に用いる node 型変数 */

    int N;        /* 数値の数は N */
    int Data[50]; /* 数値を格納する配列は Data */
    int i;
    int a;
    char fname[128]; /* 読み込むファイルの名前を格納する変数 */
    FILE *fp;        /* ファイル名は 128 文字まで対応可能にする */

    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */
    fp = fopen(fname, "r");             /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d", &N);               /* N をファイルから読み込む */

    if (N > 50)
    {
        printf("N is too large, setting N = 50\n"); /* N が 50 を超えるときは警告をした上で */
        N = 50;                                     /* N =50 に設定する */
    }           
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%d", &Data[i]); /* 整数値を順に読み込み，Data に格納する */
    }
    fclose(fp);             /* 開いたファイルを閉じる */
    Tree = NULL;            /* Tree の初期化，最初は空 */
                            /* Tree は2分探索木の根を指す*/
    for (i = 0; i < N; i++) /* データ挿入部分のくりかえし */
    {
        x = (struct node *)malloc(sizeof(struct node));
        x->key = Data[i]; /* 新しい頂点 x を生成して key などを指定 */
        x->parent = x->left = x->right = NULL;
        Tree = tree_insert(Tree, x); /* x を Tree に挿入して根の情報を更新*/
        /* ループ主要部分(各自作成) */
        printf("key in tree: ");
        inorder_tree_walk(Tree);
        printf("\n");
        x = tree_minimum(Tree);
        printf("min: %d\n", x->key);
        x = tree_maximum(Tree);
        printf("max: %d\n", x->key);
    }
    for (i = 0; i < N; i++) /* データ削除部分のくりかえし */
    {
        /* ループ主要部分(各自作成) */
        a = Data[i];
        z = tree_search(Tree, a);
        Tree = tree_delete(Tree, z);
        printf("key in tree: ");
        if (Tree == NULL)
        {
            printf("NULL\n");
        }
        else
        {
            inorder_tree_walk(Tree);
            printf("\n");
            x = tree_minimum(Tree);
            printf("min: %d\n", x->key);
            x = tree_maximum(Tree);
            printf("max: %d\n", x->key);
        }
    }
    
   
    return 0;
}
/*以下，関数 tree insert の冒頭部分:*/

struct node *tree_insert(struct node *T, struct node *x)
{
    struct node *r, *y, *z;
    r = T; /* 根を変数 r に格納 */
    y = NULL;
    z = r;
    /* 主要部分(各自作成) */
    while (z != NULL)
    {
        if (z->key > x->key)
        {
            y = z;
            z = z->left;
        }
        else
        {
            y = z;
            z = z->right;
        }
    }
    x->parent = y;
    if (y == NULL)
    {
        r = x;
    }
    else
    {
        if (y->key > x->key)
        {
            y->left = x;
        }
        else
        {
            y->right = x;
        }
    }

    return (r);
}
void inorder_tree_walk(struct node *x)
{
    if (x != NULL)
    {
        inorder_tree_walk(x->left);
        printf("%d ", x->key);
        inorder_tree_walk(x->right);
    }
}
struct node *tree_search(struct node *x, int a)
{
    while ((x != NULL) && (x->key != a))
    {
        if (a < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return x;
}
struct node *tree_minimum(struct node *x)
{
    while (x->left != NULL)
    {
        x = x->left;
    }
    return x;
}
struct node *tree_maximum(struct node *x)
{
    while (x->right != NULL)
    {
        x = x->right;
    }
    return x;
}

struct node *tree_delete(struct node *T, struct node *z)
{
    struct node *r, *y, *x, *p;
    r = T;
    if ((z->right == NULL) || (z->left == NULL))
    {
        y = z;
    }
    else
    {
        y = tree_minimum(z->right);
    }

    p = y->parent;

    if (y->right != NULL)
    {
        x = y->right;
    }
    else if (y->left != NULL)
    {
        x = y->left;
    }
    else
    {
        x = NULL;
    }

    if (x != NULL)
    {
        x->parent = p;
    }

    if (p == NULL)
    {
        r = x;
    }
    else
    {
        if (y == p->left)
        {
            p->left = x;
        }
        else
        {
            p->right = x;
        }
    }
    if (y != z)
    {
        z->key = y->key;
    }

    free(y);

    return r;
}