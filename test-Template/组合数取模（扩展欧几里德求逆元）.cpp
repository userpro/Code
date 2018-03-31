#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int P=1000000007;
int n,m;
long long a=1,b=1,x=0,y=0;

inline void read(int &x) 
  {
    char ch; int s=1;x=0;
    while (ch=getchar(),(ch<'0' || ch>'9') && (ch!='-'));
    if (ch=='-') s=-1; else x =ch-'0';
    while (ch=getchar(),ch>='0' && ch<='9') x*=10,x+=ch-'0';
    x*=s;
  }
long long gcd(long long a,long long b)
  {
    if (b==0) 
      {
        x=1;y=0;return a;
      }
    long long ans=gcd(b,a%b);
    long long o=x;
    x=y;y=o-(a/b)*y;
    return ans;
  }
int main()
  {
    read(n);read(m);
    for (int i=1;i<=m;++i) b=(b*i)%P;
    for (int i=n;i>n-m;--i) a=(a*i)%P;
    gcd(b,P);
    x=(x%P+P)%P;
    printf("%I64d\n",(a*x)%P);
  }