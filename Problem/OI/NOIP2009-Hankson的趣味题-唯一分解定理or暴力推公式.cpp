// NOIP2009-Hankson的趣味题-唯一分解定理or暴力推公式
/* 397ms */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
int n,cnt,ans;
int p[50010];
bool vis[50010];
int a0,a1,b0,b1;
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void _init() {
    memset(vis,1,sizeof(vis));
    vis[0]=vis[1]=0;
    for (int i=2;i<=50000;i++) {
        if (i>50000/i || !vis[i]) continue;
        for (int j=i+i;j<=50000;j+=i) vis[j]=0;
    }
    cnt=0;
    for (int i=2;i<=50000;i++) if (vis[i]) p[++cnt]=i;
}
inline void solve(int x) {
    int c0=0,c1=0,c2=0,c3=0;
    while (a0%x==0) c0++,a0/=x;
    while (a1%x==0) c1++,a1/=x;
    while (b0%x==0) c2++,b0/=x;
    while (b1%x==0) c3++,b1/=x;
    if (c0==c1 && c2==c3) {
        if (c1<=c3) ans*=(c3-c1+1);
        else ans=0;
    } else if (c0!=c1 && c2!=c3 && c1!=c3) ans=0;
}
int main() {
    _init();
    n=read();
    while (n--) {
        a0=read(), a1=read(), b0=read(), b1=read();
        ans=1;
        for (int i=1;i<=cnt;i++) solve(p[i]);
        if (b1>1) solve(b1);
        printf("%d\n", ans);
    }
    return 0;
}

/* 1407ms */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
int n;
LL a0,a1,b0,b1,a2,b2;
inline LL gcd(LL a,LL b) { return b==0?a:gcd(b,a%b); }
inline bool check(LL x) { return x%a1==0 && b1%x==0 && gcd(x/a1,a2)==1 && gcd(b2,b1/x)==1; }
int main() {
    scanf("%d",&n);
    while (n--) {
        scanf("%lld%lld%lld%lld",&a0,&a1,&b0,&b1);
        a2=a0/a1; b2=b1/b0;
        int ans=0;
        for (LL i=1;i*i<=b1;i++) {
            if (b1%i==0) {
                ans+=check(i);
                if (i*i!=b1) ans+=check(b1/i);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}