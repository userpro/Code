// 点分治模版题
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

const int maxn = 10010;
struct Edge
{
    int v,w;
    int next;
} edge[maxn<<1];
int head[maxn];
int sim[maxn]; // sim数组存以i为根节点的子树的节点数量（即子树大小）
int mxson[maxn]; // mxson数组存以i节点为根的子树中的最大子树
bool vis[maxn];
int Smer,MX; // Smer为这棵树（当前处理树）的大小. MX记录当前已经找到的最小 最大子树值.
int root,ans;

int N,K; // N个顶点 树中点对之间距离不超过K的
int cnt;

void add(int u,int v,int w)
{
    edge[cnt].v=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void getroot(int u,int fa)
{
    sim[u] = 1; mxson[u] = 0;
    for(int i = head[u];i!=-1;i = edge[i].next)
    {
        int v = edge[i].v;
        if(vis[v]||v == fa)continue;
        getroot(v,u);
        sim[u] = sim[u] + sim[v];
        mxson[u] = max(mxson[u],sim[v]);
    }
    mxson[u] = max(mxson[u],Smer - sim[u]);
    if(mxson[u]<MX){root = u; MX = mxson[u];}
}

int dis[maxn],dcnt;
void getdis(int u,int fa,int dist)
{
    dis[++dcnt]=dist;
    for (int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].v;
        if (vis[v]||v==fa) continue;
        getdis(v,u,dist+edge[i].w);
    }
    return;
}

int solve(int sta,int len1)
{
    dcnt=0;
    CLR(dis,0);
    getdis(sta,0,len1);
    sort(dis+1,dis+dcnt+1);
    int L=1,R=dcnt,ret=0;
    while (L<=R)
    {
        if (dis[R]+dis[L]<=K) 
        {
            ret=ret+R-L;
            L++;
        }
        else
            R--;
    }
    return ret;
}

void Divide(int tr)
{
    ans = ans + solve(tr,0);
    vis[tr] = true;
    for(int i = head[tr];i!=-1;i = edge[i].next)
    {
        int v = edge[i].v;
        if(vis[v])continue;
        ans = ans - solve(v,edge[i].w);
        Smer = sim[v]; root = 0;
        MX = INF; getroot(v,0);
        Divide(root);
    }
    return;
}

int main()
{
    while (scanf("%d%d",&N,&K)!=EOF && (N||K))
    {
        int u,v,w;
        cnt=0;
        CLR(head,-1);
        for (int i=0;i<N-1;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);
            add(v,u,w);
        }
        ans=0;
        CLR(vis,0);
        MX=INF; Smer=N; getroot(1,0);
        Divide(root);
        printf("%d\n", ans);
    }
    return 0;
}