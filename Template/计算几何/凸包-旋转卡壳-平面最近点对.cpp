// hdu1589
// 可把vector换成下标数组 优化空间不大
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const long long inf=1e18;
const int maxn=1e5+10;
int n;
struct Point
{
     long long x,y;
}p[maxn];

inline long long dis(Point&p1,Point&p2) { return ((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)); }
//计算叉积, 小于0说明p1在p2的逆时针方向(右边), 即p0p1的极角大于p0p2的极角
inline long long cross(Point&p0,Point&p1,Point&p2) {
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
// 极角排序
bool cmp_polar_angle(Point&p1,Point&p2) {
    long long tmp=cross(p[0],p1,p2);
    if (tmp==0) return dis(p[0],p1)<dis(p[0],p2);
    else return tmp>0;
}

// 凸包
vector<Point> GrahamScan() {
    vector<Point> v;
    int idx=0;
    for (int i=1;i<n;i++) {
        if (p[i].y<p[idx].y||(p[i].y==p[idx].y&&p[i].x<p[idx].x)) idx=i;
    }
    swap(p[0],p[idx]);
    sort(p+1,p+n,cmp_polar_angle);
    v.emplace_back(p[0]); v.emplace_back(p[1]);
    int top=1;
    for (int i=2;i<n;++i) {
        while (top>0 && cross(v[top-1],p[i],v[top])>=0)
            top--,v.pop_back();
        top++,v.emplace_back(p[i]);
    }
    return v;
}

// 最远点对-旋转卡壳
long long rotating_caliper(vector<Point> v) {
    long long maxdis=0;
    int len=v.size();
    if (len==2) maxdis=dis(v[0],v[1]);
    else {
        v.emplace_back(v[0]);
        int j=2;
        for (int i=0;i<len;i++) {
            while (cross(v[i],v[i+1],v[j])<cross(v[i],v[i+1],v[j+1]))
                j=(j+1)%len;
            maxdis=max(maxdis,max(dis(v[i],v[j]),dis(v[j],v[i+1])));
        }
    }
    return maxdis;
}

// -- 最近点对 --
bool cmpx(Point&p1,Point&p2) { return p1.x<p2.x || (p1.x==p2.x && p1.y<p2.y); }
bool cmpy(Point&p1,Point&p2) { return p1.y<p2.y || (p1.y==p2.y && p1.x<p2.x); }

long long closest_pair(int left,int right) {
    long long d=inf;
    if (left==right) return d;
    if (left+1==right) return dis(p[left],p[right]);
    int mid=(left+right)>>1;
    long long d1=closest_pair(left,mid);
    long long d2=closest_pair(mid+1,right);
    d=min(d1,d2);
    vector<Point> closest_t;
    for (int i=left;i<=right;i++) {
        if (abs(p[i].x-p[mid].x)<=d) closest_t.emplace_back(p[i]);
    }
    sort(closest_t.begin(), closest_t.end(),cmpy);
    int cnt=closest_t.size();
    for (int i=0;i<cnt;i++)
        for (int j=i+1;j<cnt && (closest_t[j].y-closest_t[i].y)*(closest_t[j].y-closest_t[i].y)<d;j++) // 剪枝很重要
            d=min(d,dis(closest_t[i],closest_t[j]));

    return d;
}
// -- 最近点对 --

int main() {
    int cas=0;
    while (~scanf("%d",&n) && n) {
        for (int i=0;i<n;i++) scanf("%lld%lld",&p[i].x,&p[i].y);
        // 最远点对(旋转卡壳)
        long long maxdis=rotating_caliper(GrahamScan());
        // 最近点对
        sort(p,p+n,cmpx);
        long long mindis=closest_pair(0,n-1);
        printf("Case %d:\n", ++cas);
        printf("Distance of the nearest couple is %.3lf\n", sqrt((double)(mindis)));
        printf("Distance of the most distant couple is %.3lf\n\n", sqrt((double)(maxdis)));
    }
    return 0;
}