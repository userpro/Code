#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
#define MAXN 510
#define dis(a,b) (sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)))
struct Node
{
    double x,y;
}node[MAXN];
struct Edge
{
    int u,v;
    double c;
    Edge(int _u,int _v,double _c):u(_u),v(_v),c(_c) {}
};
vector<Edge> E;
int N,S,P;
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
    scanf("%d",&N);
    while (N--)
    {
        E.clear();
        memset(F,-1,sizeof(F));
        scanf("%d%d",&S,&P);
        for (int i = 0; i < P; ++i)
        {
            scanf("%lf%lf",&node[i].x,&node[i].y);
            for (int j = 0; j < i; ++j)
                E.push_back(Edge(i,j,dis(node[i],node[j])));
        }
        sort(E.begin(), E.end(), cmp);

        vector<double> tmp;
        for (int i = 0; i < E.size(); ++i)
        {
            int a=findd(E[i].u),b=findd(E[i].v);
            if (a!=b)
            {
                F[a]=b;
                tmp.push_back(E[i].c);
            }
        }

        for (int i = 0; i < S-1; ++i)
            tmp.pop_back();

        printf("%.2f\n", *(max_element(tmp.begin(), tmp.end())));
    }
    return 0;
}