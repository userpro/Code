#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e5+10;
int n,m,cnt,tot;
int head[maxn],num[maxn];
int seg[maxn],rev[maxn],son[maxn],fa[maxn],top[maxn],dep[maxn],sz[maxn];
struct Edge
{
    int to,next;
}edge[maxn<<1];
struct SegNode
{
    int l,r,lc,rc;
    LL c,lazy;
}tree[maxn<<2];

void _init() {
    memset(head,-1,sizeof(head));
    cnt=tot=0;
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
        if (son[u]==0||sz[v]>sz[son[u]]) son[u]=v;
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

inline void pushup(int k) {
    tree[k].c=tree[k<<1].c+tree[k<<1|1].c;
    if (tree[k<<1].rc==tree[k<<1|1].lc) tree[k].c--;
    tree[k].lc=tree[k<<1].lc; tree[k].rc=tree[k<<1|1].rc;
}

inline void pushdown(int k) {
    if (tree[k].lazy!=-1) {
        tree[k<<1].lazy=tree[k].lazy;
        tree[k<<1].lc=tree[k<<1].rc=tree[k].lazy;
        tree[k<<1].c=1;
        tree[k<<1|1].lazy=tree[k].lazy;
        tree[k<<1|1].lc=tree[k<<1|1].rc=tree[k].lazy;
        tree[k<<1|1].c=1;
    }
    tree[k].lazy=-1;
}

void build(int k,int l,int r) {
    tree[k].l=l; tree[k].r=r;
    tree[k].lazy=-1;
    if (l==r) {
        tree[k].c=1;
        tree[k].lc=tree[k].rc=num[rev[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    pushup(k);
}

void update(int k,int x,int y,int c) {
    int l=tree[k].l,r=tree[k].r;
    if (x>r||y<l) return;
    if (x<=l&&y>=r) {
        tree[k].c=1;
        tree[k].lc=tree[k].rc=c;
        tree[k].lazy=c;
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    update(k<<1,x,y,c);
    update(k<<1|1,x,y,c);
    pushup(k);
}

void modify(int u,int v,int c) {
    while (top[u]!=top[v]) {
        if (dep[top[u]]<dep[top[v]]) swap(u,v);
        update(1,seg[top[u]],seg[u],c);
        u=fa[top[u]];
    }
    if (dep[u]>dep[v]) swap(u,v);
    update(1,seg[u],seg[v],c);
}

LL query(int k,int x,int y) {
    int l=tree[k].l,r=tree[k].r;
    if (x>r||y<l) return 0;
    if (x<=l&&y>=r) return tree[k].c;
    pushdown(k);
    int mid=(l+r)>>1;
    LL res=0;
    res+=query(k<<1,x,y);
    res+=query(k<<1|1,x,y);
    if (mid>=x&&mid<y&&tree[k<<1].rc==tree[k<<1|1].lc) res--;
    return res;
}

SegNode& queryColor(int k,int x) {
    int l=tree[k].l,r=tree[k].r;
    if (l==r&&l==x) return tree[k];
    pushdown(k);
    int mid=(l+r)>>1;
    if (mid>=x) return queryColor(k<<1,x);
    else return queryColor(k<<1|1,x);
}

LL ask(int u,int v) {
    LL res=0;
    while (top[u]!=top[v]) {
        if (dep[top[u]]<dep[top[v]]) swap(u,v);
        res+=query(1,seg[top[u]],seg[u]);
        if (queryColor(1,seg[fa[top[u]]]).rc == queryColor(1,seg[top[u]]).lc) res--;
        u=fa[top[u]];
    }
    if (dep[u]>dep[v]) swap(u,v);
    res+=query(1,seg[u],seg[v]);
    return res;
}

int main() {
    _init();
    scanf("%d%d",&n,&m);
    int u,v;
    for (int i=1;i<=n;i++) scanf("%d",&num[i]);
    for (int i=1;i<n;i++) {
        scanf("%d%d",&u,&v);
        add(u,v); add(v,u);
    }
    dfs1(1,1);
    dfs2(1,1);
    build(1,1,tot);
    char op[10];
    int c;
    for (int i=1;i<=m;i++) {
        scanf("%s%d%d",op,&u,&v);
        if (op[0]=='Q') printf("%lld\n", ask(u,v));
        else if (op[0]=='C') {
            scanf("%d",&c);
            modify(u,v,c);
        }
    }
    return 0;
}


