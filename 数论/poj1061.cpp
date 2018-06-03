#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

LL extend_Euclid(LL a, LL b, LL &x, LL &y)
{
    if(b==0)
    {
        x = 1;
        y = 0;
        return a;
    }
    LL r = extend_Euclid(b, a%b, y, x);
    y -= a/b*x;
    return r;
}

LL x,y,m,n,l;
int main()
{
    while (scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&l)!=EOF)
    {
        LL xx,yy,c,a,b;
        if (m<n)
            swap(m,n), swap(x,y);
        a=m-n; b=l;
        c=y-x;
        LL d=extend_Euclid(a,b,xx,yy);
        if (c%d) printf("Impossible\n");
        else
            printf("%lld\n", ((xx*c/d)%(b/d)+b/d)%(b/d));
    }
    return 0;
}