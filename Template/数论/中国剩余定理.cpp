// loj10212曹冲养猪-中国剩余定理
/*
求解同余线性方程组
x≡ai(mod mi) mi(1<=i<=n)互质
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1010;
LL a[maxn],m[maxn];
int n;
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
    LL t;
    if (b==0) { d=a,x=1,y=0; }
    else {
        exgcd(b,a%b,d,x,y);
        t=x,x=y,y=t-(a/b)*y;
    }
}
LL intChina(int r) {
    LL d,x0,y0,ans=0;
    LL M=1;
    for (int i=1;i<=r;i++) M*=m[i];
    for (int i=1;i<=r;i++) {
        LL Mi=M/m[i];
        exgcd(Mi,m[i],d,x0,y0);
        ans=(ans+Mi*x0*a[i])%M;
    }
    return (ans+M)%M;
}
int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%lld%lld",&m[i],&a[i]);
    printf("%lld\n", intChina(n));
}
