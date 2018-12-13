// luogu-P2633-树上主席树+树链剖分+树上差分
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
int n,m;
int a[maxn],b[maxn],num;
int son[maxn],sz[maxn],top[maxn],f[maxn],dep[maxn];
int head[maxn],tot;
struct Edge
{
    int v,nx;
}e[maxn<<1];
inline void _init() { tot=num=0;memset(head,-1,sizeof(head)); }
inline void add(int u,int v) {
    e[tot].v=v; e[tot].nx=head[u]; head[u]=tot++;
    e[tot].v=u; e[tot].nx=head[v]; head[v]=tot++;
}

int rt[maxn];
struct PersistableSegmentTree
{
    struct Tree
    {
        int l,r,v;
    }tree[maxn*20];
    int cnt;
    inline void init() { cnt=0; }
    inline void insert(int &o,int pre,int l,int r,int v) {
        o=++cnt; tree[o]=tree[pre]; ++tree[o].v;
        if (l==r) return;
        int mid=(l+r)>>1;
        if (v<=mid) insert(tree[o].l,tree[pre].l,l,mid,v);
        else insert(tree[o].r,tree[pre].r,mid+1,r,v);
    }
    inline int query(int ql,int qr,int _lca,int _lca_f,int l,int r,int k) {
        if (l==r) return l;
        int mid=(l+r)>>1;
        int x=tree[tree[ql].l].v+tree[tree[qr].l].v-tree[tree[_lca].l].v-tree[tree[_lca_f].l].v;
        if (k<=x) return query(tree[ql].l,tree[qr].l,tree[_lca].l,tree[_lca_f].l,l,mid,k);
        else return query(tree[ql].r,tree[qr].r,tree[_lca].r,tree[_lca_f].r,mid+1,r,k-x);
    }
}pst;

void dfs1(int u,int fa) {
    f[u]=fa; dep[u]=dep[fa]+1; sz[u]=1;
    pst.insert(rt[u],rt[fa],1,num,a[u]);
    for (int i=head[u];i!=-1;i=e[i].nx) {
        int v=e[i].v;
        if (v==fa) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        if (!son[u] || sz[son[u]]<sz[v]) son[u]=v;
    }
}

void dfs2(int u,int fa) {
    top[u]=fa;
    if (son[u]) dfs2(son[u],fa);
    for (int i=head[u];i!=-1;i=e[i].nx) {
        int v=e[i].v;
        if (v!=f[u]&&v!=son[u]) dfs2(v,v);
    }
}

int lca(int x,int y) {
    while (top[x]!=top[y]) {
        if (dep[top[x]]>=dep[top[y]]) x=f[top[x]];
        else y=f[top[y]];
    }
    return dep[x]>=dep[y]?y:x;
}

int main() {
    scanf("%d%d",&n,&m);
    _init(); pst.init();
    for (int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
    sort(b+1,b+1+n);
    num=unique(b+1,b+1+n)-b-1;
    for (int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+num,a[i])-b;
    int u,v;
    for (int i=1;i<n;i++) {
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    dfs1(1,0);
    dfs2(1,0);
    int k,ans=0;
    while (m--) {
        scanf("%d%d%d",&u,&v,&k);
        u^=ans;
        int tmp=lca(u,v);
        // printf("%d %d %d %d %d\n", u,v,k,tmp,f[tmp]);
        // printf("%d\n", pst.query(rt[u],rt[v],rt[tmp],rt[f[tmp]],1,num,k));
        ans=b[pst.query(rt[u],rt[v],rt[tmp],rt[f[tmp]],1,num,k)];
        printf("%d\n", ans);
    }
    return 0;
}
