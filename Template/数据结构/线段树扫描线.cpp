// poj2482 线段树 扫描线 英文情书
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e6+10;
LL n,w,h;
struct Node {
    LL x,y1,y2,k;
    bool operator <(const Node &t) const { return x==t.x?k<t.k:x<t.x; }
}node[maxn<<1];
LL yy[maxn<<1];
struct SegNode
{
    LL sum,add;
}tree[maxn<<2];

void update(int k,int l,int r,int x,int y,int val) {
    if (x>r||y<l) return;
    if (x<=l&&y>=r) {
        tree[k].add+=val;
        tree[k].sum+=val;
        return;
    }
    int mid=(l+r)>>1;
    update(k<<1,l,mid,x,y,val);
    update(k<<1|1,mid+1,r,x,y,val);
    tree[k].sum=max(tree[k<<1].sum,tree[k<<1|1].sum)+tree[k].add;
}

int main() {
    while (scanf("%lld%lld%lld",&n,&w,&h)!=EOF) {
        memset(tree,0,sizeof(tree));
        LL cnt=0;
        LL x,y,k;
        for (int i=1;i<=n;i++) {
            scanf("%lld%lld%lld",&x,&y,&k);
            yy[++cnt]=y;
            node[cnt].x=x; node[cnt].y1=y; node[cnt].y2=y+h;
            node[cnt].k=k;
            yy[++cnt]=y+h;
            node[cnt].x=x+w; node[cnt].y1=y; node[cnt].y2=y+h;
            node[cnt].k=-k;
        }
        sort(node+1,node+1+cnt);
        sort(yy+1,yy+1+cnt);
        LL num=unique(yy+1,yy+1+cnt)-(yy+1);
        LL ans=0;
        for (int i=1;i<=cnt;i++) {
            LL l=lower_bound(yy+1,yy+num+1,node[i].y1)-yy;
            LL r=lower_bound(yy+1,yy+num+1,node[i].y2)-yy-1;
            // printf("%lld\n", node[i].k);
            // printf("1 %lld  %lld %lld   %lld\n", num,l,r,node[i].k);
            if (l<=r) update(1,1,num,l,r,node[i].k);
            ans=max(ans,tree[1].sum);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
