#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define INF 1<<20
#define MAX 10010
typedef struct _pos
{
    int from, to;
    int cost;
}pos;
pos E[MAX];
int D[MAX];
int n, i, j, k, l, m;

void Bellman_Ford()
{
    for (i = 1; i <= n; ++i) D[i] = INF;
    D[1] = 0;
    m = n*(n-1)/2;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m*2; ++j)
            if (D[E[j].to] > D[E[j].from] + E[j].cost)
                D[E[j].to] = D[E[j].from] + E[j].cost;
}

int main()
{
    while (scanf("%d", &n) > 0 && n)
    {
        pos tmp;
        l = 1;
        for (i = 2; i <= n; ++i)
        {
            for (j = 1; j < i; ++j)
            {
                if (!scanf("%d", &k))
                {
                    getchar(); getchar();
                    k = INF;
                }
                tmp.from = i; tmp.to = j; tmp.cost = k;
                E[l++] = tmp;
                swap(tmp.from, tmp.to);
                E[l++] = tmp;
            }
        }

        Bellman_Ford();

        k = 0;
        for (i = 1; i <= n; ++i)
            if (k < D[i])
                k = D[i];
        printf("%d\n", k);
    }
    return 0;
}