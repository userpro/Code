// loj10130 点的距离
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,q,cnt;
int head[maxn<<1],dep[maxn],f[maxn][25];
struct Node
{
    int to,next;
}edge[maxn<<1];

int read()
{
    int f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return x*f;
}

void print(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9) print(x/10);
    putchar(x%10+'0');
}



void _init() {
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(dep,0,sizeof(dep));
    memset(f,0,sizeof(f));
}

void add(int u,int v) {
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void dfs(int u,int fa) {
    dep[u]=dep[fa]+1;
    for (int i=0;i<24;i++)
        f[u][i+1]=f[f[u][i]][i];
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (v==fa) continue;
        f[v][0]=u;
        dfs(v,u);
    }
}

int query(int x,int y) {
    if (dep[x]<dep[y]) swap(x,y);
    for (int i=24;i>=0;i--) {
        if (dep[f[x][i]]>=dep[y]) x=f[x][i];
        if (x==y) return x;
    }
    for (int i=24;i>=0;i--) {
        if (f[x][i]!=f[y][i]) {
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}

int main() {
    _init();
    n=read();
    int u,v;
    for (int i=1;i<n;i++) {
        u=read(), v=read();
        add(u,v); add(v,u);
    }
    dfs(1,0);
    q=read();
    for (int i=1;i<=q;i++) {
        u=read(), v=read();
        print(dep[u]+dep[v]-2*dep[query(u,v)]);
    }
    return 0;
}