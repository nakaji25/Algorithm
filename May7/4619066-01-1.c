#include <stdio.h>

int urudosi(int y)
{
    int u = 0;

    if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
    {
        u++;
    }

    return u;
}

void month(int u, int y, int m)
{
    if (u == 1 && m == 2)
    {
        printf("西暦%d年%d月は29日です。\n", y, m);
    }
    else if ((m % 2 == 1 & m < 8) || (m % 2 == 0 & m >= 8))
    {
        printf("西暦%d年%d月は31日です。\n", y, m);
    }
    else if (m == 2)
    {
        printf("西暦%d年%d月は28日です。\n", y, m);
    }
    else
    {
        printf("西暦%d年%d月は30日です。\n", y, m);
    }
}

int main()
{
    int y = 0;
    int m = 0;
    int u = 0;
    int r = 1;

    printf("西暦何年の何月の日数が知りたいですか？\n");

    while (r == 1)
    {
        scanf("%d", &y);
        scanf("%d", &m);

        if (m > 12)
        {
            printf("1~12の間で入力して下さい。\n");
            r--;
        }

        r++;
    }

    u = urudosi(y);

    month(u, y, m);
    return 0;
}