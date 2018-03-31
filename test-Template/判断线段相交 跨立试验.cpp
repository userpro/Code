//t1683
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int N=2001;
const double e=1E-4;
struct point {double x,y;} dl[N],dr[N],wl[N],wr[N],S;
int n,k,ans=0;

int cross(point p1,point p2,point p3)
  {
    double 
      x1=p2.x-p1.x,
      x2=p3.x-p1.x,
      y1=p2.y-p1.y,
      y2=p3.y-p1.y;
    double k=x1*y2-x2*y1;
    if (fabs(k)<e) return 0;
    if (k>0) return 1;else return -1;
  }
bool onSegment(point p1,point p2,point p3)
  {
    double 
      x1=min(p1.x,p2.x),
      x2=max(p1.x,p2.x),
      y1=min(p1.y,p2.y),
      y2=max(p1.y,p2.y);
    if (x1<=p3.x && p3.x<=x2 && y1<=p3.y && p3.y<=y2) return true;
    return false;
  }
bool judge(point p1,point p2,point p3,point p4)
  {
    int d1=cross(p3,p4,p1);
    int d2=cross(p3,p4,p2);
    int d3=cross(p1,p2,p3);
    int d4=cross(p1,p2,p4);
    if (d1*d2<0 && d3*d4<0) return true;
    if (d1==0 && onSegment(p3,p4,p1)) return true;
    if (d2==0 && onSegment(p3,p4,p2)) return true;
    if (d3==0 && onSegment(p1,p2,p3)) return true;
    if (d4==0 && onSegment(p1,p2,p4)) return true;
    return false;
  }
bool check(point wll,point wrr)
  {
    if (fabs(wll.x-wrr.x)<e && fabs(wll.y-wrr.y)<e) 
      return false;
    if (cross(S,wll,wrr)==0) return false;
    bool ok1=true,ok2=true,t1,t2,t3,t4;
    for (int i=1;i<=n;++i)
      {
        if (i==k) continue;
        t1=judge(S,wll,dl[i],wl[i]);
        t2=judge(S,wll,dr[i],wr[i]);
        t3=judge(S,wrr,dl[i],wl[i]);
        t4=judge(S,wrr,dr[i],wr[i]);
        if ((t1 && t3) || (t2 && t4)) return false;
        if (t1 || t2) ok1=false;
        if (t3 || t4) ok2=false;
      }
    if (ok1 || ok2) return true;
    point mid;
    mid.x=(wll.x+wrr.x)/2;
    mid.y=(wll.y+wrr.y)/2;
    return check(wll,mid) || check (mid,wrr);
  }
int main()
  {
    scanf("%d%lf%lf",&n,&S.x,&S.y);
    for (int i=1;i<=n;++i)
      {
        scanf("%lf%lf",&dl[i].x,&dl[i].y);
        scanf("%lf%lf",&dr[i].x,&dr[i].y);
        scanf("%lf%lf",&wl[i].x,&wl[i].y);
        scanf("%lf%lf",&wr[i].x,&wr[i].y);
        if (judge(dl[i],wl[i],dr[i],wr[i])) 
          swap(wl[i],wr[i]);
      }
    for (k=1;k<=n;++k) 
      if (check(wl[k],wr[k])) ++ans;
    printf("%d\n",ans);
  }