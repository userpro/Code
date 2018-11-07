// hdu5992
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
#define lson (rt<<1)
#define rson (rt<<1|1)
#define Sqrt2(x) ((x)*(x))
const int maxn=2e5+10;
int n,k,idx; // n条数据 k维特征

struct Node
{
    int id;
    LL feature[3];
    bool operator <(const Node &u) const { return feature[idx]<u.feature[idx]; }
}_data[maxn];
typedef pair<double,Node> Pair;

priority_queue<Pair> Q;

class KDTree {
    public:
        void Build(int rt,int l,int r,int dep);
        void Query(int rt,Node p,int m,int dep); // p起始点 最近m个点

    private:
        Node data[maxn<<2];
        int flag[maxn<<2];
}kd;

void KDTree::Build(int rt,int l,int r,int dep) {
    if (l>r) return;
    flag[rt]=1;
    flag[lson]=flag[rson]=-1;
    idx=dep%2;
    int mid=(l+r)>>1;
    nth_element(_data+l,_data+mid,_data+r+1);
    data[rt]=_data[mid];
    Build(lson,l,mid-1,dep+1);
    Build(rson,mid+1,r,dep+1);
}

void KDTree::Query(int rt,Node p,int m,int dep) {
    if (flag[rt]==-1) return;
    Pair cur(0,data[rt]);
    for (int i=0;i<2;i++) cur.first+=Sqrt2(cur.second.feature[i]-p.feature[i]);
    int dim=dep%2;
    bool fg=0;
    int x=lson, y=rson;
    if (p.feature[dim]>=data[rt].feature[dim]) swap(x,y);
    if (~flag[x]) Query(x,p,m,dep+1);

    if (Q.size()<m) {
        if (p.feature[2]>=cur.second.feature[2]) {
            Q.push(cur);
        }
        fg=1;
    } else {
        if (p.feature[2]>=cur.second.feature[2] && (cur.first<Q.top().first || (cur.first==Q.top().first && cur.second.id<Q.top().second.id))) {
            Q.pop(); Q.push(cur);
        }
        if (Sqrt2(p.feature[dim]-data[rt].feature[dim])<Q.top().first)
            fg=1;
    }
    if (~flag[y]&&fg)
        Query(y,p,m,dep+1);
}

int t,m;
int main() {
    scanf("%d",&t);
    while (t--) {
        scanf("%d%d",&n,&m);
        for (int i=0;i<n;i++) {
            for (int j=0;j<3;j++) scanf("%lld",&_data[i].feature[j]);
            _data[i].id=i;
        }
        kd.Build(1,0,n-1,0);
        for (int i=0;i<m;i++) {
            Node p;
            scanf("%lld%lld%lld",&p.feature[0],&p.feature[1],&p.feature[2]);
            while (!Q.empty()) Q.pop();
            kd.Query(1,p,1,0);
            while (!Q.empty()) {
                Node tmp=Q.top().second;
                Q.pop();
                printf("%lld %lld %lld\n", tmp.feature[0],tmp.feature[1],tmp.feature[2]);
            }
        }
    }
    return 0;
}


