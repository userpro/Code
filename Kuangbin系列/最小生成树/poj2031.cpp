#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
#define MAXN 110
#define MAXE 10010
#define dis(n1,n2) (sqrt((n1.x-n2.x)*(n1.x-n2.x)+(n1.y-n2.y)*(n1.y-n2.y)+(n1.z-n2.z)*(n1.z-n2.z)))
struct Node
{
    double x,y,z,r;
}node[MAXN];

struct Edge
{
    int fi,ti;
    double c;
    Edge(int _fi,int _ti,double _c):fi(_fi),ti(_ti),c(_c) {}
};
vector<Edge> E;
int N;
int F[MAXN];

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
    while (scanf("%d",&N)==1&&N)
    {
        E.clear();
        memset(F,-1,sizeof(F));
        for (int i = 0; i < N; ++i)
            node[i].x=node[i].y=node[i].z=node[i].r=0;
        
        for (int i = 0; i < N; ++i)
        {
            scanf("%lf%lf%lf%lf",&node[i].x,&node[i].y,&node[i].z,&node[i].r);
            for (int j=0;j<i;++j)
            {
                double t=dis(node[i],node[j]);
                t=t-node[i].r-node[j].r>0?t-node[i].r-node[j].r:0;
                E.push_back(Edge(i,j,t));
            }
        }
        sort(E.begin(), E.end(),cmp);
        double ans=0;
        for (int i = 0; i < E.size(); ++i)
        {
            int a=findd(E[i].fi),b=findd(E[i].ti);
            if (a!=b)
            {
                F[a]=b;
                ans+=E[i].c;
            }
        }

        printf("%.3f\n", ans);
    }
    return 0;
}