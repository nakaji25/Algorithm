#include <stdio.h>
#include <stdlib.h>

double ave(int n, double *ip)
{
    int i;
    double sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += ip[i];
    }
    return sum / n;
}

int main()
{
    int n, i;
    double *ip;
    double ave2;
    printf("受験者の人数を入力して下さい。\n");
    scanf("%d", &n);

    ip = (double *)malloc(n * sizeof(double));

    printf("各受験者の点数を入力してください。\n");
    for (i = 0; i < n; i++)
    {
        scanf("%lf", &ip[i]);
    }
    free(ip);

    ave2 = ave(n, ip);

    printf("受験者の平均は%.1f点\n", ave2);
    printf("点数一覧\n");
    for (i = 0; i < n; i++)
    {
        printf("%.1f点\n", ip[i]);
    }

    return 0;
}