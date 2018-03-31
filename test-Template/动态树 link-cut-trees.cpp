//h2814
#include <cstdio> 
#include <iostream> 
#include <cstring> 
#include <cmath> 
 
using namespace std; 
 
const int N=50012,M=N*2,INF=2147483647; 
int n,m,Q[N],a,b,c; 
char s[10]; 
struct Edge {int u,v;Edge *next;} e[M],*point[N],*P=e; 
inline void Add_Edge(int a,int b) 
  { 
    P->u=a;P->v=b;P->next=point[a];point[a]=P++; 
  } 
struct Info  
  { 
    long long max;int len; 
  } Black,Empty; 
inline Info max(Info t1,Info t2) 
  { 
    if (t1.max>=t2.max)  
      return t1;else return t2; 
  } 
inline Info operator + (Info a,Info b) 
  { 
    Info ans;ans.max=a.max+b.max;ans.len=a.len+b.len;return ans; 
  } 
struct Snode 
  { 
    Snode *lch,*rch,*p; 
    bool color[2],flag; 
    int cover,id; 
    Info l[2][2],r[2][2],q[2],sum[2][2][2],a[2][2]; 
    inline void Update() 
      { 
        for (int k=0;k<=1;++k) 
          { 
            q[k]=max(lch->q[k],rch->q[k]); 
            for (int i=0;i<=1;++i) 
              { 
                l[k][i]=lch->l[k][i]; 
                l[k][i]=max(l[k][i],lch->sum[k][i][i]+a[k][i]+rch->l[k][i]); 
                l[k][i]=max(l[k][i],lch->sum[k][i][i]+a[k][1]+a[k][0]+rch->l[k][i^1]); 
                l[k][i]=max(l[k][i],lch->sum[k][i][i^1]+a[k][i^1]+rch->l[k][i^1]); 
                l[k][i]=max(l[k][i],lch->sum[k][i][i^1]+a[k][1]+a[k][0]+rch->l[k][i]); 
                r[k][i]=rch->r[k][i]; 
                r[k][i]=max(r[k][i],rch->sum[k][i][i]+a[k][i]+lch->r[k][i]); 
                r[k][i]=max(r[k][i],rch->sum[k][i][i]+a[k][1]+a[k][0]+lch->r[k][i^1]); 
                r[k][i]=max(r[k][i],rch->sum[k][i^1][i]+a[k][i^1]+lch->r[k][i^1]); 
                r[k][i]=max(r[k][i],rch->sum[k][i^1][i]+a[k][1]+a[k][0]+lch->r[k][i]); 
                sum[k][i][i]=max(lch->sum[k][i][i]+a[k][i]+rch->sum[k][i][i],lch->sum[k][i][i]+a[k][1]+a[k][0]+rch->sum[k][i^1][i]); 
                sum[k][i][i]=max(sum[k][i][i],lch->sum[k][i][i^1]+a[k][i^1]+rch->sum[k][i^1][i]); 
                sum[k][i][i]=max(sum[k][i][i],lch->sum[k][i][i^1]+a[k][1]+a[k][0]+rch->sum[k][i][i]); 
                sum[k][i][i^1]=max(lch->sum[k][i][i]+a[k][i]+rch->sum[k][i][i^1],lch->sum[k][i][i]+a[k][1]+a[k][0]+rch->sum[k][i^1][i^1]); 
                sum[k][i][i^1]=max(sum[k][i][i^1],lch->sum[k][i][i^1]+a[k][i^1]+rch->sum[k][i^1][i^1]); 
                sum[k][i][i^1]=max(sum[k][i][i^1],lch->sum[k][i][i^1]+a[k][1]+a[k][0]+rch->sum[k][i][i^1]); 
                q[k]=max(q[k],lch->r[k][i]+a[k][i]+rch->l[k][i]); 
                q[k]=max(q[k],lch->r[k][i]+a[k][1]+a[k][0]+rch->l[k][i^1]); 
              } 
          } 
      } 
    inline bool Is_Lch() {return this==p->lch;} 
    inline void Set_Lch(Snode *x) {x->p=this;lch=x;} 
    inline void Set_Rch(Snode *x) {x->p=this;rch=x;} 
    inline void Paint(int c) 
      { 
        if (id==0) return; 
        color[0]=color[1]=c;cover=c; 
        if (c==0) 
          { 
            q[1]=q[0]; 
            for (int i=0;i<=1;++i) 
              { 
                a[1][i]=a[0][i]; 
                l[1][i]=l[0][i];r[1][i]=r[0][i]; 
                sum[1][i][i]=sum[0][i][i];sum[1][i][i^1]=sum[0][i][i^1]; 
              } 
          } 
        else 
          { 
            q[1]=Black; 
            for (int i=0;i<=1;++i) 
              { 
                a[1][i]=Black;l[1][i]=Empty;r[1][i]=Empty; 
                sum[1][i][i]=Black;sum[1][i][i^1]=Black; 
              } 
          } 
      } 
    inline void Pass() 
      { 
        if (cover==-1) return;lch->Paint(cover);rch->Paint(cover);cover=-1; 
      } 
    inline void L() 
      { 
        Snode *fa=p;p=fa->p; 
        if (fa->flag) flag=true,fa->flag=false; 
          else if (fa->Is_Lch()) fa->p->Set_Lch(this);else fa->p->Set_Rch(this); 
        fa->Set_Rch(lch);Set_Lch(fa);fa->Update(); 
      } 
    inline void R() 
      { 
        Snode *fa=p;p=fa->p; 
        if (fa->flag) flag=true,fa->flag=false; 
          else if (fa->Is_Lch()) fa->p->Set_Lch(this);else fa->p->Set_Rch(this); 
        fa->Set_Lch(rch);Set_Rch(fa);fa->Update(); 
      } 
  } T[N],*R=T,*nil=T,*pos[N]; 
inline void New(Snode *&node,int id,Snode *fa) 
  { 
    node=++R;node->id=id; 
    node->lch=node->rch=nil;node->flag=true;node->p=fa; 
    node->cover=-1;node->color[0]=node->color[1]=false; 
    for (int k=0;k<=1;++k) 
      for (int i=0;i<=1;++i) 
        node->a[k][i].max=1,node->a[k][i].len=1; 
    node->Update(); 
  } 
inline void Splay(Snode *x) 
  { 
    x->Pass(); 
    while (!x->flag) 
      { 
        if (!x->p->flag) x->p->p->Pass();x->p->Pass();x->Pass(); 
        if (x->p->flag) 
          { 
            if (x->Is_Lch()) x->R();else x->L(); 
            break; 
          } 
        if (x->p->Is_Lch()) 
          if (x->Is_Lch()) x->p->R(),x->R(); 
            else x->L(),x->R(); 
        else
          if (x->Is_Lch()) x->R(),x->L(); 
            else x->p->L(),x->L(); 
      } 
    x->Update(); 
  } 
void Prepare() 
  { 
    Black.max=-INF;Black.len=0; 
    Empty.max=0;Empty.len=0; 
    nil->lch=nil->rch=nil->p=nil;nil->flag=false; 
    nil->cover=-1;nil->color[0]=nil->color[1]=true; 
    for (int k=0;k<=1;++k) 
      { 
        for (int i=0;i<=1;++i) 
          { 
            nil->a[k][i]=Empty; 
            nil->l[k][i]=nil->r[k][i]=Empty; 
            nil->sum[k][i][i]=Empty;nil->sum[k][i][i^1]=Black; 
          } 
        nil->q[k]=Black; 
      } 
  } 
 
void Bfs() 
  { 
    int h,t;pos[0]=nil; 
    New(pos[1],1,nil); 
    for (Q[h=t=1]=1;h<=t;++h) 
      for (Edge *j=point[Q[h]];j;j=j->next) 
        if (pos[j->v]==NULL)  
          New(pos[j->v],j->v,pos[Q[h]]),Q[++t]=j->v; 
  } 
void Access(Snode *x,int opt) 
  { 
    for (Snode *y=nil;x!=nil;y=x,x=x->p) 
      {  
        Splay(x); 
        if (x->p==nil) 
          { 
            if (opt==1)  
              { 
                x->Paint(c);x->cover=-1; 
                y->Paint(c);x->rch->Paint(c); 
              } 
            if (opt==2 || opt==3) 
              { 
                Info ans; 
                ans=max(y->q[1],x->rch->q[1]); 
                for (int i=0;i<=1;++i) 
                  { 
                    ans=max(ans,x->rch->l[1][i]+x->a[1][i]+y->l[1][i]); 
                    ans=max(ans,x->rch->l[1][i]+x->a[1][i]+x->a[1][i^1]+y->l[1][i^1]); 
                  } 
                if (ans.max==-INF) 
                  if (opt==2) puts("Bad Request.");else puts("0"); 
                else
                  if (opt==2) printf("%lld\n",ans.max); 
                    else printf("%d\n",ans.len); 
              } 
          } 
        x->rch->flag=true;y->flag=false;x->Set_Rch(y);x->Update(); 
      } 
  } 
void Cover(int a,int b) {Access(pos[a],0);Access(pos[b],1);} 
void CVal(int a)  
  { 
    Access(pos[a],0);Splay(pos[a]); 
    pos[a]->a[0][b].max=c; 
    if (!pos[a]->color[b]) pos[a]->a[1][b].max=c; 
    pos[a]->Update(); 
  } 
void CColor(int a)  
  { 
    Splay(pos[a]); 
    pos[a]->color[b]=c; 
    if (pos[a]->color[b]) pos[a]->a[1][b]=Black; 
      else pos[a]->a[1][b]=pos[a]->a[0][b]; 
    pos[a]->Update(); 
  } 
void QMax(int a,int b) {Access(pos[a],0);Access(pos[b],2);} 
void QLen(int a,int b) {Access(pos[a],0);Access(pos[b],3);} 
int main() 
  { 
    Prepare(); 
    scanf("%d",&n); 
    for (int i=1;i<n;++i)  
      scanf("%d%d",&a,&b),Add_Edge(a,b),Add_Edge(b,a); 
    Bfs(); 
    scanf("%d",&m); 
    for (int i=1;i<=m;++i) 
      { 
        scanf("\n%s",s); 
        if (s[0]=='C') 
          { 
            scanf("%d%d%d",&a,&b,&c); 
            if (s[1]=='o') Cover(a,b); 
            if (s[1]=='V') CVal(a); 
            if (s[1]=='C') CColor(a); 
          } 
        else
          { 
            scanf("%d%d",&a,&b); 
            if (s[1]=='M') QMax(a,b); 
            if (s[1]=='L') QLen(a,b); 
          } 
      } 
  }