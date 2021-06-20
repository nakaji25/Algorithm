#include <stdio.h>
#include <math.h>

int r = 100000;

double siki(double xn0, double a)
{
    double xn1;

    xn1 = a * xn0 * xn0 + 1;

    if (fabs(xn1 - xn0) < 0.00001)
    {
        return xn1;
    }
    else if (r <= 0)
    {
        return -1;
    }

    r--;
    return siki(xn1, a);
}

int main()
{
    double xn0, xn1;
    double a;
    printf("X0の値を入力して下さい。\n");
    scanf("%lf", &xn0);
    printf("aの値を入力して下さい。\n");
    scanf("%lf", &a);

    xn1 = siki(xn0, a);

    if (xn1 == -1)
    {
        printf("収束しませんでした。\n");
    }
    else
    {
        printf("%lfに収束しました。\n", xn1);
    }
}