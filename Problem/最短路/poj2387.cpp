#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 2001
typedef struct _edge
{
    int from, to;
    int cost;
} edge;
edge E[MAX*2];
int D[MAX];
int T, N, i, j, k;

int main()
{
    while (scanf("%d %d", &T, &N) != EOF && T)
    {
        memset(D, 0x7f, sizeof(D));
        edge temp;
        i = 1;
        k = T;
        while (k--)
        {
            scanf("%d %d %d", &temp.from, &temp.to, &temp.cost);
            E[i++] = temp;
            swap(temp.from, temp.to);
            E[i++] = temp;
        }

        D[N] = 0;
        for (i = 1; i <= N - 1; ++i)
            for (j = 1; j <= T*2; ++j)
            {
                if (D[E[j].to] > D[E[j].from] + E[j].cost)
                    D[E[j].to] = D[E[j].from] + E[j].cost;
            }

        printf("%d\n", D[1]);
    }
    return 0;
}