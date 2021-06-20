#include <stdio.h>

void nijou(int n[5])
{
    int i;

    printf("各値を二乗します。\n");
    for (i = 0; i < 5; i++)
    {
        n[i] = n[i] * n[i];
    }

    for (i = 0; i < 5; i++)
    {
        printf("%d\n",n[i]);
    }
}

int main()
{
    int i;
    int n[5];

    printf("配列の要素を整数で５つ入力してください。\n");

    for (i = 0; i < 5; i++)
    {
        scanf("%d", &n[i]);
    }

    nijou(n);

    return 0;
}