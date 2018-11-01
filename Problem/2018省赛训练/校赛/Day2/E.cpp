#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>

using namespace std;
#define INF (1<<25)
#define LL unsigned long long
#define MAXN 100010
int n,k,m;
int f[MAXN],val[MAXN];
map<string,int> mp;
char buf[MAXN];

int findd(int x)
{
    if (f[x]==-1)
        return x;
    return f[x]=findd(f[x]);
}

int main()
{
    while (scanf("%d%d%d",&n,&k,&m)!=EOF)
    {
        mp.clear();
        memset(val,0,sizeof(val));
        memset(f,-1,sizeof(f));
        string ts;
        for (int i=1;i<=n;i++)
        {
            scanf("%s",buf);
            ts=buf;
            mp[ts]=i;
        }
        for (int i=1;i<=n;i++)
            scanf("%d",&val[i]);

        int a,b,c;
        for (int i=1;i<=k;i++)
        {
            scanf("%d",&c);
            scanf("%d",&a);
            int fa=findd(a);
            val[fa]=min(val[fa],val[a]);
            for (int j=1;j<c;j++)
            {
                scanf("%d",&b);
                int fb=findd(b);
                if (fa!=fb)
                {
                    f[fb]=fa;
                    val[fa]=min(val[fa],val[fb]);
                }
            }
        }

        LL ans=0;
        for (int i=1;i<=m;i++)
        {
            scanf("%s",buf);
            ts=buf;
            ans+=val[findd(mp[ts])];
        }
        printf("%lld\n", ans);
    }
    return 0;
}