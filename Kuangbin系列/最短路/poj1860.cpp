#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef struct _pos
{
    int from, to;
    double r, c;
}pos;
#define MAX 1010
pos E[MAX];
double MONEY[MAX];
int N, M, S, i, j;
double V;

bool Bellman_Ford()
{
    MONEY[S] = V;
    for (i = 1; i <= N; ++i)
    {
        for (j = 1; j <= M * 2; ++j)
            if (MONEY[E[j].to] < E[j].r * (MONEY[E[j].from] - E[j].c))
                MONEY[E[j].to] = E[j].r * (MONEY[E[j].from] - E[j].c);
        if (MONEY[S] > V) return true;
    }

    for (j = 1; j <= M * 2; ++j)
        if (MONEY[E[j].to] < E[j].r * (MONEY[E[j].from] - E[j].c))
            return true;
    return false;
}

int main()
{
    while (scanf("%d%d%d%lf", &N, &M, &S, &V) != EOF && N)
    {
        pos tmp;
        memset(MONEY, 0, sizeof(MONEY));
        j = 1;
        for (i = 0; i < M; ++i)
        {
            scanf("%d%d", &tmp.from, &tmp.to);
            scanf("%lf%lf", &tmp.r, &tmp.c);
            E[j++] = tmp;
            swap(tmp.from, tmp.to);
            scanf("%lf%lf", &tmp.r, &tmp.c);
            E[j++] = tmp;
        }

        if (Bellman_Ford())
            printf("YES\n");
        else
            printf("NO\n");

    }
    return 0;
}