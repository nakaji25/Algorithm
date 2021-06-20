#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    int random1[1000000];
    int random2[10000];
    int ans[100] = {0};
    int i, j, min = 0, max = 99;

    fp = fopen("random.txt", "r");
    if (fp == NULL)
    {
        printf("file open error!!\n");
        exit(1);
    }
    for (i = 0; i < 1000000; i++)
    {
        fscanf(fp, "%d", &random1[i]);
    }
    fclose(fp);

    for (j = 0; j < 10000; j++)
    {
        for (i = min; i < max; i++)
        {
            random2[j] += random1[i];
        }
        min += 100;
        max += 100;
    }

    min = 0;
    max = 99;

    printf("100万のデータを100個ずつの和にして各範囲の生起回数を表示します。\n");
    printf("なお0個の範囲は表示しません。\n");
    for (j = 0; j < 100; j++)
    {
        for (i = 0; i < 10000; i++)
        {
            if (min <= random2[i] && max >= random2[i])
            {
                ans[j]++;
            }
        }
        if (ans[j] != 0)
        {
            printf("%d~%dの値は%4d個\n", min, max, ans[j]);
        }
        min += 100;
        max += 100;
    }
    return 0;
}