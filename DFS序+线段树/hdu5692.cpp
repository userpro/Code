// DFS序+线段树
#pragma comment(linker, "/STACK:1024000000,1024000000") 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;
#define INF ((LL)1E18)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define MAXN 100010

vector<int> G[MAXN];
int T,n,m;
int tot;
LL dis[MAXN],cost[MAXN];
int le[MAXN<<1],ri[MAXN<<1],num[MAXN];
void dfs(int u,int fa)
{
    tot++;
    num[tot]=u;
    le[u]=ri[u]=tot;
    int sz=G[u].size();
    for (int i=0;i<sz;i++)
    {
        int v=G[u][i];
        if (v!=fa)
        {
            dis[v]=dis[u]+cost[v];
            dfs(v,u);
            ri[u]=max(ri[u],ri[v]);
        }
    }
}

struct SegTree
{
    #define Mid ((l+r)>>1)
    #define lson l,m,rt<<1
    #define rson m+1,r,rt<<1|1
    LL _sum[MAXN<<2], _lazy[MAXN<<2];

    void PushDown(int rt)
    {
        if (_lazy[rt])
        {
            _sum[rt << 1] += _lazy[rt];  
            _sum[rt << 1 | 1] += _lazy[rt];  
            _lazy[rt << 1] += _lazy[rt];  
            _lazy[rt << 1 | 1] += _lazy[rt];  
            _lazy[rt] = 0; 
        }
    }

    inline void PushUp(int rt)
    {
        _sum[rt]=max(_sum[rt<<1],_sum[rt<<1|1]);
    }

    void Build(LL l, LL r, LL rt)
    {
        _lazy[rt]=0;
        if (l==r)
        {
            _sum[rt]=dis[num[l]];
            return;
        }
        LL m=Mid;
        Build(lson);
        Build(rson);
        PushUp(rt);
    }

    void UpdateRange(LL L, LL R, LL val, LL l, LL r, LL rt)
    {
        if (L<=l && r<=R)
        {
            _sum[rt]+=val;
            _lazy[rt]+=val;
            return;
        }
        LL m=Mid;
        PushDown(rt);
        if (L<=m) UpdateRange(L,R,val,lson);
        if (R>m) UpdateRange(L,R,val,rson);
        PushUp(rt);
    }

    void UpdateOne(LL pos, LL val, LL l, LL r, LL rt)
    {
        if (l==r && r==pos)
        {
            _sum[rt]=val;
            return;
        }
        LL m=Mid;
        if (pos<=m) UpdateOne(pos,val,lson);
        else UpdateOne(pos,val,rson);
        PushUp(rt);
    }

    LL Query(LL L, LL R, LL l, LL r, LL rt)
    {
        if (L<=l && r<=R)
            return _sum[rt];
        LL m=Mid;
        PushDown(rt);
        LL ans=-INF;
        if (L<=m) ans=max(ans,Query(L,R,lson));
        if (R>m) ans=max(ans,Query(L,R,rson));
        return ans;
    }
};

SegTree st;
void _init()
{
    for (int i=0;i<MAXN;i++)
        G[i].clear();
    tot=0;
}

int main()
{
    int cnt=0;
    int u,v;
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            printf("Case #%d:\n", ++cnt);
            _init();
            scanf("%d%d",&n,&m);
            for (int i=0;i<n-1;i++)
            {
                scanf("%d%d",&u,&v);
                G[u].push_back(v);
                G[v].push_back(u);
            }
            for (int i=0;i<n;i++)
                scanf("%lld",&cost[i]);

            dis[0]=cost[0];
            dfs(0,-1);
            st.Build(1,n,1);

            int a,b;
            while (m--)
            {
                int op,x;
                LL y;
                scanf("%d",&op);
                if (op==1)
                {
                    scanf("%d",&x);
                    printf("%lld\n", st.Query(le[x],ri[x],1,n,1));
                }
                else
                {
                    scanf("%d%lld",&x,&y);
                    st.UpdateRange(le[x],ri[x],y-cost[x],1,n,1);
                    cost[x]=y;
                }
            }
        }
    }
    return 0;
}