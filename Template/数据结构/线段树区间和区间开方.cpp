// pushup：
// (1)build的结尾，当叶子节点分别有对应的值后，它的父亲们就等于它们求和。
// (2)update的结尾，因为此时当前根的左右孩子已经更新了，故它也需要更新。

// pushdown(延迟标记):
// *pushdown会出现在一切要从当前结点往下的位置
// query和update中，要先把add的值传给两个儿子。

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e5+10;
int n,m;
int a[maxn];
LL sum[maxn<<2];
bool flag[maxn<<2];

void pushup(int k) {
    sum[k]=sum[k<<1]+sum[k<<1|1];
    flag[k]=flag[k<<1]&flag[k<<1|1];
}

void build(int k,int l,int r) {
    if (l==r) {
        sum[k]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    pushup(k);
}

void update(int k,int l,int r,int x,int y) {
    if (flag[k]) return;
    if (x>r||y<l) return;
    if (l==r) {
        sum[k]=(LL)sqrt(sum[k]);
        if (sum[k]==1||sum[k]==0) flag[k]=1;
        return;
    }
    int mid=(l+r)>>1;
    // -> pushdown
    update(k<<1,l,mid,x,y);
    update(k<<1|1,mid+1,r,x,y);
    pushup(k);
}

LL query(int k,int l,int r,int x,int y) {
    if (x>r||y<l) return 0;
    if (x<=l && y>=r) return sum[k];
    int mid=(l+r)>>1;
    // -> pushdown
    LL res=0;
    if (mid>=x) res+=query(k<<1,l,mid,x,y);
    if (mid<y)  res+=query(k<<1|1,mid+1,r,x,y);
    return res;
}

int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    scanf("%d",&m);
    int t1,t2,t3;
    for (int i=1;i<=m;i++) {
        scanf("%d%d%d",&t1,&t2,&t3);
        if (t1==1) printf("%lld\n", query(1,1,n,t2,t3));
        else update(1,1,n,t2,t3);
    }
    return 0;
}
