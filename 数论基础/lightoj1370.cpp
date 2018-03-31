/*
素数打表
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define maxn 1000010
bool vis[maxn];
int prime[maxn];
int t,n,cnt=0;

void getprime(int n)
{
    memset(vis,0,sizeof(vis));
    memset(prime,0,sizeof(prime));
    for (int i = 2; i < n; ++i)
    {
        if (!vis[i])
            prime[cnt++]=i;
        for (int j = 0; j < cnt && i*prime[j] <= n; ++j)
        {
            vis[i*prime[j]]=1;
            if (i%prime[j]==0)
                break;
        }
    }
}

int main()
{
    int num=0;
    getprime(maxn);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        int u;
        long long ans=0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d",&u);
            int st=0,ed=cnt-1;
            while (st<ed)
            {
                int mid=(st+ed)>>1;
                if (prime[mid]<=u)
                    st=mid+1;
                else
                    ed=mid;
            }
            ans+=prime[st];
        }
        printf("Case %d: %lld Xukha\n", ++num,ans);
    }
    return 0;
}
