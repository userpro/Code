#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
#define LL long long
#define MAXN 200010

LL n,w,l;
struct Node
{
    LL h,r;
} A[MAXN];

bool check(LL mid)
{
    LL tmpl=l;
    LL tmpw=w;
    for (LL i=0;i<n;i++)
    {
        LL a=(tmpl-A[i].h)/A[i].r;
        if ((tmpl-A[i].h)%A[i].r!=0)
            a++;

        LL b=(tmpw-A[i].h)/A[i].r;
        if ((tmpw-A[i].h)%A[i].r!=0)
            b++;

        if (mid>=a)
        {
            if (mid>=b)
                return 1;
            else
                tmpw-=A[i].h+A[i].r*mid;
        }
    }
    if (tmpw<=0)
        return 1;
    return 0;
}

int main()
{
    while (scanf("%lld%lld%lld",&n,&w,&l)!=EOF)
    {
        for (LL i=0;i<n;i++)
            scanf("%lld%lld",&A[i].h,&A[i].r);

        LL st=0,en=1e18;
        while (st<en)
        {
            LL mid=(st+en)>>1;
            if (check(mid))
                en=mid;
            else
                st=mid+1;
        }
        
        if (check(st))
            printf("%lld\n", st);
        else if (check(st-1))
            printf("%lld\n", st-1);
    }
    return 0; 
}