// luogu P3919
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e6+10;
int n,m;
int a[maxn],rt[maxn*20];
struct PersistableSegmentTree {
    struct Tree {
        int l,r,val;
    }tree[maxn*20];
    int cnt;
    inline void init() { cnt=0; }
    inline void build(int &o,int l,int r) {
        o=++cnt;
        if (l==r) { tree[o].val=a[l]; return; }
        int mid=(l+r)>>1;
        build(tree[o].l,l,mid); build(tree[o].r,mid+1,r);
    }
    // 单点修改
    inline void insert(int &o,int pre,int l,int r,int loc,int val) {
        o=++cnt; tree[o]=tree[pre];
        if (l==r) { tree[o].val=val; return; }
        int mid=(l+r)>>1;
        if (loc<=mid) insert(tree[o].l,tree[pre].l,l,mid,loc,val);
        else insert(tree[o].r,tree[pre].r,mid+1,r,loc,val);
    }
    inline int query(int o,int l,int r,int loc) {
        if (l==r) return tree[o].val;
        int mid=(l+r)>>1;
        if (loc<=mid) return query(tree[o].l,l,mid,loc);
        else return query(tree[o].r,mid+1,r,loc);
    }
}pst;

int main() {
    pst.init();
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    pst.build(rt[0],1,n);
    int pre,typ,loc,val;
    for (int i=1;i<=m;i++) {
        scanf("%d%d%d",&pre,&typ,&loc);
        if (typ==1) {
            scanf("%d",&val);
            pst.insert(rt[i],rt[pre],1,n,loc,val);
        } else {
            printf("%d\n", pst.query(rt[pre],1,n,loc));
            rt[i]=rt[pre];
        }
    }
    return 0;
}
