#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    int random1[1000000];
    int random2[10000];
    int ans[100];
    int i, j, min = 0, max = 100;

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
    for (i = 0; i < 10000; i++)
    {
        printf("%d:%d\n", i, random2[i]);
    }
}