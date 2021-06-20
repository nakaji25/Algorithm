#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#include <math.h>
int powk(int k, int p)
{
    int i, l;
    l = k;
    for (i = 0; i < p - 1; i++)
    {
        k *= l;
    }
    return k;
}
int main()
{
    int k, p, d;
    scanf("%d", &k);
    scanf("%d", &p);
    d = powk(k, p);
    printf("%d\n", d);
}