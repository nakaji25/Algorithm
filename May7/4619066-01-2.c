#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int q;
    int a;

    srand((unsigned int)time(NULL));
    q = rand() % 100;
    printf("0~99の範囲で数当てゲームを始めます。\n");

    while (1)
    {
        printf("値を入力してください。\n");
        scanf("%d", &a);
        if (a > 99)
        {
            printf("0~99の範囲で入力して下さい。\n");
        }

        if (a != q)
        {
            if (q - a >= 10)
            {
                printf("小さすぎます。\n");
            }
            else if (q - a <= -10)
            {
                printf("大きすぎます。\n");
            }
            else if (q - a < 10 && q - a > 0)
            {
                printf("小さいです。\n");
            }
            else if (q - a > -10 && q - a < 0)
            {
                printf("大きいです。\n");
            }
        }
        else
        {
            printf("正解です。\n数は%dでした。\n", q);
            break;
        }
    }
    return 0;
}