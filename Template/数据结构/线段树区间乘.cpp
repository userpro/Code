// bzoj1798 本题要求对p取模 记得开 long long!!!
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e5+10;
int n,m,p;
int a[maxn];
struct Node
{
    int l,r,sum,add,mul;
}val[maxn<<2];

inline void pushup(LL k) {
    val[k].sum=(val[k<<1].sum+val[k<<1|1].sum)%p;
}

inline void add_node(LL k,LL num) {
    val[k].add=(val[k].add+num)%p;
    val[k].sum=(val[k].sum+(val[k].r-val[k].l+1)*num%p)%p;
}

inline void mul_node(LL k,LL num) {
    val[k].mul=(val[k].mul*num)%p;
    val[k].add=(val[k].add*num)%p;
    val[k].sum=(val[k].sum*num)%p;
}

inline void pushdown(LL k) {
    if (val[k].mul!=1) {
        mul_node(k<<1,val[k].mul);
        mul_node(k<<1|1,val[k].mul);
        val[k].mul=1;
    }
    if (val[k].add!=0) {
        add_node(k<<1,val[k].add);
        add_node(k<<1|1,val[k].add);
        val[k].add=0;
    }
}

void build(LL k,LL x,LL y) {
    val[k].l=x; val[k].r=y;
    val[k].add=0; val[k].sum=0;
    val[k].mul=1;
    if (x==y) {
        val[k].sum=a[x];
        return;
    }
    LL mid=(x+y)>>1;
    build(k<<1,x,mid);
    build(k<<1|1,mid+1,y);
    pushup(k);
}

void updateAdd(LL k,LL x,LL y,LL v) {
    if (x>val[k].r||y<val[k].l) return;
    if (val[k].l>=x&&val[k].r<=y) {
        val[k].add=(val[k].add+v)%p;
        val[k].sum=(val[k].sum+(val[k].r-val[k].l+1)*v%p)%p;
        return;
    }
    pushdown(k);
    LL mid=(val[k].l+val[k].r)>>1;
    if (mid>=x) updateAdd(k<<1,x,y,v);
    if (mid<y)  updateAdd(k<<1|1,x,y,v);
    pushup(k);
}

void updateMul(LL k,LL x,LL y,LL v) {
    if (x>val[k].r||y<val[k].l) return;
    if (val[k].l>=x&&val[k].r<=y) {
        val[k].mul=(val[k].mul*v)%p;
        val[k].add=(val[k].add*v)%p;
        val[k].sum=(val[k].sum*v)%p;
        return;
    }
    pushdown(k);
    LL mid=(val[k].l+val[k].r)>>1;
    if (mid>=x) updateMul(k<<1,x,y,v);
    if (mid<y)  updateMul(k<<1|1,x,y,v);
    pushup(k);
}

LL query(LL k,LL x,LL y) {
    if (x>val[k].r||y<val[k].l) return 0;
    if (val[k].l>=x&&val[k].r<=y) return val[k].sum%p;
    pushdown(k);
    LL mid=(val[k].l+val[k].r)>>1;
    LL res=0;
    if (mid>=x) res=(res+query(k<<1,x,y))%p;
    if (mid<y)  res=(res+query(k<<1|1,x,y))%p;
    return res;
}

int main() {
    scanf("%d%d",&n,&p);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    scanf("%d",&m);
    int t1,t2,t3,t4;
    for (int i=1;i<=m;i++) {
        scanf("%d",&t1);
        if (t1==1) {
            scanf("%d%d%d",&t2,&t3,&t4);
            updateMul(1,t2,t3,t4);
        } else if (t1==2) {
            scanf("%d%d%d",&t2,&t3,&t4);
            updateAdd(1,t2,t3,t4);
        } else if (t1==3) {
            scanf("%d%d",&t2,&t3);
            printf("%lld\n", query(1,t2,t3));
        }
    }
    return 0;
}
