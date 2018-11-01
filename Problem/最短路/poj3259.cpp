// Bellman判环
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define INF 1<<20
#define MAX 5210
typedef struct _pos
{
    int from, to;
    int cost;
}pos;
pos E[MAX];
int D[MAX];
int A, N, M, W, i, j, k;

bool Bellman_Ford()
{
    for (i = 1; i <= N; ++i) D[i] = INF;
    D[1] = 0;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M*2 + W; ++j)
            if (D[E[j].to] > D[E[j].from] + E[j].cost)
                D[E[j].to] = D[E[j].from] + E[j].cost;

    for (j = 1; j <= M*2 + W; ++j)
        if (D[E[j].to] > D[E[j].from] + E[j].cost)
            return true;
    return false;
}

int main()
{
    while (scanf("%d", &A) != EOF && A > 0)
    {
        while (A--)
        {
            scanf("%d%d%d", &N, &M, &W);
            pos tmp;
            j = 1;
            for (i = 1; i <= M; ++i)
            {
                scanf("%d%d%d", &tmp.from, &tmp.to, &tmp.cost);
                E[j++] = tmp;
                swap(tmp.from, tmp.to);
                E[j++] = tmp;
            }

            for (; i <= M + W; ++i)
            {
                scanf("%d%d%d", &tmp.from, &tmp.to, &tmp.cost);
                tmp.cost = -tmp.cost;
                E[j++] = tmp;
            }

            if (Bellman_Ford())
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}