//h1923
#include <cstdio>
#include <iostream>
#include <bitset>

using namespace std;

const int N=1001,M=2001;
bitset<N> bit[M];
int n,m,ans[N],pos[M];
char ch;

int main()
  {
    scanf("%d%d\n",&n,&m);
    for (int i=1;i<=m;++i)
      {
        for (int j=1;j<=n;++j)
          ch=getchar(),bit[i][j]=ch=='1';
        ch=getchar();ch=getchar();
        bit[i][0]=ch=='1';
        ch=getchar();
      }
    int tot=n,num=-1;
    for (int i=1;i<=m;++i)
      {
        int t=-1;
        for (int j=1;j<=n;++j)
          if (bit[i][j]) 
            {
              t=j;break;
            }
        if (t==-1) continue;
        pos[i]=t;
        for (int j=1;j<=m;++j)
          if (i!=j && bit[j][t]) bit[j]^=bit[i];
        if (!--tot) {num=i;break;}
      }
    if (num==-1) 
      {
        puts("Cannot Determine");
        return 0;
      }
    printf("%d\n",num);
    for (int i=1;i<=num;++i)
      if (pos[i]!=-1) ans[pos[i]]=bit[i][0];
    for (int i=1;i<=n;++i)
      if (ans[i]) puts("?y7M#");else puts("Earth");
  }