#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define P 3000000021
#define MOD 1000000007

LL pow(LL a,LL n){
    LL ans=1;
    while (n)
    {
        if (n&1) ans=ans*a%MOD;
        a=a*a%MOD;
        n>>=1;
    }
    return ans%MOD;
}

int main(){
    int T;
    LL n,m;
    scanf("%d",&T);
    while (T--)
    {
        scanf("%lld%lld",&n,&m);
        LL ans = pow(2,n);
        ans = (ans - 1) % P;
        ans = pow(ans,m-1);
        if (n&1) ans = ans * 2 + 1;
        else ans = ans * 2;
        ans /= 3;
        printf("%lld\n", ans%MOD);
    }
    return 0;
}