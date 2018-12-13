// codeforce 853C 矩形主席树

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=2e5+10;
int n,q;
int rt[maxn];
struct PersistableSegTree
{
    struct Tree {
        int l,r,v;
    }tree[maxn*20];
    int cnt;
    inline void init() { cnt=0; }
    inline void update(int &o,int pre,int l,int r,int v) {
        o=++cnt; tree[o]=tree[pre]; ++tree[o].v;
        if (l==r&&l==v) return;
        int mid=(l+r)>>1;
        if (v<=mid) update(tree[o].l,tree[pre].l,l,mid,v);
        else update(tree[o].r,tree[pre].r,mid+1,r,v);
    }
    inline int query(int o,int pre,int l,int r,int x,int y) {
        if (x<=l&&y>=r) return tree[o].v-tree[pre].v;
        int mid=(l+r)>>1;
        int res=0;
        if (mid>=x) res+=query(tree[o].l,tree[pre].l,l,mid,x,y);
        if (mid<y) res+=query(tree[o].r,tree[pre].r,mid+1,r,x,y);
        return res; 
    }
}pst;
int main() {
    while (~scanf("%d%d",&n,&q)) {
        pst.init();
        memset(rt,0,sizeof(rt));
        int tmp;
        for (int i=1;i<=n;i++) {
            scanf("%d",&tmp);
            pst.update(rt[i],rt[i-1],1,n,tmp);
        }
        int l,d,r,u;
        while (q--) {
            scanf("%d%d%d%d",&l,&d,&r,&u);
            LL sum1=0,sum2=0,sum3=0,sum4=0,sum5=0,sum6=0,sum7=0,sum8=0,sum9=0;
            if (d-1>=1) {
                sum1=pst.query(rt[l-1],rt[0],1,n,1,d-1);
                sum2=pst.query(rt[r],rt[l-1],1,n,1,d-1);
                sum3=pst.query(rt[n],rt[r],1,n,1,d-1);
            }
            sum4=pst.query(rt[l-1],rt[0],1,n,d,u);
            sum5=pst.query(rt[r],rt[l-1],1,n,d,u);
            sum6=pst.query(rt[n],rt[r],1,n,d,u);
            sum7=pst.query(rt[l-1],rt[0],1,n,u+1,n);
            sum8=pst.query(rt[r],rt[l-1],1,n,u+1,n);
            sum9=pst.query(rt[n],rt[r],1,n,u+1,n);
            // printf("sum: %lld %lld %lld %lld %lld %lld %lld %lld %lld\n", sum1,sum2,sum3,sum4,sum5,sum6,sum7,sum8,sum9);

            LL ans=sum1*(sum5+sum6+sum8+sum9);
            ans+=sum2*(sum4+sum5+sum6+sum7+sum8+sum9);
            ans+=sum3*(sum4+sum5+sum7+sum8);
            ans+=sum4*(sum2+sum3+sum5+sum6+sum8+sum9);
            ans+=sum5*(n-1);
            ans+=sum6*(sum1+sum2+sum4+sum5+sum7+sum8);
            ans+=sum7*(sum2+sum3+sum5+sum6);
            ans+=sum8*(sum1+sum2+sum3+sum4+sum5+sum6);
            ans+=sum9*(sum1+sum2+sum4+sum5);
            printf("%I64d\n", ans/2);
        }
    }
    return 0;
}
