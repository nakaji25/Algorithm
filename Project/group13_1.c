/* 駒取りプログラム ver1.0 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxN 10000   /* キューに入れる数の最大値 */
#define N 65536      /* 2の16乗,盤面の全パターンの数 */
const int MOD = 500; /*ハッシュのmod値*/

typedef struct cell
{
    int parent;
    int key;
    int next;
} cell;

void bfs(int *Q, int *d, int *memory, cell *List, int *freeL, int s, int *maxd, int *maxb);
void addqueue(int *Q, int *m, cell *L, int *f, int *d, int *maxd, int *maxb, int p, int v);
void enqueue(int *Q, int a);
int dequeue(int *Q);
void symmetrymemory(int *memory, cell *L, int *f, int a);
int allocate_object(cell *L, int *f);
void chained_hash_insert(int *A, cell *L, int x);
int chained_hash_search(int *A, cell *L, int p);
int hash_val(int a);
void show(int board[][16], int *ans);

int head = 0, tail = 0; /* キューの先頭と末尾 */

int main(void)
{
    clock_t start_t, end_t;
    double utime;

    start_t = clock();

    int i, j;              /* 必要な変数を宣言 */
    int A = (1 << 16) - 1; /* 盤面の全てに駒が置いてある状態 */
    int ans[16];
    for (i = 0; i < 16; i++)
        ans[i] = -1;
    int board[16][16];
    for (i = 0; i < 16; i++)
    {
        board[i][0] = -1;
    }
    int count = 0;

    for (i = 0; i < 16; i++)
    {
        if (ans[i] != -1)
            continue;
        int memory[MOD]; /* 盤面の一つ前の手を保存する配列 ハッシュにするべきなやつ */
        for (j = 0; j < MOD; j++)
            memory[j] = -1;
        cell List[10000];
        for (j = 0; j < 10000; j++)
            List[j].next = j + 1;
        List[9999].next = -1;
        int freeL = 0;
        int d[N];             /* それぞれの盤面の深さを記録する配列 */
        int Q[maxN];          /* キューを表す変数 */
        int B = A ^ (1 << i); /* 1つ駒を除いた盤面を1つbitを反転させて作成 */
        int maxd = 0, maxb;   /*一番深いときとその盤面を保存*/
        d[B] = 0;
        int p = allocate_object(List, &freeL);
        List[p].key = B;
        List[p].parent = -1;
        chained_hash_insert(memory, List, p);
        bfs(Q, d, memory, List, &freeL, B, &maxd, &maxb);

        ans[i] = 15 - maxd;
        int pos = 0;
        int v = maxb;
        while (v != -1)
        {
            board[i][pos] = v;
            v = List[chained_hash_search(memory, List, v)].parent;
            pos++;
        }
        board[i][pos] = -1;
        int a, b;
        a = i;
        b = i / 4 * 4 + (3 - i % 4);
        ans[b] = 15 - maxd;
        for (j = 0; j < 3; j++)
        {
            a = (80 - 4 * a) % 17;
            b = (80 - 4 * b) % 17;
            ans[a] = 15 - maxd;
            ans[b] = 15 - maxd;
        }
    }

    end_t = clock();
    utime = (double)(end_t - start_t) / CLOCKS_PER_SEC; /* 差を取り秒に換算 */

    show(board, ans);
    printf("time = %lf\n\n", utime);
}

void bfs(int *Q, int *d, int *m, cell *L, int *f, int s, int *maxd, int *maxb)
{
    int i, v;
    enqueue(Q, s);
    while (head != tail)
    {
        v = dequeue(Q);
        for (i = 4; i <= 11; i++)
        { //縦向きの駒取りを探索
            if ((v >> i) & 1)
            {
                if (((v >> (i - 4)) & 1) ^ ((v >> (i + 4)) & 1))
                { //こまを取れるか確認して取れるならbitを反転させて保存する。
                    int p = v;
                    p ^= (273 << (i - 4));
                    if (chained_hash_search(m, L, p) == -1)
                    {
                        addqueue(Q, m, L, f, d, maxd, maxb, p, v); //幅優先探索の探索候補に加える
                    }
                }
            }
        }

        i = 1;
        while (i < 15)
        { //横向きの駒取りを探索
            if ((v >> i) & 1)
            {
                if (((v >> (i - 1)) & 1) ^ ((v >> (i + 1)) & 1))
                {
                    int p = v;
                    p ^= (7 << (i - 1));
                    if (chained_hash_search(m, L, p) == -1)
                    {
                        addqueue(Q, m, L, f, d, maxd, maxb, p, v);
                    }
                }
            }
            if (i % 2)
                i++;
            else
                i += 3;
        }
    }
}

void addqueue(int *Q, int *m, cell *L, int *f, int *d, int *maxd, int *maxb, int p, int v)
{
    d[p] = d[v] + 1; //深さを追加する
    int pos = allocate_object(L, f);
    L[pos].key = p;
    L[pos].parent = v;
    chained_hash_insert(m, L, pos);
    enqueue(Q, p);
    if (*maxd < d[p])
    { //もし来たことのない深さなら更新する
        *maxd = d[p];
        *maxb = p;
    }
    symmetrymemory(m, L, f, p);
}

void enqueue(int *Q, int a)
{
    Q[tail] = a;
    tail++;
    if (tail == maxN)
    {
        tail = 0;
    }
    if (tail == head)
    {
        printf("overflow from queue\n");
    }
}

int dequeue(int *Q)
{
    int a = -1;
    if (head == tail)
    {
        printf("underflow form queue\n");
    }
    else
    {
        a = Q[head];
        head++;
        if (head == maxN)
        {
            head = 0;
        }
    }
    return a;
}

void symmetrymemory(int *memory, cell *L, int *f, int a)
{ //反転と回転をメモリ―に入れる
    int i, j, b = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            b += ((a >> (i * 4 + j)) & 1) << (i * 4 + 3 - j); //aと左右対称の行列を作ってbに保存
        }
    }
    if (chained_hash_search(memory, L, b) == -1)
    {
        int pos = allocate_object(L, f);
        L[pos].key = b;
        chained_hash_insert(memory, L, pos); //memoryに探索済みとして記録
    }
    for (i = 0; i < 3; i++)
    {
        int c = 0; //90度回転させたものを一旦eに保存する
        for (j = 0; j < 16; j++)
        {
            c += ((a >> j) & 1) << (80 - 4 * j) % 17; //90度回転させてます説明むずいかも
        }
        if (chained_hash_search(memory, L, c) == -1)
        {
            int pos = allocate_object(L, f);
            L[pos].key = c;
            chained_hash_insert(memory, L, pos);
        }
        a = c; //aに回転させたものを代入する
        c = 0;
        for (j = 0; j < 16; j++)
        {
            c += ((b >> j) & 1) << (80 - 4 * j) % 17;
        }
        if (chained_hash_search(memory, L, c) == -1)
        {
            int pos = allocate_object(L, f);
            L[pos].key = c;
            chained_hash_insert(memory, L, pos);
        }
        b = c; //bに回転させたものを代入する
    }
}

void show(int board[][16], int *ans)
{
    int i, j, k;
    int A = (1 << 16) - 1, B;

    printf("最小値の答えの表を出力します\n");
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("%d ", ans[15 - (i * 4 + j)]);
        }
        printf("\n");
    }
    printf("\n");

    printf("最小の駒数になるとり方を表示します\n");
    for (i = 0; i < 16; i++)
    {
        if (board[i][0] == -1)
            continue;
        B = A ^ (1 << i);
        printf("initial configuration:\n");
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 4; k++)
            {
                printf("%d ", (B >> (15 - (j * 4 + k))) & 1);
            }
            printf("\n");
        }
        printf("\n");

        int cnt = 0, piece = ans[i];
        printf("transform sequence (in reverse)\n\n");
        while (board[i][cnt] != -1)
        {
            printf("value = %d, #piece = %d\n", board[i][cnt], piece++);
            int v = board[i][cnt];
            for (j = 0; j < 4; j++)
            {
                for (k = 0; k < 4; k++)
                {
                    printf("%d ", (v >> (15 - (j * 4 + k))) & 1);
                }
                printf("\n");
            }
            printf("\n");
            cnt++;
        }
    }
}

int allocate_object(cell *L, int *f)
{ /* リスト配列と空きアドレスリスト先頭はポインタ渡し */
    int x;
    if (*f == -1)
    {
        printf("error: out of space\n");
        x = -1;
    }
    /* 空きアドレスがなければエラーメッセージを表示 */
    else
    {
        x = *f;
        *f = L[*f].next;
    }
    return x;
}

void chained_hash_insert(int *A, cell *L, int x)
{
    int h;
    h = hash_val(L[x].key);
    L[x].next = A[h];
    A[h] = x;
}

int chained_hash_search(int *A, cell *L, int p)
{
    int x = A[hash_val(p)];
    while (x != -1 && L[x].key != p)
    {
        x = L[x].next;
    }
    return x;
}

int hash_val(int a)
{
    return a % MOD;
}