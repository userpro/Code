// 并查集
#include <cstdio>
#include <cstring>

#define MAX 1010
int fa[MAX];
int T, N, M, ans;

void init(int n)
{
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
}

int findd(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = findd(fa[x]);
}

void unite(int x, int y)
{
    x = findd(x);
    y = findd(y);
    if (x == y) return;
    else fa[y] = x;
}

int main()
{
    while (scanf("%d", &T) > 0 && T)
    {
        for (int l = 0; l < T; ++l)
        {
            int u, v;
            scanf("%d%d", &N, &M);
            init(N);
            for (int i = 1; i <= M; ++i)
            {
                scanf("%d%d", &u, &v);
                unite(u, v);
            }
            ans = 0;
            for (int i = 1; i <= N; ++i)
                if (findd(i) == i)
                    ans++;
            printf("%d\n", ans);
        }
    }
    return 0;
}

// DFS求连通块
// #include <cstdio>
// #include <cstring>

// #define MAX 1010
// bool vis[MAX];
// bool mp[MAX][MAX];
// int T, N, M, ans;

// void dfs(int start)
// {
//     vis[start] = 1;
//     for (int i = 1; i <= N; ++i)
//         if (!vis[i] && mp[start][i])
//         {
//             vis[i] = 1;
//             dfs(i);
//         }
// }

// int main()
// {
//     while (scanf("%d", &T) > 0 && T)
//     {
//         for (int l = 0; l < T; ++l)
//         {
//             int u, v;
//             memset(vis, 0, sizeof(vis));
//             memset(mp, 0, sizeof(mp));
//             scanf("%d%d", &N, &M);
//             for (int i = 1; i <= M; ++i)
//             {
//                 scanf("%d%d", &u, &v);
//                 mp[u][v] = mp[v][u] = 1;
//             }
//             ans = 0;
//             for (int i = 1; i <= N; ++i)
//                 if (!vis[i])
//                 {
//                     ans++;
//                     dfs(i);
//                 }
//             printf("%d\n", ans);
//         }
//     }
//     return 0;
// }