//t1662
#include <cstdio>
#include <iostream>
#include <deque>
#include <cmath>
#include <cstring>

using namespace std;

const int N=10001,inf=2147483647;
typedef pair<int,int> Pii;
deque<Pii> Q;
int n,m,v[N],w[N],p[N],f[N];

void push(int pos,int w)
  {
    while (!Q.empty() && Q.back().second<w) Q.pop_back();
    Q.push_back(Pii(pos,w));
  }
int main()
  {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
      {
        scanf("%d%d%d",&v[i],&w[i],&p[i]);
        if (!p[i]) p[i]=inf;
        p[i]=min(p[i],m/v[i]);
      }
    memset(f,0,sizeof(f));
    for (int i=1;i<=n;++i)
      for (int d=0;d<v[i];++d)
        {
          Q.clear();
          for (int j=0;j<=(m-d)/v[i];++j)
            {
              push(j,f[j*v[i]+d]-j*w[i]);
              while (Q.front().first<j-p[i]) Q.pop_front();
              f[j*v[i]+d]=Q.front().second+j*w[i];
            }
        }
    printf("%d\n",f[m]);
  }