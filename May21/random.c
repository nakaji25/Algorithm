#include <stdio.h>
#include <time.h>
#include "MT.h"

int main(void)
{
    FILE *fp;
    int i, n;

    printf("データの個数入力してください。\n");
    scanf("%d", &n);

    fp = fopen("random.txt", "w");
    init_genrand((unsigned)time(NULL));
    fprintf(fp, "%d\n", n);
    for (i = 0; i < n; i++)
    {
        fprintf(fp, "%ld\n", genrand_int32() % (99 - 1) + 1);
    }

    fclose(fp);

    return 0;
}