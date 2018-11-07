// hdu4347 
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define lson (rt<<1)
#define rson (rt<<1|1)
#define Sqrt2(x) ((x)*(x))
const int maxn=5e4+10;
int n,k,idx; // n条数据 k维特征

struct Node
{
    int feature[5]; // 特征维度数组
    bool operator <(const Node &u) const { return feature[idx]<u.feature[idx]; }
}_data[maxn];
typedef pair<double,Node> Pair; // first 存的就是距离

priority_queue<Pair> Q; // 队列Q用于存放离p最近的m个数据

class KDTree {
    public:
        void Build(int rt,int l,int r,int dep);
        void Query(int rt,Node p,int m,int dep); // p起始点 最近m个点

    private:
        Node data[maxn<<2]; // data[]数组代表K-D树的所有节点数据
        int flag[maxn<<2];  // 用于标记某个节点是否存在, 1表示存在, -1表示不存在
}kd;

void KDTree::Build(int rt,int l,int r,int dep) {
    if (l>r) return;
    flag[rt]=1;               // 表示编号为rt的节点存在
    flag[lson]=flag[rson]=-1; // 表示编号为lson rson的节点不存在
    idx=dep%k;                // 按照编号为idx的属性进行划分
    int mid=(l+r)>>1;
    nth_element(_data+l,_data+mid,_data+r+1);
    data[rt]=_data[mid];
    Build(lson,l,mid-1,dep+1);
    Build(rson,mid+1,r,dep+1);
}


// 查询函数, 寻找离p最近的m个特征属性
void KDTree::Query(int rt,Node p,int m,int dep) {
    if (flag[rt]==-1) return;
    Pair cur(0,data[rt]);
    for (int i=0;i<k;i++) cur.first+=Sqrt2(cur.second.feature[i]-p.feature[i]); // 当前节点到p的距离
    int dim=dep%k;      // //跟建树一样, 这样能保证相同节点的dim值不变
    bool fg=0;          // 是否需要遍历右子树
    int x=lson, y=rson;
    if (p.feature[dim]>=data[rt].feature[dim]) swap(x,y); //数据p的第dim个特征值大于等于当前的数据, 则需要进入右子树
    if (~flag[x]) Query(x,p,m,dep+1); // 如果节点x存在, 则进入子树继续遍历

    // 以下是回溯过程, 维护一个优先队列
    if (Q.size()<m) {
        Q.push(cur); 
        fg=1;
    } else {
        if (cur.first<Q.top().first) { // 如果找到更小的距离, 则用于替换队列Q中最大的距离的数据
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
    while (scanf("%d%d",&n,&k)!=EOF) {
        for (int i=0;i<n;i++) 
            for (int j=0;j<k;j++)
                scanf("%d",&_data[i].feature[j]);

        kd.Build(1,0,n-1,0);
        scanf("%d",&t);
        while (t--) {
            Node p;
            for (int i=0;i<k;i++)
                scanf("%d",&p.feature[i]);
            scanf("%d",&m);
            while (!Q.empty()) Q.pop();
            kd.Query(1,p,m,0);
            printf("the closest %d points are:\n", m);
            Node ans[20];
            for (int i=0;!Q.empty();i++) {
                ans[i]=Q.top().second; Q.pop();
            }
            for (int i=m-1;i>=0;i--) {
                for (int j=0;j<k;j++) {
                    if (j==0) printf("%d", ans[i].feature[j]);
                    else printf(" %d", ans[i].feature[j]);
                }
                puts("");
            }
        }
    }
    return 0;
}


