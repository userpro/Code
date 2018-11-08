// hdu5988 最小费用最大流 Tips: log将乘转换为加
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn=210;
const int inf=1<<29;
const double eps=1e-8;
struct Edge
{
    int from,to,cap,flow;
    double cost;
    Edge() {}
    Edge(int from,int to,int cap,int flow,double cost):from(from),to(to),cap(cap),flow(flow),cost(cost) {}
};

struct MCMF
{
    int n,m,s,t;
    vector<Edge> edges;
    vector<int> G[maxn];
    int inq[maxn];
    double d[maxn];
    int p[maxn];
    int a[maxn];

    void init(int n) {
        this->n=n;
        for (int i=0;i<n;i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from,int to,int cap,double cost) {
        edges.push_back(Edge(from,to,cap,0,cost));
        edges.push_back(Edge(to,from,0,0,-cost));
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BellmanFord(int s,int t,int &flow,double &cost) {
        for (int i=0;i<=n;i++) d[i]=inf;
        memset(inq,0,sizeof(inq));
        d[s]=0; inq[s]=1; p[s]=0; a[s]=inf;

        queue<int> Q;
        Q.push(s);
        while (!Q.empty()) {
            int u=Q.front(); Q.pop();
            inq[u]=0;
            for (int i=0;i<G[u].size();i++) {
                Edge &e=edges[G[u][i]];
                if (e.cap>e.flow && d[e.to]>d[u]+e.cost+eps) {
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=G[u][i];
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if (!inq[e.to]) { Q.push(e.to); inq[e.to]=1; }
                }
            }
        }
        if (d[t]==inf) return false;
        flow+=a[t];
        cost+=d[t]*a[t];
        int u=t;
        while (u!=s) {
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
        return true;
    }

    double Mincost(int s,int t) {
        int flow=0;
        double cost=0;
        while (BellmanFord(s,t,flow,cost));
        return cost;
    }
};

int t,n,m;
int a[maxn],b[maxn],c[maxn];
int main() {
    MCMF mc;
    scanf("%d",&t);
    while (t--) {
        scanf("%d%d",&n,&m);
        mc.init(n*2+1);
        int st=0,ed=n*2+1;
        for (int i=0;i<n;i++) {
            scanf("%d%d",&a[i],&b[i]);
            c[i]=a[i]-b[i];
        }
        int u,v,cap;
        double p;
        for (int i=0;i<m;i++) {
            scanf("%d%d%d%lf",&u,&v,&cap,&p);
            p=-log10(1-p);
            if (cap>0) mc.AddEdge(u,v,1,0);
            if (cap-1>0) mc.AddEdge(u,v,cap-1,p);
        }
        for (int i=0;i<n;i++) {
            if (c[i]>0) mc.AddEdge(st,i+1,c[i],0);
            else if (c[i]<0) mc.AddEdge(i+1,ed,-c[i],0);
        }
        double ans=mc.Mincost(st,ed);
        printf("%.2f\n", 1.0-pow(10,-ans));
    }
    return 0;
}

