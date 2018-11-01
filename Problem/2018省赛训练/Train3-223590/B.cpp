//http://acm.fzu.edu.cn/problem.php?pid=2273
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const double eps=1e-8;
const double pi=acos(-1.0);
int sgn(double x)
{
    if (fabs(x)<eps) return 0;
    if (x<0) return -1;
    return 1;
}
struct Point
{
    double x,y;
    Point() {}
    Point(double _x,double _y)
    {
        x=_x;
        y=_y;
    }
    Point operator +(const Point &b) const
    {
        return Point(x+b.x,y+b.x);
    }
    Point operator -(const Point &b) const
    {
        return Point(x-b.x,y-b.y);
    }
    double operator ^(const Point &b) const
    {
        return x*b.y-y*b.x;
    }
    double operator *(const Point &b) const
    {
        return x*b.x+y*b.y;
    }
    Point operator /(const double b) const
    {
        return Point(x/b,y/b);
    }
};

struct Line
{
    Point s,e;
    Line() {}
    Line(Point _s,Point _e)
    {
        s=_s;
        e=_e;
    }
};

double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}
bool inter(Line l1,Line l2)
{
    return
        max(l1.s.x,l1.e.x)>=min(l2.s.x,l2.e.x) &&
        max(l2.s.x,l2.e.x)>=min(l1.s.x,l1.e.x) &&
        max(l1.s.y,l1.e.y)>=min(l2.s.y,l2.e.y) &&
        max(l2.s.y,l2.e.y)>=min(l1.s.y,l1.e.y) &&
        sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e))<=0 &&
        sgn((l1.s-l2.e)^(l2.s-l2.e))*sgn((l1.e-l2.e)^(l2.s-l2.e))<=0;
}
Point o;
bool _cmp(Point p1,Point p2)
{
    double tmp=(p1-o)^(p2-o);
    if (sgn(tmp)>0) return true;
    else if (sgn(tmp)==0 && sgn(dist(p1,o)-dist(p2,o))<=0) return true;
    else return false;
}

bool OnSeg(Point P,Line L)
{
    return 
        sgn((L.s-P)^(L.e-P))==0 &&
        sgn((P.x-L.s.x)*(P.x-L.e.x))<=0 &&
        sgn((P.y-L.s.y)*(P.y-L.e.y))<=0;
}
int inConvexPoly(Point a,Point p[],int n)
{
    for (int i=0;i<n;i++)
    {
        if (sgn((p[i]-a)^(p[(i+1)%n]-a))<0) return -1;  // out
        else if (OnSeg(a,Line(p[i],p[(i+1)%n]))) return 0;  // on
    }
    return 1; // in
}

Point p[6];


int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        for (int i=0;i<6;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        bool xj=false;
        for (int i=0;i<3;i++)
        {
            for (int j=0;j<3;j++)
            {
                Line l1=Line(p[i],p[(i+1)%3]);
                Line l2=Line(p[j+3],p[(j+1)%3+3]);
                if (inter(l1,l2))
                {
                    xj=true;
                    break;
                }
            }
            if (xj) break;
        }
        if (xj)
        {
            printf("intersect\n");
            continue;
        }
        int in1=0,in2=0;
        o=(p[0]+p[1]+p[2])/3.0;
        sort(p,p+3,_cmp);
        o=(p[3]+p[4]+p[5])/3.0;
        sort(p+3,p+6,_cmp);
        for (int i=0;i<3;i++)
        {
            if (inConvexPoly(p[i],p+3,3)==1) in1++;
            if (inConvexPoly(p[i+3],p,3)==1) in2++;
        }
        if (in1==3||in2==3) printf("contain\n");
        else printf("disjoint\n");
    }
    return 0;
}