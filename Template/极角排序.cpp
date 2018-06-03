struct point
{
    double x,y;
};

double cross(double x1,double y1,double x2,double y2) //计算叉积
{
    return (x1*y2-x2*y1);
}

double compare(point a,point b,point c)
{
    return cross((b.x-a.x),(b.y-a.y),(c.x-a.x),(c.y-a.y));
}

bool cmp0(const point& a, const point& b) //利用complex类按极角从小到大排序
{
    complex<double> c1(a.x,a.y); //头文件 #include<complex>
    complex<double> c2(b.x,b.y);
    if( arg(c1) == arg(c2))
        return a.x<b.x;
    return arg(c1) < arg(c2);
}

bool cmp1(point a,point b)//利用atan2()函数按极角从小到大排序
{
    if(atan2(a.y,a.x)!=atan2(b.y,b.x))
        return atan2(a.y,a.x)<atan2(b.y,b.x);
    else return a.x<b.x;
}

bool cmp2(point a,point b) //利用叉积按极角从小到大排序
{
    point c; //原点
    c.x = 0;
    c.y = 0;
    if(compare(c,a,b)==0)
        return a.x<b.x;
    else return compare(c,a,b)>0;
}

int Quadrant(point a)　　   //象限排序
{
    if(a.x>0&&a.y>=0)  return 1;
    if(a.x<=0&&a.y>0)  return 2;
    if(a.x<0&&a.y<=0)  return 3;
    if(a.x>=0&&a.y<0)  return 4;
}


bool cmp3(point a,point b)  //先按象限从小到大排序 再按极角从小到大排序
{
    if(Quadrant(a)==Quadrant(b))
        return cmp1(a,b);
    else Quadrant(a)<Quadrant(b);
}
