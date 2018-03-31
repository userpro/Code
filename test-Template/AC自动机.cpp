//hdu2222
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=500001,M=26,L=1000001;
struct Anode
  {
    Anode *ch[M],*fail;
    int num,id;
  } T[N],*nil,*root,*P,*Q[N];
int n,data,ans;
char s[L];

inline void newnode(Anode *&x)
  {
    x=P++;
    x->num=0;x->fail=nil;
    x->id=x-nil;
    for (int i=0;i<M;++i) x->ch[i]=nil;
  }
inline void clear()
  {
    P=T;ans=0;
    newnode(nil);
    newnode(root);
    for (int i=0;i<M;++i) nil->ch[i]=root;
  }
inline void insert(char* s)
  {
    Anode *k=root;int t;
    for (int i=0;s[i];++i)
      {
        t=s[i]-'a';
        if (k->ch[t]==nil) newnode(k->ch[t]);
        k=k->ch[t];
      }
    k->num++;
  }
void AC_automaton()
  {
    int h,t;Anode *now;
    for (Q[h=t=1]=root;now=Q[h],h<=t;++h)
      for (int i=0;i<M;++i)
        if (now->ch[i]==nil) now->ch[i]=now->fail->ch[i];
          else now->ch[i]->fail=now->fail->ch[i],Q[++t]=now->ch[i];
  }
void getans(char* s)
  {
    Anode *k=root;int t;
    for (int i=0;s[i];++i)
      {
        t=s[i]-'a';k=k->ch[t];
        for (Anode *j=k;j!=nil && j->num!=-1;j=j->fail) ans+=j->num,j->num=-1;
      }
  }
int main()
  {
    for (scanf("%d",&data);data;--data)
      {
        clear();
        scanf("%d\n",&n);
        for (int i=1;i<=n;++i)
          scanf("%s",s),insert(s);
        AC_automaton();
        scanf("%s",s);  
        getans(s);
        printf("%d\n",ans);
      }
  }