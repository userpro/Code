#include <cstdio>
#include <cstring>

#define INF 1<<20
#define MAX_N 110
bool W[MAX_N][MAX_N];
int D[MAX_N];
int N, M, i, j, k, l;

int main()
{
    int N, M;
    while (scanf("%d%d", &N, &M) > 1 && N)
    {
        memset(D, 0, sizeof(D));
        memset(W, 0, sizeof(W));
        for (i = 1; i <= M; ++i)
        {
            scanf("%d%d", &j, &k);
            W[j][k] = 1;
        }

        for (i = 1; i <= N; ++i)
            for (j = 1; j <= N; ++j)
                for (k = 1; k <= N; ++k)
                    if (W[j][i] && W[i][k])
                        W[j][k] = 1;

        for (i = 1; i <= N; ++i)
            for (j = 1; j <= N; ++j)
            {
                D[i] += W[i][j];
                D[j] += W[i][j];
            }

        l = 0;
        for (i = 1; i <= N; ++i)
            if (D[i] == N - 1)
                l++;

        printf("%d\n", l);
    }
    return 0;
}