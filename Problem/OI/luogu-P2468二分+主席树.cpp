// luogu-P2468二分+主席树
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn1=210;
const int maxn2=5e5+10;
const int maxk=1010;
int n,m,t;
int val[maxn1][maxn1][maxk],num[maxn1][maxn1][maxk],mp[maxn1][maxn1];

inline int getval(int x1,int y1,int x2,int y2,int k) {
    return val[x2][y2][k]-val[x1-1][y2][k]+val[x1-1][y1-1][k]-val[x2][y1-1][k];
}

inline int getnum(int x1,int y1,int x2,int y2,int k) {
    return num[x2][y2][k]-num[x1-1][y2][k]+num[x1-1][y1-1][k]-num[x2][y1-1][k];
}

void solve2() {
    memset(val,0,sizeof(val));
    memset(num,0,sizeof(num));
    int mx=0;
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) {
        scanf("%d",&mp[i][j]);
        mx=max(mx,mp[i][j]);
    }
    for (int k=0;k<=mx;k++)
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++) {
                val[i][j][k]=val[i-1][j][k]-val[i-1][j-1][k]+val[i][j-1][k]+(mp[i][j]>=k?mp[i][j]:0);
                num[i][j][k]=num[i-1][j][k]-num[i-1][j-1][k]+num[i][j-1][k]+(mp[i][j]>=k?1:0);
            }

    int x1,y1,x2,y2,h;
    while (t--) {
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&h);
        if (getval(x1,y1,x2,y2,0)<h) {
            puts("Poor QLW");
            continue;
        }
        int l=0,r=mx+1,ans=-1;
        while (l<r) {
            int mid=(l+r)>>1;
            if (getval(x1,y1,x2,y2,mid)>=h) l=mid+1,ans=mid;
            else r=mid;
        }
        if (ans==-1) {
            puts("Poor QLW");
            continue;
        }
        printf("%d\n", getnum(x1,y1,x2,y2,ans)-(getval(x1,y1,x2,y2,ans)-h)/ans);
    }
}

int rt[maxn2];
struct PersistableSegTree
{
    struct tree {
        int l,r,sz,sum;
    }tree[maxn2*20];
    int cnt;
    inline void init() { cnt=0; }
    inline void update(int &o,int pre,int l,int r,int v) {
        o=++cnt; tree[o]=tree[pre];
        tree[o].sz++; tree[o].sum+=v;
        if (l==r) return;
        int mid=(l+r)>>1;
        if (v<=mid) update(tree[o].l,tree[pre].l,l,mid,v);
        else update(tree[o].r,tree[pre].r,mid+1,r,v);
    }
    inline int query(int o,int pre,int l,int r,int v) {
        if (l==r) return (v+l-1)/l;
        int mid=(l+r)>>1,x=tree[tree[o].r].sum-tree[tree[pre].r].sum;
        if (v<=x) return query(tree[o].r,tree[pre].r,mid+1,r,v);
        else return tree[tree[o].r].sz-tree[tree[pre].r].sz+query(tree[o].l,tree[pre].l,l,mid,v-x);
    }
}pst;

void solve1() {
    pst.init();
    memset(rt,0,sizeof(rt));
    int tmp;
    for (int i=1;i<=m;i++) {
        scanf("%d",&tmp);
        pst.update(rt[i],rt[i-1],1,maxk,tmp);
    }

    int x1,y1,x2,y2,h;
    while (t--) {
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&h);
        if (pst.tree[rt[y2]].sum-pst.tree[rt[y1-1]].sum<h) {
            puts("Poor QLW");
            continue;
        }
        printf("%d\n", pst.query(rt[y2],rt[y1-1],1,maxk,h));
    }
}

int main() {
    while (~scanf("%d%d%d",&n,&m,&t)) {
        if (n==1) solve1();
        else solve2();
    }
    return 0;
}
