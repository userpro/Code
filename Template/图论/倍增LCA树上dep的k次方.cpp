// bzoj5293
// 生成了一棵有根树, 多次询问这棵树上一段路径上所有节点深度的k 次方和, 而且每次的k 可能是不同的
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=3e5+1000;
const LL mod=998244353;
int n,m;
vector<int> G[maxn];
bool vis[maxn];
int bin[26],fa[maxn][26],depth[maxn];
LL sum[maxn][55];
 
inline LL qpow(LL x,int y)
{
    LL ret=1;
    while (y>0)
    {
        if (y&1) ret=ret*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ret;
}
 
void dfs(int u)
{
    for (int i=1;bin[i]<=depth[u];i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
 
    int sz=G[u].size();
    for (int i=0;i<sz;i++)
    {
        int v=G[u][i];
        if (v!=fa[u][0])
        {
            fa[v][0]=u;
            depth[v]=depth[u]+1;
            dfs(v);
        }
    }
}
 
void cal(int u)
{
    for (int i=1;i<=50;i++)
        sum[u][i]=sum[fa[u][0]][i]+qpow(depth[u]-1,i);
 
    int sz=G[u].size();
    for (int i=0;i<sz;i++)
    {
        int v=G[u][i];
        if (v!=fa[u][0]) cal(v);
    }
}
 
int lca(int x,int y)
{
    if (depth[x]<depth[y]) swap(x,y);
    for (int i=20;i>=0;i--)
        if (bin[i]<=depth[x] && depth[fa[x][i]]>=depth[y])
            x=fa[x][i];
 
    if (x==y) return x;
    for (int i=20;i>=0;i--)
        if (bin[i]<=depth[x] && fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
 
    return fa[x][0];
}
 
inline LL solve(int x,int y,int k)
{
    LL la=lca(x,y);
    return (sum[x][k]+sum[y][k]-sum[la][k]-sum[fa[la][0]][k])%mod;
}
 
int main()
{
    //freopen("1.txt","r",stdin);
    bin[0]=1;
    for (int i=1;i<=20;i++) bin[i]=bin[i-1]<<1;
    scanf("%d",&n);
    int u,v;
    for (int i=0;i<n-1;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    fa[1][0]=0; depth[1]=1;
    dfs(1);
    cal(1);
 
    scanf("%d",&m);
    int x,y,k;
    for (int i=0;i<m;i++)
    {
        scanf("%d%d%d",&x,&y,&k);
        printf("%lld\n",solve(x,y,k));
    }
    return 0;
}