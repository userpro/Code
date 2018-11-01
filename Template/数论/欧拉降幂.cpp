// cf906D Power Tower 欧拉降幂应用
// n^x mod m=n^(φ(m)+x%φ(m)) mod m 式子当且仅当x>φ(m)时满足
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;
#define MOD(a,b) (a<b?a:a%b+b) // 保证取模方式一致 不然结果会出错
const int maxn=1e5+10;
LL n,m,mod;
LL a[maxn];
map<LL,LL> mp;

LL qpow(LL a,LL b,LL mod) {
    LL res=1;
    while (b) {
        if (b&1) res=MOD(res*a,mod);
        a=MOD(a*a,mod);
        b>>=1;
    }
    return res;
} 

LL phi(LL n) {
    LL res=n;
    if (mp.find(n)!=mp.end()) return mp[n];
    for (LL i=2;i*i<=n;i++) {
        if (n%i==0) {
            res=res/i*(i-1);
            while (n%i==0) n/=i;
        }
    }
    if (n>1) res=res/n*(n-1);
    return mp[n]=res;
}

LL solve(LL l,LL r,LL mod) {
    if (l==r||mod==1) return MOD(a[l],mod);
    return qpow(a[l],solve(l+1,r,phi(mod)),mod);
}

int main() {
    scanf("%lld%lld",&n,&mod);
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
    scanf("%lld",&m);
    LL l,r;
    while (m--) {
        scanf("%lld%lld",&l,&r);
        printf("%lld\n", solve(l,r,mod)%mod);
    }
    return 0;
}

