// codeforces816E树形DP
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=5e3+10;
int n,b;
int sz[maxn];
LL dp[maxn][maxn][2],c[maxn],d[maxn];
vector<int> G[maxn];
void dfs(int u,int fa) {
    sz[u]=1;
    dp[u][0][0]=0;
    dp[u][1][0]=c[u];
    dp[u][1][1]=c[u]-d[u];
    for (int i=0;i<G[u].size();i++) {
        int v=G[u][i];
        if (v==fa) continue;
        dfs(v,u);
        for (int j=sz[u];j>=0;j--) {
            for (int k=0;k<=sz[v];k++) {
                dp[u][j+k][0]=min(dp[u][j+k][0],dp[u][j][0]+dp[v][k][0]);
                dp[u][j+k][1]=min(dp[u][j+k][1],min(dp[u][j][1]+dp[v][k][1],dp[u][j][1]+dp[v][k][0]));
            }
        }
        sz[u]+=sz[v];
    }
}
int main() {
    while (cin>>n>>b) {
        memset(dp,0x3f,sizeof(dp));
        for (int i=1;i<=n;i++) G[i].clear();
        cin>>c[1]>>d[1];
        int x;
        for (int i=2;i<=n;i++) {
            cin>>c[i]>>d[i]>>x;
            G[x].push_back(i);
        }
        dfs(1,0);
        int ans=0;
        for (int i=n;i>=0;i--) {
            if (dp[1][i][0]<=b || dp[1][i][1]<=b) {
                ans=i;
                break;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
