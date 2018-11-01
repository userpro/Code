#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define uint long long
int t;
uint a,b,n;

int main()
{
    scanf("%d",&t);
    for (int i = 1; i <= t; ++i)
    {
        scanf("%lld%lld%lld",&a,&b,&n);
        vector<uint> v;
        for (int j = 2; j*j <= n; ++j)
        {
            if (n%j==0)
            {
                v.push_back(j);
                while (n%j==0) n/=j;
            }
        }
        if (n>1) v.push_back(n);

        uint ans1=0,ans2=0;
        for (uint j = 1; j < (1<<v.size()); ++j)
        {
            uint bits=0,mul=1;
            for (int k = 0; k < v.size(); ++k)
            {
                if (j&(1<<k))
                {
                    bits++;
                    mul*=v[k];
                }
            }

            uint cur1=(a-1)/mul;
            uint cur2=b/mul;
            if (bits&1)
            {
                ans1+=cur1;
                ans2+=cur2;
            }
            else
            {
                ans1-=cur1;
                ans2-=cur2;
            }
        }
        printf("Case #%d: %lld\n", i, b-a+1-(ans2-ans1));
    }
    return 0;
}