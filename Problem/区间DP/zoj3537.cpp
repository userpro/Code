// 凸包 最优三角形 区间DP
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

const double eps=1e-8;
const double PI=acos(-1.0);
int sgn(double x)
{
    if(fabs(x)<eps) return 0;
    if (x<0) return -1;
    return 1;
}

struct Point
{
    double x,y;
    Point() { }
    Point(double _x,double _y) : x(_x),y(_y) { }
    Point operator - (const Point& b) const
    {
        return Point(x-b.x,y-b.y);
    }
    double operator ^ (const Point& b) const
    {
        return x*b.y-y*b.x;
    }
    double operator * (const Point& b) const
    {
        return x*b.x+y*b.y;
    }
    void transXY(double B)
    {
        double tx=x,ty=y;
        x=tx*cos(B)-ty*sin(B);
        y=tx*sin(B)+ty*cos(B);
    }
};

double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}

const int MAXN = 310;
Point list[MAXN];
int Stack[MAXN],top;
bool _cmp(Point p1,Point p2)
{
    double tmp=(p1-list[0])^(p2-list[0]);
    if (sgn(tmp)>0) return true;
    else if (sgn(tmp)==0 && sgn(dist(p1,list[0])-dist(p2,list[0]))<=0)
        return true;
    else
        return false;
}

void Graham(int n)
{
    Point p0;
    int k=0;
    p0=list[0];
    for (int i=1;i<n;i++)
    {
        if (p0.y>list[i].y)
        {
            p0=list[i];
            k=i;
        }
    }
    swap(list[k],list[0]);
    sort(list+1,list+n,_cmp);
    if (n==1)
    {
        top=1;
        Stack[0]=0;
        return;
    }
    if (n==2)
    {
        top=2;
        Stack[0]=0;
        Stack[1]=1;
        return;
    }
    Stack[0]=0; Stack[1]=1;
    top=2;
    for (int i=2;i<n;i++)
    {
        while (top>1 && sgn((list[Stack[top-1]]-list[Stack[top-2]])^(list[i]-list[Stack[top-2]]))<=0)
            top--;
        Stack[top++]=i;
    }
}

int N,p,x,y;
int dp[MAXN][MAXN],cost[MAXN][MAXN];
int dist2(Point& p1,Point& p2)
{
    return abs((int)(p1.x+p2.x))*abs((int)(p1.y+p2.y)) % p;
}

int main()
{
    while (scanf("%d%d",&N,&p)!=EOF)
    {
        for (int i=0;i<N;i++)
        {
            scanf("%d%d",&x,&y);
            list[i]=Point(x,y);
        }
        Graham(N);
        if (top<N)
        {
            printf("I can't cut.\n");
            continue;
        }

        CLR(cost,0);
        for (int i=0;i<N;i++)
            for (int j=i+2;j<N;j++)
                cost[i][j]=cost[j][i]=dist2(list[Stack[i]],list[Stack[j]]);

        for (int i=0;i<N;i++)
            for (int j=0;j<N;j++)
            {
                dp[i][j]=INF;
                dp[i][(i+1)%N]=0;
            }

        for (int len=2;len<N;len++)
            for (int i=0;i+len<N;i++)
            {
                int j=i+len;
                for (int k=i+1;k<=j-1;k++)
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+cost[i][k]+cost[k][j]);
            }

        printf("%d\n", dp[0][N-1]);
    }
    return 0;
}