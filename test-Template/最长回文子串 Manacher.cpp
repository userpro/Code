//h2565
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstring>
#include <cmath>

using namespace std;

const int N=200012,inf=99999999;
int n=0,l,r[N],mr,mid,ans=0;
char s[N],st[N];
struct BIT
  {
    int c[N];
    inline void clean() {memset(c,127,sizeof(c));}
    inline void insert(int k,int t)
      {
        while (k<=n) c[k]=min(c[k],t),k+=k&(-k);
      }
    inline int find(int k)
      {
        int ans=inf;
        while (k) ans=min(ans,c[k]),k-=k&(-k);
        return ans;
      }
  } B;
inline int c(int k) {return n-k+1;}
int main()
  {
    B.clean();
    scanf("%s",st);
    l=strlen(st);
    s[++n]='&';s[++n]='#';
    for (int i=0;i<l;++i) s[++n]=st[i],s[++n]='#';
    s[++n]='$';
    r[mid=1]=1;mr=2;
    for (int i=2;i<n;++i)
      {
        r[i]=min(r[mid*2-i],mr-i);
        while (s[i+r[i]]==s[i-r[i]]) ++r[i];
        if (i+r[i]>mr) mr=i+r[i],mid=i;
        ans=max(ans,i-B.find(c(i-r[i])-1));
        B.insert(c(i+r[i]),i);
      }
    printf("%d\n",ans);
  }