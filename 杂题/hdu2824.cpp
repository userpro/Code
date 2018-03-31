#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn=3e6+10;
int a,b;
long long phi[maxn];

void get_phi(int n)
{
    memset(phi,0,sizeof(phi));
    phi[1]=1;
    for (int i = 2; i <= n; ++i)
    {
        if (!phi[i])
        {
            for (int j = i; j <= n; j+=i)
            {
                if (!phi[j]) phi[j]=j;
                phi[j]=phi[j]/i * (i-1);
            }
        }
    }
}

int main()
{
    get_phi(maxn);
    while (scanf("%d%d",&a,&b)==2)
    {
        long long ans=0;
        for (int i = a; i <= b; ++i)
            ans+=phi[i];
        printf("%lld\n", ans);
    }
    return 0;
}