// poj1061-解不定方程 ax + by = c
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
LL M,N,L;
LL a,b,X,Y;
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
    LL t;
    if (b==0) { d=a, x=1, y=0; }
    else {
        exgcd(b,a%b,d,x,y);
        t=x, x=y, y=t-(a/b)*y;
    }
}
int main() {
    while (~scanf("%lld%lld%lld%lld%lld",&X,&Y,&M,&N,&L)) {
        LL x0,y0,d;
        if (N<M) { swap(N,M); swap(X,Y); }
        exgcd(N-M,L,d,x0,y0);
        if ((X-Y)%d!=0 || N==M) puts("Impossible");
        else {
            LL ans=x0*(X-Y)/d; // 特解
            printf("%lld\n", (ans%(L/d)+L/d)%(L/d)); // 最小整数解
        }
    }
    return 0;
}

// 解模线性方程 ax ≡ c (mod b)
LL a,b;
inline void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
    LL t;
    if (b==0) { d=a ,x=1, y=0; }
    else {
        exgcd(b,a%b,d,x,y);
        t=x, x=y, y=t-a/b*y;
    }
}
int main() {
    while (~scanf("%lld%lld",&a,&b)) {
        LL d,x,y;
        exgcd(a,b,d,x,y);
        printf("%lld\n", ((x/d)%(b/d)+b/d)%(b/d));
    }
    return 0;
}