// luogu P3567(POI2014)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=5e5+10;
int n,m;
int a[maxn],b[maxn],rt[maxn*20];
struct PersistableSegmentTree
{
    struct Tree {
        int l,r,val;
    }tree[maxn*20];
    int cnt;
    inline void init() { cnt=0; }
    // 单点修改
    inline void insert(int &o,int pre,int l,int r,int pos) {
        o=++cnt; tree[o]=tree[pre]; ++tree[o].val;
        if (l==r) return;
        int mid=(l+r)>>1;
        if (pos<=mid) return insert(tree[o].l,tree[pre].l,l,mid,pos);
        else return insert(tree[o].r,tree[pre].r,mid+1,r,pos);
    }
    inline int query(int o,int pre,int l,int r,int pos) {
        if (l==r) return l;
        int mid=(l+r)>>1,v=tree[tree[pre].l].val-tree[tree[o].l].val; // v为左边的sum
        if (pos<v) return query(tree[o].l,tree[pre].l,l,mid,pos);
        if (tree[pre].val-tree[o].val-v>pos) return query(tree[o].r,tree[pre].r,mid+1,r,pos); // 根的sum减去左边的sum 剩下右边的sum
        return 0;
    }
}pst;

int main() {
    pst.init();
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
    // 离散化
    sort(b+1,b+1+n);
    int cnt=unique(b+1,b+1+n)-b-1;
    for (int i=1;i<=n;i++) pst.insert(rt[i],rt[i-1],1,cnt,lower_bound(b+1,b+1+cnt,a[i])-b);
    
    int l,r;
    for (int i=1;i<=m;i++) {
        scanf("%d%d",&l,&r);
        printf("%d\n", b[pst.query(rt[l-1],rt[r],1,cnt,(r-l+1)>>1)]);
    }
    return 0;
}