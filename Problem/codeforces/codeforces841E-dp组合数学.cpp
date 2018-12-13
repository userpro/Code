// codeforces 841E dp 组合数学
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL mod=1e9+7;
const int maxn=310;
int n;
LL inv[maxn],fac[maxn],C[maxn][maxn];
LL dp[maxn][maxn];
map<LL,int> mp;
LL qpow(LL a,LL b) {
    LL r=1;
    while (b) {
        if (b&1) r=r*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return r%mod;
}

void _init() {
    fac[1]=1;
    for (int i=2;i<maxn;i++) fac[i]=fac[i-1]*i%mod;
    inv[maxn-1]=qpow(fac[maxn-1],mod-2);
    for (int i=maxn-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
    C[0][0]=1;
    for (int i=1;i<maxn;i++) {
        C[i][0]=1;
        for (int j=1;j<maxn;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    }
}

int main() {
    _init();
    while (~scanf("%d",&n)) {
        memset(dp,0,sizeof(dp));
        mp.clear();
        LL tmp;
        for (int i=1;i<=n;i++) {
            scanf("%I64d",&tmp);
            for (LL j=2;j*j<=tmp;j++) {
                while (tmp%(j*j)==0) tmp/=(j*j);
            }
            mp[tmp]++;
        }
        int sum=0;
        map<LL,int>::iterator it=mp.begin();
        dp[0][0]=1;
        for (int i=1;it!=mp.end();it++,i++) {
            sum+=it->second;
            for (int k=i;k<=sum;k++) {
                for (int j=1;j<=k && j<=it->second;j++) {
                    dp[i][k]=(dp[i][k]+dp[i-1][k-j]*C[it->second-1][j-1]%mod*fac[it->second]%mod*inv[j]%mod)%mod;
                }
            }
        }

        LL ans=0;
        int cnt=mp.size();
        for (int k=n,flag=1;k>=1;k--,flag=-flag) {
            ans=(ans+mod+flag*dp[cnt][k]*fac[k]%mod)%mod;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}