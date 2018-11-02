// JSOI 2008 最小生成树计数
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=110;
const int maxm=1010;
const int mod=31011;
int n,m;
struct Edge
{
    int u,v,w;
    bool operator <(const Edge&e) const { return w<e.w; }
}e[maxm];
struct Node
{
    int l,r,k;
}a[maxm];
int tot,sum;
int f[maxn];

int findd(int x) {
    if (f[x]==-1) return x;
    return findd(f[x]);
}

void _init() {
    tot=0;
    memset(f,-1,sizeof(f));
}

void dfs(int x,int now,int k) {
    if (a[x].r+1==now) {
        if (k==a[x].k) sum++;
        return;
    }
    int fx=findd(e[now].u),fy=findd(e[now].v);
    if (fx!=fy) {
        f[fx]=fy;
        dfs(x,now+1,k+1);
        f[fx]=f[fy]=-1;
    }
    dfs(x,now+1,k);
}

int main() {
    _init();
    scanf("%d%d",&n,&m);
    int u,v,w;
    for (int i=1;i<=m;i++) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    int num=0;
    sort(e+1,e+1+m);
    for (int i=1;i<=m;i++) {
        if (e[i].w!=e[i-1].w) a[++tot].l=i, a[tot-1].r=i-1;
        int fx=findd(e[i].u),fy=findd(e[i].v);
        if (fx!=fy) {
            f[fx]=fy; a[tot].k++;
            num++;
        }
    }
    a[tot].r=m;
    if (num!=n-1) {
        printf("0\n");
        return 0;
    }

    int ans=1;
    memset(f,-1,sizeof(f));
    for (int i=1;i<=tot;i++) {
        sum=0;
        dfs(i,a[i].l,0);
        ans=(ans*sum)%mod;
        for (int j=a[i].l;j<=a[i].r;j++) {
            int fx=findd(e[j].u),fy=findd(e[j].v);
            if (fx!=fy) f[fx]=fy;
        }
    }
    printf("%d\n", ans);
    return 0;
}
