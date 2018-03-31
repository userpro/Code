//h2274
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <set>
#include <map>

using namespace std;

const int N=100012,P=1000000009;
int n,m,a,tot=0,f[N];
set<long long> S;
set<long long>::iterator p;
map<long long,int> Map;
long long sum[N];

struct BIT
  {
    int c[N];
    inline int lowbit(int k) {return k&(-k);}
    inline void insert(int k,int t)
      {
        while (k<=tot) c[k]=(c[k]+t)%P,k+=lowbit(k);
      }
    inline int sum(int k)
      {
        int ans=0;while (k) ans=(ans+c[k])%P,k-=lowbit(k);
        return ans;
      }
  } B;
int main()
  {
    scanf("%d",&n);
    sum[0]=0;S.insert(sum[0]);
    for (int i=1;i<=n;++i) 
      scanf("%d",&a),sum[i]=sum[i-1]+a,S.insert(sum[i]);
    for (p=S.begin();p!=S.end();++p) Map[*p]=++tot;
    f[0]=1;
    B.insert(Map[sum[0]],f[0]);
    for (int i=1;i<=n;++i)
      {
        f[i]=B.sum(Map[sum[i]]);
        B.insert(Map[sum[i]],f[i]);
      }
    printf("%d\n",f[n]);
  }
    