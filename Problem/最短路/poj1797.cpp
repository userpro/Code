#include <cstdio>
#include <cstring>

#define MAX 1010
#define min(a,b) (a<b?a:b)
bool vis[MAX];
int we[MAX], mp[MAX][MAX];
int main()
{
    int S, N, M, i, j, k, l, m;
    scanf("%d", &S);
    m = 1;
    while (S--)
    {   
        while (scanf("%d%d", &N ,&M) != EOF)
        {
            memset(vis, 0, sizeof(vis));
            memset(mp, 0, sizeof(mp));
            memset(we, 0, sizeof(we));
            for (i = 1; i <= M; ++i)
            {
                scanf("%d%d%d", &j, &k, &l);
                mp[j][k] = mp[k][j] = l;
            }

            for (i = 1; i <= N; ++i)
                we[i] = mp[1][i];

            for (i = 1; i <= N; ++i)
            {
                k = -1;
                for (j = 1; j <= N; ++j)
                {
                    if (!vis[j] && we[j] > k)
                    {
                        k = we[j];
                        l = j;
                    }
                }
                vis[l] = 1;
                if (l == N) break;
                for (j = 1; j <= N; ++j)
                {
                    if (!vis[j] && we[j] < min(mp[l][j], we[l]))
                        we[j] = min(mp[l][j], we[l]);
                }
            }

            printf("Scenario #%d:\n", m++);
            printf("%d\n\n", we[N]);
        }
    }
    return 0;
}