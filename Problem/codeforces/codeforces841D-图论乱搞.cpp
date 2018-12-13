// codeforces841D-图论乱搞
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
const int maxn=3e5+10;
int n,m;
int d[maxn];
vector<pii> G[maxn];
vector<int> ans;
bool vis[maxn];
int dfs(int u) {
    vis[u]=1;
    for (int i=0;i<G[u].size();i++) {
        int v=G[u][i].first;
        if (vis[v]) continue;
        if (dfs(v)) {
            ans.push_back(G[u][i].second);
            d[v]=0;
            d[u]^=1;
        }
    }
    return d[u];
}
int main() {
    while (~scanf("%d%d",&n,&m)) {
        memset(vis,0,sizeof(vis));
        ans.clear();
        int sum=0,rt=-1;
        for (int i=1;i<=n;i++) {
            scanf("%d",&d[i]);
            if (d[i]==-1) rt=i;
            sum+=(d[i]==1);
            G[i].clear();
        }
        int u,v;
        for (int i=1;i<=m;i++) {
            scanf("%d%d",&u,&v);
            G[u].push_back(make_pair(v,i));
            G[v].push_back(make_pair(u,i));
        }
        if (sum%2 && rt==-1) {
            puts("-1");
            continue;
        }
        if (sum%2) d[rt]=1;
        else rt=1;
        for (int i=1;i<=n;i++) if (d[i]==-1) d[i]=0;
        dfs(rt);
        printf("%d\n", (int)ans.size());
        for (int i=0;i<ans.size();i++) printf("%d\n", ans[i]);
    }
    return 0;
}