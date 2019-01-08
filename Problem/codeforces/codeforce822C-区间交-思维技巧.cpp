// codeforce822C-区间交-思维技巧
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<int,LL> pii;
typedef pair<int,pii> ppii;
const LL inf=1e12;
const int maxn=2e5+10;
int n,x;
vector<ppii> v;
LL sum[maxn];
int main() {
    while (~scanf("%d%d",&n,&x)) {
        memset(sum,0x7f,sizeof(sum));
        v.clear();
        int l,r,cost;
        for (int i=1;i<=n;i++) {
            scanf("%d%d%d",&l,&r,&cost);
            v.emplace_back(l,make_pair(-r,cost));
            v.emplace_back(r,make_pair(l,cost));
        }
        sort(v.begin(), v.end());
        LL ans=inf;
        for (int i=0;i<v.size();i++) {
            int l=v[i].first, r=v[i].second.first;
            LL cost=v[i].second.second;
            if (r<0) {
                r=-r;
                if (r-l+1<x) ans=min(ans,sum[x-(r-l+1)]+cost);
            } else {
                swap(l,r);
                sum[r-l+1]=min(sum[r-l+1],cost);
            }
        }
        printf("%I64d\n", ans==inf?-1:ans);
    }
    return 0;
}
