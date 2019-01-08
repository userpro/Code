// codeforces816D-杨辉三角组合数逆元
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;
const int maxn=2e5+10;
const int mod=1e9+7;
int n;
LL inv[maxn],fac[maxn],a[maxn],b[maxn];
LL qpow(LL a,LL b) {
    LL r=1;
    while (b) {
        if (b&1) r=r*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return r%mod;
}
inline LL C(LL n,LL m) {
    if (m==0 || n==m) return 1;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init() {
    fac[0]=1;
    for (int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod;
    inv[maxn-1]=qpow(fac[maxn-1],mod-2);
    for (LL i=maxn-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int main() {
    init();
    while (~scanf("%d",&n)) {
        for (int i=1;i<=n;i++) scanf("%I64d",&a[i]);
        if (n==1) {
            printf("%I64d\n", a[1]);
            continue;
        }
        if (n==2) {
            printf("%I64d\n", (a[1]+a[2])%mod);
            continue;
        }
        if (n%2!=0) {
            for (int i=2;i<=n;i++) b[i-1]=(a[i-1]+(i%2?-1:1)*a[i])%mod;
            n--;
        } else {
            for (int i=1;i<=n;i++) b[i]=a[i];
        }
        int op=(n%4==0?-1:1);
        LL ans=0;
        for (int i=1;i<=n;i+=2) {
            LL tmp=C(n/2-1,i/2);
            ans=(ans+tmp*(b[i]+op*b[i+1])%mod)%mod;
        }
        printf("%I64d\n", (ans%mod+mod)%mod);
    }
    return 0;
}