// bzoj3531
// 对于需要n棵线段树维护的情况 可以通过动态线段树(即节点动态生成)
// 来节约内存 以免MLE
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> P;
const int maxn=1e5+10;
int n,m,cnt,tot,idx;
int root[maxn],w[maxn],s[maxn];
int head[maxn],seg[maxn],rev[maxn],dep[maxn],top[maxn],sz[maxn],fa[maxn],son[maxn];
struct Edge
{
    int to,next;
}edge[maxn<<1];
struct SegNode
{
    int l,r;
    LL sum,mx;
}tree[maxn*50];

void _init() {
    memset(head,-1,sizeof(head));
    cnt=tot=idx=0;
}

void add(int u,int v) {
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void dfs1(int u,int f) {
    fa[u]=f;
    dep[u]=dep[f]+1;
    sz[u]=1;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (v==f) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        if (!son[u] || sz[v]>sz[son[u]]) son[u]=v;
    }
}

void dfs2(int u,int f) {
    seg[u]=++tot;
    rev[tot]=u;
    top[u]=f;
    if (son[u]) dfs2(son[u],f);
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}

void update(int &k,int l,int r,int x,int val) {
    if (!k) k=++idx;
    if (l==r&&l==x) {
        tree[k].sum=tree[k].mx=val;
        return;
    }
    int mid=(l+r)>>1;
    if (mid>=x) update(tree[k].l,l,mid,x,val);
    if (mid<x) update(tree[k].r,mid+1,r,x,val);
    tree[k].sum=tree[tree[k].l].sum+tree[tree[k].r].sum;
    tree[k].mx=max(tree[tree[k].l].mx,tree[tree[k].r].mx);
}

// 1->sum  0->max
LL query(int k,int l,int r,int x,int y,int op) {
    if (x>r||y<l) return 0;
    if (x<=l&&y>=r) {
        if (op) return tree[k].sum;
        else return tree[k].mx;
    }
    int mid=(l+r)>>1;
    LL res=0;
    if (mid>=x) {
        if (op) res+=query(tree[k].l,l,mid,x,y,op);
        else res=max(res,query(tree[k].l,l,mid,x,y,op));
    }
    if (mid<y) {
        if (op) res+=query(tree[k].r,mid+1,r,x,y,op);
        else res=max(res,query(tree[k].r,mid+1,r,x,y,op));
    }
    return res;
}

LL ask(int u,int v,int op) {
    int k=root[s[u]];
    LL res=0;
    while (top[u]!=top[v]) {
        if (dep[top[u]]<dep[top[v]]) swap(u,v);
        if (op) res+=query(k,1,n,seg[top[u]],seg[u],op);
        else res=max(res,query(k,1,n,seg[top[u]],seg[u],op));
        u=fa[top[u]];
    }
    if (dep[u]>dep[v]) swap(u,v);
    if (op) res+=query(k,1,n,seg[u],seg[v],op);
    else res=max(res,query(k,1,n,seg[u],seg[v],op));
    return res;
}

int main() {
    _init();
    scanf("%d%d",&n,&m);
    int u,v;
    for (int i=1;i<=n;i++) scanf("%d%d",&w[i],&s[i]);
    for (int i=1;i<n;i++) {
        scanf("%d%d",&u,&v);
        add(u,v); add(v,u);
    }
    dfs1(1,1);
    dfs2(1,1);
    for (int i=1;i<=n;i++) update(root[s[i]],1,n,seg[i],w[i]);
    char op[5];
    for (int i=1;i<=m;i++) {
        scanf("%s%d%d",op,&u,&v);
        if (op[1]=='C') {
            update(root[v],1,n,seg[u],w[u]);
            update(root[s[u]],1,n,seg[u],0);
            s[u]=v;
        }
        if (op[1]=='W') {
            update(root[s[u]],1,n,seg[u],v);
            w[u]=v;
        }
        if (op[1]=='S') {
            printf("%lld\n", ask(u,v,1));
        }
        if (op[1]=='M') {
            printf("%lld\n", ask(u,v,0));
        }
    }
    return 0;
}

