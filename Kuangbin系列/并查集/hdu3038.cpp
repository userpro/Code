#include <cstdio>
#include <cstring>

#define MAXN 200010
int N, M, par[MAXN], val[MAXN];

int findd(int x)
{
    if (par[x] == -1) return x;
    int t = findd(par[x]);
    val[x] += val[par[x]];
    return par[x] = t;
}

int main()
{
    while (scanf("%d%d", &N, &M) > 1 && N)
    {
        int A, B, S, ans = 0;
        memset(par, -1, sizeof(par));
        memset(val, 0, sizeof(val));
        for (int i = 0; i < M; ++i)
        {
            scanf("%d%d%d", &A, &B, &S);
            A = A - 1;
            int t1 = findd(A);
            int t2 = findd(B);
            if (t1 != t2)
            {
                par[t2] = t1;
                val[t2] = val[A] - val[B] + S;
            } else {
                if (val[B] - val[A] != S) ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}