#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
#define MAXN 10010
#define dis(a,b) (sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)))
struct Node
{
    int x,y;
}node[MAXN];
struct Edge
{
    int u,v;
    double c;
    Edge(int _u,int _v,double _c):u(_u),v(_v),c(_c) {}
};
int N,M;
int F[MAXN];
vector<Edge> E,pre;

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
    E.clear();
    pre.clear();
    memset(F,-1,sizeof(F));

    scanf("%d",&N);
    for (int i = 1; i <= N; ++i)
    {
        scanf("%d%d",&node[i].x,&node[i].y);
        for (int j = 1; j < i; ++j)
            E.push_back(Edge(i,j,dis(node[i],node[j])));
    }
    sort(E.begin(), E.end(), cmp);

    scanf("%d",&M);
    int u,v;
    for (int i = 0; i < M; ++i)
    {
        scanf("%d%d",&u,&v);
        int a=findd(u),b=findd(v);
        if (a!=b) F[a]=b;
    }

    for (int i = 0; i < E.size(); ++i)
    {
        int a=findd(E[i].u),b=findd(E[i].v);
        if (a!=b)
        {
            F[a]=b;
            pre.push_back(E[i]);
        }
    }

    for (int i = 0; i < pre.size(); ++i)
        printf("%d %d\n", pre[i].u,pre[i].v);
    return 0;
}