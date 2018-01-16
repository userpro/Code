#include <cstdio>
#include <cstring>
#include <cstdlib>

#define MAXN 30010
int N, M, par[MAXN];

int findd(int x)
{
    return x == par[x] ? x : par[x] = findd(par[x]);
}

void unite(int x, int y)
{
    int a = findd(x), b = findd(y);
    if (a != b)
        par[a] = b;
}

int main()
{
    while (scanf("%d%d", &N, &M) > 1 && N)
    {
        for (int i = 0; i < N; ++i)
            par[i] = i;
        int k, k1, ki;
        for (int i = 0; i < M; ++i)
        {
            scanf("%d%d", &k, &k1);
            for (int j = 0; j < k-1; ++j)
            {
                scanf("%d", &ki);
                unite(k1, ki);
            }
        }
        int ans = 0;
        for (int i = 0; i < N; ++i)
            if (findd(i) == par[0])
                ans++;
        printf("%d\n", ans);
    }
    return 0;
}