#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define LL long long
int t;
LL m,n;

LL solve(LL n, LL m)
{
    vector<LL> v;
    for (LL i = 2; i*i <= m; ++i)
    {
        if (m%i==0)
        {
            v.push_back(i);
            while (m%i==0) m/=i;
        }
    }
    if (m>1) v.push_back(m);

    LL res=0;
    for (int i = 1; i < (1<<v.size()); ++i)
    {
        LL bits=0,mul=1;
        for (int j = 0; j < v.size(); ++j)
        {
            if (i&(1<<j))
            {
                bits++;
                mul*=v[j];
            }
        }

        LL cur=n/mul;
        if (bits&1)
            res+=cur;
        else
            res-=cur;
    }
    return n-res;
}

int main()
{
    scanf("%d",&t);
    while (t--)
    {
        scanf("%lld%lld",&m,&n);
        LL ans=0;
        for (LL i = 1; i <= m; ++i)
            ans+=solve(n, i);
        printf("%lld\n", ans);
    }
    return 0;
}