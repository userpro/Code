#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define inf 0x3f3f3f3f

const int maxn=10010;
vector<int> g[maxn];
int color[maxn],dfn[maxn<<1],low[maxn<<1],stack[maxn<<1],vis[maxn],cnt[maxn];
int deep,top,sum;

void tarjan(int u)
{
    dfn[u]=++deep;
    low[u]=deep;
    vis[u]=1;
    stack[++top]=u;
    int sz=g[u].size();
    for(int i=0;i<sz;i++)
    {
        int v=g[u][i];
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
        {
            if(vis[v])
            {
                low[u]=min(low[u],low[v]);
            }
        }
    }
    if(dfn[u]==low[u])
    {
        color[u]=++sum;
        vis[u]=0;
        while(stack[top]!=u)
        {
            color[stack[top]]=sum;
            vis[stack[top--]]=0;
        }
        top--;
    }
}

void _init()
{
    for (int i=0;i<maxn;i++) g[i].clear();
    deep=top=sum=0;
    memset(color,0,sizeof(color));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(stack,0,sizeof(stack));
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
}

int n,m;
int main()
{
    while (scanf("%d%d",&n,&m))
    {
        _init();
        for(int i=1;i<=m;i++)
        {
            int from,to;
            scanf("%d%d",&from,&to);
            g[from].push_back(to);
        }
        for(int i=1;i<=n;i++)
        {
            if(!dfn[i])
            {
                tarjan(i);
            }
        }
        for(int i=1;i<=n;i++)
        {
            cnt[color[i]]++;
        }

        int ans=0;
        for(int i=1;i<=sum;i++)
        {
            if(cnt[i]>1)
            {
                ans++;
            }
        }
        printf("%d\n",ans);
    }
}