#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const double EPS=1E-9,INF=1E100;
struct Point 
  {
    double x,y;
    Point (){}
    Point (double _x,double _y):x(_x),y(_y){}
    inline void Read() {scanf("%lf%lf",&x,&y);}
    inline Point operator +(Point b)
      {
        return Point(x+b.x,y+b.y);
      }
    inline Point operator -(Point b)
      {
        return Point(x-b.x,y-b.y);
      }
    inline double operator *(Point b)
      {
        double k=x*b.y-b.x*y;
        if (-EPS<k && k<EPS) return 0;else return k;
      }
    inline double operator /(Point b) {return x/b.x;}
    inline Point operator *(double k)
      {
        return Point(x*k,y*k);
      }
    inline Point operator /(double k)
      {
        return Point(x/k,y/k);
      }
    inline bool operator == (Point b)
      {
        return fabs(b.x-x)<=EPS && fabs(b.y-y)<EPS;
      }
    inline double Len() {return sqrt(x*x+y*y);}
    inline Point Symmetry_Point(Point b)//关于点b的对称点
      {
        return Point(2*b.x-x,2*b.y-y);
      }
  } a,b,c;
inline double Dist(Point p1,Point p2)//点p1,p2的距离
  {
    return (p1-p2).Len();
  }
  inline Point Get_Cur(Point p,double d)//以O为圆心在射线OP上截取长度为d的一段
  {
    double D=sqrt(p.x*p.x+p.y*p.y);
    return Point(d*p.x/D,d*p.y/D);
  }
inline Point Mid_Point(Point p1,Point p2)//点p1,p2的中点
  {
    return Point((p1.x+p2.x)/2,(p1.y+p2.y)/2);
  }
struct Line
  {
    double a,b,c;//ax+by+c=0
    Line (){}
    Line (Point p1,Point p2)
      { 
        a=p1.y-p2.y,b=p2.x-p1.x,c=p1.x*p2.y-p2.x*p1.y;
      }
    Line (double _a,double _b,double _c):a(_a),b(_b),c(_c){}
    inline Line Vertical_Line(Point p)//过点p的垂线
      {
        return Line(b,-a,a*p.y-b*p.x);
      }
  };
inline bool Parallel(Line m,Line n)//判断m,n是否平行
  {
    if (fabs(m.a*n.b-m.b*n.a)<EPS) return true;else return false;
  }
inline bool Vertical(Line m,Line n)//判断m,n是否垂直
  {
    if (fabs(m.a*n.a+m.b*n.b)<EPS) return true;else return false;
  }
inline Point Crossover_Point(Line m,Line n)//直线m,n的交点
  {
    return Point((m.c*n.b-n.c*m.b)/(n.a*m.b-m.a*n.b),(m.c*n.a-n.c*m.a)/(n.b*m.a-m.b*n.a));
  }
inline double Dist(Point p,Line l)//点p到直线l的距离
  {
    return Dist(p,Crossover_Point(l,l.Vertical_Line(p)));
  }
inline double Dist(Point p,Point p1,Point p2)//点p到线段p1p2的距离（如果由p无法向p1p2引垂线返回INF）
  {
    Line l=Line(p1,p2);
    Point X=Crossover_Point(l,l.Vertical_Line(p));
    if (fabs(Dist(p1,X)+Dist(p2,X)-Dist(p1,p2))<EPS) return Dist(p,X);
      else return INF;
  }
inline Line Perpendicular_Bisector(Point p1,Point p2)//线段p1p2的垂直平分线
  {
    Point p3=Mid_Point(p1,p2);
    return Line(p1,p2).Vertical_Line(p3);
  }
inline Point Circumcenter(Point p1,Point p2,Point p3)//三角形p1p2p3的外心
  {
    return Crossover_Point(Perpendicular_Bisector(p1,p2),Perpendicular_Bisector(p3,p1));
  }

  
struct Half_Plane
  {
    double a,b,c;//ax+by+c>=0
    Half_Plane(){}
    Half_Plane (Point p1,Point p2)//表示向量p1p2左手边的平面
      {
        a=p1.y-p2.y,b=p2.x-p1.x,c=p1.x*p2.y-p1.y*p2.x;
      }
    Half_Plane (double _a,double _b,double _c):a(_a),b(_b),c(_c){}
    inline bool Inside (Point p) {return a*p.x+b*p.y+c>=0;}//判断点p是否在半平面内
  };
inline Point Crossover_Point(Half_Plane m,Half_Plane n)//半平面m,n的交点
  {
    return Point((m.c*n.b-n.c*m.b)/(n.a*m.b-m.a*n.b),(m.c*n.a-n.c*m.a)/(n.b*m.a-m.b*n.a));
  }
  

int main()
  {
  }