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
int T,N;
int F[MAXN];
vector<Edge> E;

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x]=findd(F[x]);
}

bool cmp(Edge e1,Edge e2)
{
    return e1.c<e2.c;
}

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        E.clear();
        memset(F,-1,sizeof(F));
        scanf("%d",&N);
        for (int i = 0; i < N; ++i)
        {
            scanf("%d%d",&node[i].x,&node[i].y);
            for (int j = 0; j < i; ++j)
            {
                double d=dis(node[i],node[j]);
                if (d>=10&&d<=1000)
                    E.push_back(Edge(i,j,d));
            }
        }
        sort(E.begin(), E.end(), cmp);

        int cnt=0;
        double ans=0;
        for (int i = 0; i < E.size(); ++i)
        {
            int a=findd(E[i].u),b=findd(E[i].v);
            if (a!=b)
            {
                F[a]=b;
                ans+=E[i].c;
                cnt++;
            }
        }
        if (cnt==N-1)
            printf("%.1f\n", ans*100);
        else
            printf("oh!\n");
    }
    return 0;
}