#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int n;

int pow(int n,int k)
  {
    int ans=1;
    for (int i=1;i<=k;++i) ans*=n;
    return ans;
  }
int Euler(int n)
  {
    int ans=1;
    for (int i=2;i<=int(sqrt(n));++i)
      if (n%i==0)
        {
          int num=0;
          while (n%i==0) n/=i,++num;
          ans=ans*(i-1)*pow(i,num-1);
        }
    if (n!=1) ans*=(n-1);
    return ans;
  }
int main()
  {
    while (scanf("%d",&n),n) printf("%d\n",Euler(n));
  }