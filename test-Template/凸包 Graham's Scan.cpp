#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int N=10001;
const double e=1E-8;
struct point {double x,y;} a[N];
int n,Z[N],top=0;
double ans=0;

int cross(point p1,point p2,point p3)
  {
    double x1=p2.x-p1.x,
           y1=p2.y-p1.y,
           x2=p3.x-p1.x,
           y2=p3.y-p1.y;
    double k=x1*y2-x2*y1;
    if (fabs(k)<e) return 0;
    if (k>0) return 1;else return -1;
  }
double dist(point a,point b)
  {
    double x=a.x-b.x,y=a.y-b.y;
    return sqrt(x*x+y*y);
  }
void qsort(int s,int t)
  {
    int i=s,j=t;
    point mid=a[(i+j)>>1];
    do
      {
        while (cross(a[1],mid,a[i])<0 ||
          cross(a[1],mid,a[i])==0 && 
          dist(a[1],mid)-e>dist(a[1],a[i])) ++i;
        while (cross(a[1],mid,a[j])>0 ||
          cross(a[1],mid,a[j])==0 &&
          dist(a[1],mid)+e<dist(a[1],a[j])) --j;
        if (i<=j) swap(a[i],a[j]),++i,--j;
      }
    while (i<=j);
    if (s<j) qsort(s,j);
    if (i<t) qsort(i,t);
  }
int main()
  {
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%lf%lf",&a[i].x,&a[i].y);
    int r=1;
    for (int i=2;i<=n;++i)
      if (a[i].x<a[r].x || a[i].x==a[r].x && a[i].y<a[r].y) r=i;
    swap(a[r],a[1]);
    qsort(2,n);
    Z[++top]=1;Z[++top]=2;
    for (int i=3;i<=n;++i)
      {
        while (top>1 && cross(a[Z[top-1]],a[Z[top]],a[i])<=0) --top;
        Z[++top]=i;
      }
    for (int i=1;i<top;++i) ans+=dist(a[Z[i]],a[Z[i+1]]);
    ans+=dist(a[Z[1]],a[Z[top]]);
    printf("%.2lf\n",ans);
  }