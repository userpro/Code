#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define MAXN 1010
struct Edge
{
    int u,v,c;
    Edge(int _u,int _v,int _c):u(_u),v(_v),c(_c) {}
};
int T,N;
int price[MAXN],F[MAXN];
vector<Edge> E;

bool cmp(Edge e1,Edge e2)
{
    return e1.c<e2.c;
}

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x]=findd(F[x]);
}

int main()
{
    int t;
    scanf("%d",&T);
    for (int i = 0; i < T; ++i)
    {
        E.clear();
        memset(F,-1,sizeof(F));
        memset(price,0,sizeof(price));
        scanf("%d",&N);
        for (int j = 0; j < N; ++j)
            scanf("%d",&price[j]);
        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                scanf("%d",&t);
                if (j<=k) continue;
                E.push_back(Edge(j,k,t+price[j]+price[k]));
            }
        }
        sort(E.begin(), E.end(), cmp);

        int ans=0;
        for (int i = 0; i < E.size(); ++i)
        {
            int a=findd(E[i].u),b=findd(E[i].v);
            if (a!=b)
            {
                F[a]=b;
                ans+=E[i].c;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}