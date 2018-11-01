// bzoj2038 小Z的袜子 莫队算法 对查询分块
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn=5e4+10;
int n,m;
int pos[maxn],L[maxn],R[maxn];
LL a[maxn],s[maxn];
struct Node
{
    LL a,b,l,r,id;
}q[maxn];
LL ans;

LL pw(LL x) { return x*x; }
LL gcd(LL a,LL b) { return b==0?a:gcd(b,a%b); }
inline bool cmp1(const Node&n1,const Node&n2) { return pos[n1.l]==pos[n2.l]?n1.r<n2.r:n1.l<n2.l; }
inline bool cmp2(const Node&n1,const Node&n2) { return n1.id<n2.id; }

inline void update(int k,int add) {
    ans-=pw(s[a[k]]);
    s[a[k]]+=add;
    ans+=pw(s[a[k]]);
}

void solve() {
    for (int i=1,l=1,r=0;i<=m;i++) {
        for (;l<q[i].l;l++) update(l,-1);
        for (;l>q[i].l;l--) update(l-1,1);
        for (;r<q[i].r;r++) update(r+1,1);
        for (;r>q[i].r;r--) update(r,-1);
        if (q[i].l==q[i].r) {
            q[i].a=0; q[i].b=1;
            continue;
        }
        q[i].a=ans-(q[i].r-q[i].l+1);
        q[i].b=(q[i].r-q[i].l+1)*(q[i].r-q[i].l);
        LL k=gcd(q[i].a,q[i].b);
        q[i].a/=k; q[i].b/=k;
    }
}

int main() {
    ans=0;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for (int i=1;i<=m;i++) {
        scanf("%lld%lld",&q[i].l,&q[i].r);
        q[i].a=q[i].b=0;
        q[i].id=i;
    }
    int t=(int)sqrt(n);
    for (int i=1;i<=t;i++) {
        L[i]=(i-1)*t+1;
        R[i]=i*t;
    }
    if (R[t]<n) ++t,L[t]=R[t-1]+1,R[t]=n;
    for (int i=1;i<=t;i++) for (int j=L[i];j<=R[i];j++) pos[j]=i;
    sort(q+1,q+1+m,cmp1);
    solve();
    sort(q+1,q+1+m,cmp2);
    for (int i=1;i<=m;i++) printf("%lld/%lld\n", q[i].a,q[i].b);
    return 0;
}
