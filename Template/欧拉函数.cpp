#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn=3e6+5;

int get_phi1(int n)
{
    int m=sqrt(n+0.5);
    int ans=n;
    for (int i = 2; i <= m; ++i)
    {
        if (n%i==0)
        {
            ans=ans/i * (i-1);
            while (n%i==0) n/=i;
        }
    }
    if (n>1) ans=ans/n*(n-1);
    return ans;
}

long long phi[maxn];
void get_phi2(int n)
{
    memset(phi,0,sizeof(phi));
    phi[1]=1;
    for (int i = 2; i <= n; ++i)
        if (!phi[i])
        {
            for (int j = i; j <= n; j+=i)
            {
                if (!phi[j]) phi[j]=j;
                phi[j]=phi[j]/i * (i-1);
            }
        }
}

int main()
{
    printf("%d\n", get_phi1(7));
    get_phi2(1000);
    for (int i = 0; i < 20; ++i)
        printf("%lld ", phi[i]);
    printf("\n");
    return 0;
}