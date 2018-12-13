// luogu P3402
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,m;

int f[maxn*30],dep[maxn*30],rt[maxn];
struct PersistableUnionSet
{
    struct Tree {
        int l,r;
    }tree[maxn*30];
    int cnt;
    inline void init() { cnt=0; }
    inline void build(int &o,int l,int r) {
        o=++cnt;
        if (l==r) {
            f[o]=l; return;
        }
        int mid=(l+r)>>1;
        build(tree[o].l,l,mid); build(tree[o].r,mid+1,r);
    }
    inline void merge(int &o,int pre,int l,int r,int pos,int fa) {
        o=++cnt; tree[o]=tree[pre];
        if (l==r) {
            f[o]=fa;
            dep[o]=dep[pre];
            return;
        }
        int mid=(l+r)>>1;
        if (pos<=mid) return merge(tree[o].l,tree[pre].l,l,mid,pos,fa);
        else return merge(tree[o].r,tree[pre].r,mid+1,r,pos,fa);
    }
    inline void update(int o,int l,int r,int pos) {
        if (l==r) {
            dep[o]++; return;
        }
        int mid=(l+r)>>1;
        if (pos<=mid) return update(tree[o].l,l,mid,pos);
        else return update(tree[o].r,mid+1,r,pos);
    }
    inline int query(int o,int l,int r,int pos) {
        if (l==r) return o;
        int mid=(l+r)>>1;
        if (pos<=mid) return query(tree[o].l,l,mid,pos);
        else return query(tree[o].r,mid+1,r,pos);
    }
    inline int findd(int o,int pos) {
        int tmp=query(o,1,n,pos);
        if (f[tmp]==pos) return tmp;
        return findd(o,f[tmp]);
    }
}psu;

int main() {
    int opt,a,b;
    while (~scanf("%d%d",&n,&m)) {
        memset(dep,0,sizeof(dep));
        rt[0]=0;
        psu.init(); psu.build(rt[0],1,n);

        for (int i=1;i<=m;i++) {
            scanf("%d",&opt);
            if (opt==1) {
                rt[i]=rt[i-1];
                scanf("%d%d",&a,&b);
                int pa=psu.findd(rt[i],a),pb=psu.findd(rt[i],b);
                if (f[pa]!=f[pb]) {
                    if (dep[pa]>dep[pb]) swap(pa,pb);
                    psu.merge(rt[i],rt[i-1],1,n,f[pa],f[pb]);
                    if (dep[pa]==dep[pb]) psu.update(rt[i],1,n,f[pb]);
                }
            } else if (opt==2) {
                scanf("%d",&a);
                rt[i]=rt[a];
            } else if (opt==3) {
                scanf("%d%d",&a,&b);
                rt[i]=rt[i-1];
                int pa=psu.findd(rt[i],a),pb=psu.findd(rt[i],b);
                if (f[pa]==f[pb]) puts("1");
                else puts("0");
            }
        }
    }
    return 0;
}
