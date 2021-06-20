#include <stdio.h>

typedef struct Person
{
    double height;
    double weight;
    char blood[2];
} Person1;

void output(int N, Person1 *P1)
{
    int i = 0;
    for (i = 0; i < N; i++)
    {
        printf("%d:%.1fcm,%.1fkg,%s型\n", i + 1, (P1 + i)->height, (P1 + i)->weight, (P1 + i)->blood);
    }
}

void input(int N, Person1 *P1)
{
    int i = 0;
    printf("身長(cm)、体重(kg)、血液型の順番で入力してください。\n");
    for (i = 0; i < N; i++)
    {
        scanf("%lf %lf %s", &P1[i].height, &P1[i].weight, P1[i].blood);
    }
}

int main()
{
    int i;
    int N, height, weight;
    char blood[2];

    printf("何人の生徒のデータを入力しますか？\n");
    scanf("%d", &N);

    Person1 P1[N];

    input(N, P1);

    output(N, P1);

    return 0;
}