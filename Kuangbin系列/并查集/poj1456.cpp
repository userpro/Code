#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 10010
struct Node
{
    int p,d;
}node[MAXN];
int N;
int F[MAXN];

bool cmp(Node a, Node b)
{
    return a.p>b.p;
}

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x] = findd(F[x]);
}

int main()
{
    while (~scanf("%d", &N))
    {
        memset(F, -1, sizeof(F));
        int u,v;
        for (int i = 0; i < N; ++i)
            scanf("%d%d", &node[i].p, &node[i].d);
        sort(node, node+N, cmp);
        int ans = 0;
        for (int i=0; i<N; ++i)
        {
            int t=findd(node[i].d);
            if (t>0)
            {
                ans+=node[i].p;
                F[t]=t-1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}