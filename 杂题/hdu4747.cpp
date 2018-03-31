#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 200010
#define ll long long
#define mem(a,b) (memset(a,b,sizeof(a)))
int a[MAXN],p[MAXN],mp[MAXN];
int N;

int main()
{
    while (~scanf("%d",&N)&&N)
    {
        mem(a,0); mem(p,0); mem(mp,0);
        for (int i = 1; i <= N; ++i)
            scanf("%d",&a[i]);
        ll pre=0,ans=0,now=0;
        for (int i = 1; i <= N; ++i)
        {
            if (a[i]<=N)
            {
                pre=p[a[i]];
                p[a[i]]=i;
                for (int j = a[i]; j <= N; ++j)
                {
                    if (j)
                        mp[j]=min(mp[j-1],p[j]);
                    else
                        mp[j]=p[j];

                    if (mp[j]>pre)
                        now+=mp[j]-pre;
                    else
                        break;
                }
            }
            ans+=now;
        }
        printf("%lld\n", ans);
    }
    return 0;
}