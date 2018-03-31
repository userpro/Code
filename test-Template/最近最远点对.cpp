//pointpair
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int N=100012;const double e=1E-8,inf=1E100;
struct point 
  {
    double x,y;
    point operator +(const point b)
      {
        point ans;ans.x=x+b.x;ans.y=y+b.y;
        return ans;
      }
    point operator -(const point b)
      {
        point ans;ans.x=x-b.x;ans.y=y-b.y;
        return ans;
      }
    double operator *(const point b)
      {
        double k=x*b.y-b.x*y;
        if (-e<k && k<e) return 0;else return k;
      }
  } a[N];
int n,Z[N*2];

inline double dist(point p1,point p2)
  {
    point p=p1-p2;
    return sqrt(p.x*p.x+p.y*p.y);
  }
inline double S(point p1,point p2,point p3)
  {
    double k=(p2-p1)*(p3-p1);
    if (k<0) return -k;else return k;
  }
inline bool cmp1(point p,point q)
  {
    return p.x<q.x || p.x==q.x && p.y<q.y;
  }
inline bool cmp2(point p,point q)
  {
    return p.y<q.y || p.y==q.y && p.x<q.x;
  }
inline bool cmp3(point p,point q)
  {
    return (p-a[1])*(q-a[1])>0 || (p-a[1])*(q-a[1])==0 && dist(a[1],p)+e<dist(a[1],q);
  }
double dc(int l,int r)
  {
    if (l==r) return inf;
    if (l+1==r) return dist(a[l],a[r]);
    int mid=(l+r)>>1;
    double ans=min(dc(mid+1,r),dc(l,mid)),p=(a[mid].x+a[mid+1].x)/2;
    if (a[mid].x<=p-ans || a[mid+1].x>=p+ans) return ans;
    int x=mid,y=mid+1;
    while (x>l && a[x-1].x>p-ans) --x;
    while (y<r && a[y+1].x<p+ans) ++y;
    sort(a+x,a+mid+1,cmp2);
    sort(a+mid+1,a+y+1,cmp2);
    int head=mid+1,tail=mid;
    for (int i=x;i<=mid;++i)
      {
        while (head<=tail && a[i].y-a[head].y>=ans) ++head;
        while (tail<y && a[tail+1].y-a[i].y<ans) ++tail;
        for (int j=head;j<=tail;++j) ans=min(ans,dist(a[i],a[j]));
      }
    sort(a+x,a+y+1,cmp1);
    return ans;
  }
double GetMin()
  {
    sort(a+1,a+n+1,cmp1);
    return dc(1,n);
  }
double GetMax()
  {
    int w=1;
    for (int i=2;i<=n;++i)
      if (a[i].x<a[w].x || a[i].x==a[w].x && a[i].y<a[w].y) w=i;
    swap(a[w],a[1]);
    sort(a+2,a+n+1,cmp3);
    int t;Z[t=1]=1;
    for (int i=2;i<=n;++i)
      {
        while (t>1 && (a[Z[t]]-a[Z[t-1]])*(a[i]-a[Z[t-1]])<=0) --t;
        Z[++t]=i;
      }
    for (int i=1;i<=t;++i) Z[t+i]=Z[i];
    w=1;double ans=0;
    if (t==1) ans=0;
    if (t==2) ans=dist(a[Z[1]],a[Z[2]]);
    if (t>2)
      for (int i=1;i<=t;++i)
        {
          while (S(a[Z[i]],a[Z[i+1]],a[Z[w]])<=S(a[Z[i]],a[Z[i+1]],a[Z[w+1]])) ++w;
          ans=max(ans,dist(a[Z[i]],a[Z[w]]));
          ans=max(ans,dist(a[Z[i+1]],a[Z[w]]));
        }
    return ans;
  }
int main()
  {
    freopen("pointpair.in","r",stdin);
    freopen("pointpair.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%lf%lf",&a[i].x,&a[i].y);
    printf("%.2lf %.2lf\n",GetMin(),GetMax());
    fclose(stdin);fclose(stdout);
    return 0;
  }