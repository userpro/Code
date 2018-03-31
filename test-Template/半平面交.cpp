//h2732
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N=100012;
struct Point 
  {
    double x,y;
    Point (){}
    Point (double _x,double _y):x(_x),y(_y){}
  } a[N],b[N];
struct Half_Plane
  {
    double a,b,c;
    Half_Plane(){}
    Half_Plane (Point p1,Point p2)
      {
        a=p1.y-p2.y,b=p2.x-p1.x,c=p1.x*p2.y-p1.y*p2.x;
      }
    Half_Plane(double _a,double _b,double _c):a(_a),b(_b),c(_c){}
    inline bool Inside (Point p) {return a*p.x+b*p.y+c>=0;}
  };
inline Point Get_Point(Half_Plane m,Half_Plane n)
  {
    return Point((m.c*n.b-n.c*m.b)/(n.a*m.b-m.a*n.b),(m.c*n.a-n.c*m.a)/(n.b*m.a-m.b*n.a));
  }
int q,top;
double x,y,z;
bool inside[N];
bool work(Half_Plane now)
  {
    a[top+1]=a[1];
    for (int i=1;i<=top+1;++i) inside[i]=now.Inside(a[i]);
    int t=0;
    for (int i=1;i<=top;++i)
      {
        if (inside[i]) b[++t]=a[i];
        if (inside[i]^inside[i+1]) 
          b[++t]=Get_Point(Half_Plane(a[i],a[i+1]),now);
      }
    copy(b+1,b+t+1,a+1);top=t;
    return top>0;
  }
int main()
  {
    scanf("%d",&q);
    a[++top]=Point(-1E15,-1E15);
    a[++top]=Point(1E15,-1E15);
    a[++top]=Point(1E15,1E15);
    a[++top]=Point(-1E15,1E15);
    for (int i=1;i<=q;++i)
      {
        scanf("%lf%lf%lf",&x,&y,&z);
        bool f1=work(Half_Plane(x*x,x,-y)),
             f2=work(Half_Plane(-x*x,-x,z));
        if (!f1 || !f2) {printf("%d\n",i-1);return 0;}
      }
    printf("%d\n",q);
  }