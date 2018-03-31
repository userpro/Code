#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=11;
int a[N],b[N],g,n;
long long ans=0,M=1,x,y;

int gcd(long long a,long long b)
  {
    if (b==0)
      {
        x=1;y=0;
        return a;
      }
    int g=gcd(b,a%b);
    int o=x;x=y;y=o-a/b*y;
    return g;
  }
int main()
  {
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%d%d",&a[i],&b[i]),M*=a[i];
    for (int i=1;i<=n;++i)
      {
        g=gcd(M/a[i],a[i]);
        ans=(ans+M/a[i]*x*b[i]/g)%M;
        while (ans<0) ans+=M;
      }
    printf("%I64d\n",ans);
  }