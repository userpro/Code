// hdu5033 单调栈维护凸包
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=1e6+10;
const double PI=acos(-1.0);
int t,n,m;
struct Build
{
    Build() { ang[0]=ang[1]=0; }
    double x,h;
    double ang[2];
    int id;
    bool flag;
    bool operator <(const Build&b) const { return x<b.x; }
}b[maxn<<1],q[maxn<<1];

bool cmp1(const Build&b1,const Build&b2) { return b1.x<b2.x; }
bool cmp2(const Build&b1,const Build&b2) { return b1.id<b2.id; }

inline double cal(Build &b1,Build&b2) {
    double dx=fabs(b1.x-b2.x);
    double dy=b2.h-b1.h;
    return dy/dx;
}

int main() {
    int cas=0;
    scanf("%d",&t);
    while (t--) {
        scanf("%d",&n);
        for (int i=0;i<n;i++) {
            scanf("%lf%lf",&b[i].x,&b[i].h);
            b[i].flag=false;
            b[i].id=i;
        }
        scanf("%d",&m);
        for (int i=n;i<n+m;i++) {
            scanf("%lf",&b[i].x);
            b[i].h=0;
            b[i].flag=true;
            b[i].id=i;
        }
        n+=m;
        sort(b,b+n,cmp1);
        q[0]=b[0];
        int top=0;
        for (int i=1;i<n;i++) {
            if (!b[i].flag) {
                while (top && cal(b[i],q[top])<cal(q[top],q[top-1]))
                    top--;
                q[++top]=b[i];
            } else {
                int tmp=top;
                while (tmp && cal(b[i],q[tmp])<cal(b[i],q[tmp-1]))
                    tmp--;
                b[i].ang[0]=cal(b[i],q[tmp]);
            }
        }

        q[0]=b[n-1];
        top=0;
        for (int i=n-2;i>=0;i--) {
            if (!b[i].flag) {
                while (top && cal(b[i],q[top])<cal(q[top],q[top-1]))
                    top--;
                q[++top]=b[i];
            } else {
                int tmp=top;
                while (tmp && cal(b[i],q[tmp])<cal(b[i],q[tmp-1]))
                    tmp--;
                b[i].ang[1]=cal(b[i],q[tmp]);
            }
        }
        printf("Case #%d:\n", ++cas);
        sort(b,b+n,cmp2);
        for (int i=0;i<n;i++) {
            if (b[i].flag) {
                double ans=(PI-atan(b[i].ang[0])-atan(b[i].ang[1]))/PI*180.0;
                printf("%lf\n", ans);
            }
        }
    }
    return 0;
}