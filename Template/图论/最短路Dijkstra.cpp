#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=50;
const int inf=1<<29;
int n,m,cnt;
int mp[maxn][maxn];
bool used[maxn];
int dis[maxn];

void dijk() {
    for (int i=2;i<=n;i++) dis[i]=inf;
    dis[1]=0;
    for (int i=1;i<=n-1;i++) {
        int mn=inf,mi;
        for (int j=1;j<=n;j++) {
            if (!used[j] && mn>dis[j]) {
                mn=dis[j]; mi=j;
            }
        }
        used[mi]=1;
        for (int j=1;j<=n;j++) {
            dis[j]=min(dis[j],dis[mi]+mp[mi][j]);
        }
    }
}

int main() {
    //freopen("1.txt","r",stdin);
    while (scanf("%d%d",&n,&m)!=EOF&&(n||m)) {
        for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) mp[i][j]=inf;
        int u,v,w;
        for (int i=1;i<=m;i++) {
            scanf("%d%d%d",&u,&v,&w);
            mp[v][u]=mp[u][v]=w;
        }
        int mx=0;
        for (int i=2;i<=n-1;i++) {
            memset(used,0,sizeof(used));
            used[i]=1;
            dijk();
            mx=max(mx,dis[n]);
            used[i]=0;
        }
        if (mx==inf) puts("Inf");
        else printf("%d\n",mx);
    }
    return 0;
}