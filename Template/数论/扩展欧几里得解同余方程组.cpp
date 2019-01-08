// poj2891-扩展欧几里得解同余方程组
// x ≡ ai (mod mi)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
int n;
LL a,b;
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
    LL t;
    if (b==0) { d=a,x=1,y=0; }
    else {
        exgcd(b,a%b,d,x,y);
        t=x, x=y, y=t-(a/b)*y;
    }
}

int main() {
    LL x0,y0,d,k;
    while (~scanf("%d",&n)) {
        scanf("%lld%lld",&a,&b);
        LL lcm=a,now=b,fail=0;
        for (int i=1;i<n;i++) {
            scanf("%lld%lld",&a,&b);
            b=(b-now%a+a)%a;
            exgcd(lcm,a,d,x0,y0);
            if (b%d==0) k=x0*(b/d)%a;
            else fail=1;
            now+=k*lcm;
            lcm=lcm/d*a;
            now=(now%lcm+lcm)%lcm;
        }
        if (fail) puts("-1");
        else printf("%lld\n", now);
    }
    return 0;
}
