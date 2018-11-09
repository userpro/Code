// bzoj1051 缩点后判断出度为0的点
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e4+10;
const int maxm=5e4+10;
int n,m,cnt,tot,top,col;
int head[maxn],color[maxn],st[maxn],dfn[maxn],low[maxn];
int num[maxn],out[maxn];
struct Edge
{
    int to,next;
}edge[maxm<<1];

void _init() {
    memset(head,-1,sizeof(head));
    memset(num,0,sizeof(num));
    memset(out,0,sizeof(out));
    cnt=tot=top=col=0;
}

void add(int u,int v) {
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void tarjan(int u) {
    dfn[u]=low[u]=++tot;
    st[++top]=u;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        } else if (!color[v]) {
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (dfn[u]==low[u]) {
        color[u]=++col;
        num[col]++;
        while (st[top]!=u) {
            num[col]++;
            color[st[top]]=col;
            top--;
        }
        top--;
    }
}

int main() {
    _init();
    scanf("%d%d",&n,&m);
    int u,v;
    for (int i=1;i<=m;i++) {
        scanf("%d%d",&u,&v);
        if (u==v) continue;
        add(u,v);
    }
    for (int i=1;i<=n;i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i=1;i<=n;i++) {
        for (int j=head[i];j!=-1;j=edge[j].next) {
            int v=edge[j].to;
            if (color[i]!=color[v]) out[color[i]]++;
        }
    }
    int ans=0,tmp=0;
    for (int i=1;i<=col;i++) if (out[i]==0) {
        ans=num[i];
        tmp++;
    }
    printf("%d\n", tmp==1?ans:0);
    return 0;
}