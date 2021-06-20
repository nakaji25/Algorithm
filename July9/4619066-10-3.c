#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
#define inf 1000000
int Adj[maxN][maxN];                      /* 隣接行列 */
int d[maxN], f[maxN], p[maxN], color[50]; /* 配列変数 d,f, p, color */
int T;

void Traverse(int N, int v);
void DFS(int N);

int main(void) {
  int N, M; /* N:頂点の数、M:枝の数 */
  int v0;   /* 始点の変数 */
  int u, v;
  int i;

  char fname[128];
  FILE *fp;

  printf("input filename: ");
  fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
  fname[strlen(fname) - 1] = '\0'; /* 最後の改行コードを除去 */
  fflush(stdin);

  fp = fopen(fname, "r");
  fscanf(fp, "%d %d", &N, &M);

  for (u = 0; u < N; u++) {
    for (v = 0; v < N; v++) {
      Adj[u][v] = 0; /* 隣接行列の初期化 */
    }
  }

  for (i = 0; i < M; i++) {
    fscanf(fp, " %d %d", &u, &v); /* 隣接行列に値を入力 */
    Adj[u][v] = 1;
    Adj[v][u] = 1;
  }

  fscanf(fp, " %d", &v0);
  fclose(fp);

  DFS(N);

  for (i = 0; i < N; i++) {
    printf("vertex: d[%d] = %d,p[%d] = %d,f[%d] = %d\n", i, d[i], i, p[i], i,
           f[i]);
  }
}

void DFS(int N) {
  int i;
  for (i = 0; i < N; i++) {
    color[i] = 0;
    f[i] = inf;
    d[i] = inf;
    p[i] = -1;
  }
  T = 0;
  for (i = 0; i < N; i++) {
    if (color[i] == 0) {
      Traverse(N, i);
    }
  }
}
void Traverse(int N, int v) {
  int u;
  color[v] = 1;
  T = T + 1;
  d[v] = T;
  for (u = 0; u < N; u++) {
    if (Adj[u][v] == 1) {
      if (color[u] == 0) {
        p[u] = v;
        Traverse(N, u);
      }
    }
  }
  color[v] = 2;
  T = T + 1;
  f[v] = T;
}