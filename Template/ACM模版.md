-   [组合数学](#组合数学)
    -   [指数型母函数](#指数型母函数)
    -   [普通母函数](#普通母函数)
    -   [错排数](#错排数)
    -   [组合数C(打表)](#组合数c打表)
    -   [组合数C](#组合数c)
-   [图论](#图论)
    -   [链式前向星+树上最大独立集](#链式前向星树上最大独立集)
    -   [点分治(树的重心)](#点分治树的重心)
    -   [树的直径](#树的直径)
    -   [倍增LCA求树上点的距离](#倍增lca求树上点的距离)
    -   [倍增LCA求树上dep的k次方](#倍增lca求树上dep的k次方)
    -   [二分匹配(匈牙利算法)](#二分匹配匈牙利算法)
    -   [二分匹配(Hopcroft-Carp)](#二分匹配hopcroft-carp)
    -   [最大流Dinic](#最大流dinic)
    -   [最大流EK](#最大流ek)
    -   [最小费用最大流EK](#最小费用最大流ek)
    -   [最小生成树(Prim)](#最小生成树prim)
    -   [最小生成树 Kruskal](#最小生成树-kruskal)
    -   [最小生成树计数](#最小生成树计数)
    -   [严格次小生成树](#严格次小生成树)
    -   [最短路Bellman](#最短路bellman)
    -   [最短路Dijkstra(队列实现)](#最短路dijkstra队列实现)
    -   [最短路Dijkstra](#最短路dijkstra)
    -   [最短路Floyd](#最短路floyd)
    -   [最短路SPFA(判负环)](#最短路spfa判负环)
    -   [次短路Dijk](#次短路dijk)
    -   [次短路SPFA](#次短路spfa)
    -   [Tarjan强连通分量](#tarjan强连通分量)
    -   [Tarjan求割点和桥](#tarjan求割点和桥)
    -   [图论汇总](#图论汇总)
-   [数据结构](#数据结构)
    -   [单调栈维护凸包](#单调栈维护凸包)
    -   [单调队列](#单调队列)
    -   [莫队算法](#莫队算法)
    -   [并查集](#并查集)
    -   [树状数组](#树状数组)
    -   [二维树状数组](#二维树状数组)
    -   [点分治](#点分治)
    -   [线段树区间乘](#线段树区间乘)
    -   [线段树区间和区间开方](#线段树区间和区间开方)
    -   [线段树扫描线](#线段树扫描线)
    -   [分块](#分块)
    -   [ST算法求RMQ问题](#st算法求rmq问题)
    -   [KDTree(二维最近符合条件点)](#kdtree二维最近符合条件点)
    -   [树链剖分+动态线段树](#树链剖分动态线段树)
    -   [字典树Trie](#字典树trie)
-   [数论](#数论)
    -   [分解质因子](#分解质因子)
    -   [容斥原理求互素数个数](#容斥原理求互素数个数)
    -   [扩展欧几里得算法](#扩展欧几里得算法)
    -   [欧拉函数](#欧拉函数)
    -   [求逆元](#求逆元)
    -   [素数打表](#素数打表)
    -   [欧拉降幂](#欧拉降幂)
    -   [Lucas](#lucas)
-   [其余](#其余)
    -   [矩阵快速幂](#矩阵快速幂)
    -   [归并排序](#归并排序)
    -   [极角排序](#极角排序)
    -   [数位DP](#数位dp)
    -   [欧拉序](#欧拉序)
    -   [DFS序](#dfs序)
    -   [背包](#背包)
    -   [蔡勒公式](#蔡勒公式)
    -   [高精度](#高精度)
    -   [Base64](#base64)
    -   [DFS子集生成](#dfs子集生成)
    -   [LCS & LIS](#lcs-lis)
    -   [读入优化](#读入优化)

组合数学
--------

### 指数型母函数

![指数型母函数性质](/Users/zdz/Downloads/Code/Template/组合数学/指数型母函数性质.jpg)

![指数型母函数应用](/Users/zdz/Downloads/Code/Template/组合数学/指数型母函数应用.jpg)

``` {.cpp}
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 100;
double c1[N], c2[N],a[N];
int val[N];
void Factorial()
{
    a[0]=1;
    a[1]=1;
    for(int i = 2; i <=20; i++)
    {
        a[i]=a[i-1]*i;
    }
}
int main()
{
    int n, m, i, j, k;
    Factorial();
    while(~scanf("%d%d", &n, &m))
    {
        for(i = 0; i < n; ++ i)
        {
            scanf("%d", &val[i]);
        }
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));

        for(i = 0; i <= val[0]; ++i)
        {
            c1[i] = 1.0/a[i];
        }
        for(i = 1; i < n; i++)
        {
            for(j = 0; j <= m; ++j)
                for(k = 0; k + j <= m && k <= val[i]; ++k)
                    c2[j + k] += c1[j]/a[k];
                
            for(j = 0; j <= m; ++j)
            {
                c1[j] = c2[j];
                c2[j] = 0;
            }
        }
        printf("%.0lf\n", c1[m]*a[m]);
    }
    return 0;
}
```

### 普通母函数

``` {.cpp}
#include <iostream>  
using namespace std;
const int max = 1000;   
// sup是保存多项式的数组，sup[n]中的值代表xn的系数
// temp是临时多项式，保存相乘的临时中间情况  
int sup[max], temp[max];   
/*
程序始终只计算两个多项式之间的乘积，多个多项式的情况
先计算前两个的乘积，将结果作为第一个多项式，再与第三个相乘
依次类推，sup始终存放当前运算后的结果然后作为被乘多项式，
*/  
int main()  
{   
    int target;   //  目标重量， 比如上面的例子里就是10，要<max的值
    int i, j, k;  
   
    while(cin >> target)  
    {  
        for(i=0; i<=target; ++i)     
        {  
            sup[i] = 1;   
//初始化第一个多项式，也就是用1g砝码的多项式,
//注意如果题目没给1g的砝码那么就不能++i，而要加上砝码的质量
            temp[i] = 0;  
//将临时区清空，无论第一个多项式质量是几都要全部置零
        }  
        for(i=2; i<=target; ++i)   
// 生成后续的第i个多项式，此题中是2g，i从2开始。
//如果砝码的值不是规律增长，i可能需要取决于输入
        {  
   
            for(j=0; j<=target; ++j)   
// 遍历当前结果多项式的每一项（当前结果的第j项）与第i个多项式相乘，
                for(k=0; k+j<=target; k+=i) 
// 遍历第i个多项式的每一项，此处构造用小砝码组成大砝码的多项式
                {  
                    temp[j+k] += sup[j];  
//幂运算，注意理解
                }  
            for(j=0; j<=target; ++j)    
// 将临时的结果覆盖当前结果，同时把临时结果置零，为下次做准备
            {  
                sup[j] = temp[j];  
                temp[j] = 0;  
            }  
        }  
        cout << sup[target] << endl;  //输出结果
    }  
    return 0;  
}  
```

### 错排数

``` {.cpp}
#define LL long long
#define MOD 1000000007
#define MAXN 10010
LL D[MAXN];

void preD()
{
    D[0]=1; D[1]=0;
    for (int i=2;i<=MAXN;i++)
        D[i]=((i-1)*(D[i-1]+D[i-2])+MOD)%MOD;
}
```

### 组合数C(打表)

``` {.cpp}
#include <cstdio>
typedef long long LL;
LL C[40][40];
void _init()
{
    C[0][0]=C[1][0]=C[1][1]=1;
    for (int i=2;i<40;i++)
    {
        C[i][0]=1;
        for (int j=1;j<i;j++)
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        C[i][i]=1;
    }
}
```

### 组合数C

``` {.cpp}
long long C(int n,int m,int mod) {
    if (m*2>n) m=n-m;
    long long ret=1;
    for (int i=1;i<=m;i++) {
        ret*=(n-i+1)%mod;
        while (ret%i!=0) ret+=mod;
        ret/=i;
        ret%=mod;
    }
    return ret;
}
```

图论
----

### 链式前向星+树上最大独立集

``` {.cpp}
// 求树上独立集的最大异或和
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+100;
int t,n;
int dp[maxn][2],f[maxn];
int head[maxn];
int cnt;
struct E
{
    int w,to,next;
}edge[maxn];

void _init() {
    memset(head,-1,sizeof(head));
    cnt=0;
}

void adde(int u,int v,int w) {
    edge[cnt].w=w;
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

int solve(int u,int fa) {
    dp[u][0]=f[u];
    dp[u][1]=0;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (v==fa) continue;
        solve(v,u);
        dp[u][0]^=dp[v][1];
        dp[u][1]=max(dp[u][1]^dp[v][0],dp[u][1]^dp[v][1]);
    }
    return max(dp[u][0],dp[u][1]);
}

int main() {
    //freopen("1.txt","r",stdin);
    scanf("%d",&t);
    while (t--) {
        _init();
        scanf("%d",&n);
        int u,v;
        int t=0;
        for (int i=1;i<=n;i++) {
            scanf("%d",&f[i]);
            t^=f[i];
        }
        for (int i=1;i<n;i++) {
            scanf("%d%d",&u,&v);
            adde(u,v,f[u]);
        }
        int q=solve(1,0);
        t^=q;
        printf("%c\n",t==q?'D':t>q?'Q':'T');
    }
    return 0;
}
```

### 点分治(树的重心)

``` {.cpp}
// poj1741
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf=1<<29;
const int maxn=1e4+10;
int n,k;
int head[maxn],size[maxn],dis[maxn],mxson[maxn];
bool vis[maxn];
struct Edge
{
    int to,w,next;
}edge[maxn<<1];
int cnt,tot,root,sum; // sum 子树大小

void _init() {
    cnt=tot=root=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
}

inline void add(int u,int v,int w) {
    edge[cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

// 求树的重心
inline void dfs_root(int u,int f) {
    mxson[u]=0;
    size[u]=1;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (vis[v]||v==f) continue;
        dfs_root(v,u);
        size[u]+=size[v];
        mxson[u]=max(mxson[u],size[v]);
    }
    mxson[u]=max(mxson[u],sum-size[u]); // sum-size[u] !!!
    if (mxson[u]<mxson[0]) {
        mxson[0]=mxson[u];
        root=u;
    }
}

inline void dfs_dis(int u,int f,int dist) {
    dis[++tot]=dist;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (vis[v]||v==f) continue;
        dfs_dis(v,u,dist+edge[i].w);
    }
}

inline int calc(int u,int dist) {
    tot=0;
    dfs_dis(u,u,dist);
    sort(dis+1,dis+1+tot);
    int res=0;
    int i=1,j=tot;
    for (int i=1;i<j;i++) {
        while (dis[i]+dis[j]>k&&i<j) j--;
        res+=(j-i);
    }
    return res;
}

inline int dfs(int u) {
    mxson[0]=inf;
    dfs_root(u,u);
    vis[root]=1;
    int res=calc(root,0);
    for (int i=head[root];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (vis[v]) continue;
        res-=calc(v,edge[i].w);
        sum=size[v];
        res+=dfs(v);
    }
    return res;
}

int main() {
    while (scanf("%d%d",&n,&k)!=EOF && (n||k)) {
        _init();
        int u,v,w;
        for (int i=1;i<n;i++) {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w); add(v,u,w);
        }
        sum=n;
        printf("%d\n", dfs(1));
    }
    return 0;
}
```

### 树的直径

``` {.cpp}
// bzoj 1912 树的直径
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
int n,k;
// s1 最长链  s2 次长链  直径=max{s1+s2}
int head[maxn],s1[maxn],s2[maxn]; 
struct Edge
{
    int v,w,nx;
}edge[maxn<<1];
int cnt,mx,dir;

void _init() {
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(s1,-1,sizeof(s1));
    memset(s2,-1,sizeof(s2));
}

inline void add(int u,int v) {
    edge[cnt].v=v;
    edge[cnt].w=1;
    edge[cnt].nx=head[u];
    head[u]=cnt++;
}

int dfs(int u,int fa) {
    int mx1=0,mx2=0;
    for (int i=head[u];i!=-1;i=edge[i].nx) {
        int v=edge[i].v;
        if (v==fa) continue;
        int t=dfs(v,u)+edge[i].w;
        if (mx1<t) mx2=mx1,mx1=t,s2[u]=s1[u],s1[u]=i;
        else if (mx2<t) s2[u]=i,mx2=t;
    }
    if (mx1+mx2>mx) mx=mx1+mx2, dir=u;
    return mx1;
}

int main() {
    _init();
    scanf("%d%d",&n,&k);
    int u,v;
    for (int i=1;i<n;i++) {
        scanf("%d%d",&u,&v);
        add(u,v); add(v,u);
    }
    int ans=0;
    dfs(1,0);
    ans=(n-1)*2-mx+1;
    if (k==2) {
        mx=0;
        for (int i=s1[dir];i!=-1;i=s1[edge[i].v]) edge[i].w=edge[i^1].w=-1;
        for (int i=s2[dir];i!=-1;i=s1[edge[i].v]) edge[i].w=edge[i^1].w=-1;
        dfs(1,0);
        ans=ans-mx+1;
    }
    printf("%d\n", ans);
    return 0;
}
```

### 倍增LCA求树上点的距离

``` {.cpp}
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
```

### 倍增LCA求树上dep的k次方

``` {.cpp}
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
```

### 二分匹配(匈牙利算法)

``` {.cpp}
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn=210;
int m,n;
int uN,vN;
int G[maxn][maxn];
int linker[maxn];
bool vis[maxn];

bool dfs(int u)
{
    for (int v = 1; v <= vN; ++v)
    {
        if (G[u][v]&&!vis[v])
        {
            vis[v]=1;
            if (linker[v]==-1 || dfs(linker[v]))
            {
                linker[v]=u;
                return true;
            }
        }
    }
    return false;
}

int hungray()
{
    int res=0;
    memset(linker,-1,sizeof(linker));
    for (int u = 1; u <= uN; ++u)
    {
        memset(vis,0,sizeof(vis));
        if (dfs(u)) res++;
    }
    return res;
}
```

### 二分匹配(Hopcroft-Carp)

``` {.cpp}
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
const int INF=1<<29;
const int maxn=1010;
int k,m,n;
int uN,vN;
vector<int> G[maxn];
int mx[maxn],my[maxn];
int dx[maxn],dy[maxn];
int dis;
bool vis[maxn];

bool SearchP()
{
    queue<int> Q;
    dis=INF;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for (int i = 1; i <= uN; ++i) // 顶点编号从1开始
    {
        if (mx[i]==-1)
        {
            Q.push(i);
            dx[i]=0;
        }
    }
    while (!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        if (dx[u]>dis) break;
        int sz=G[u].size();
        for (int i = 0; i < sz; ++i)
        {
            int v=G[u][i];
            if (dy[v]==-1)
            {
                dy[v]=dx[u]+1;
                if (my[v]==-1)
                    dis=dy[v];
                else {
                    dx[my[v]]=dy[v]+1;
                    Q.push(my[v]);
                }
            }
        }
    }
    return dis!=INF;
}

bool dfs(int u)
{
    int sz=G[u].size();
    for (int i = 0; i < sz; ++i)
    {
        int v=G[u][i];
        if (!vis[v] && dy[v]==dx[u]+1)
        {
            vis[v]=1;
            if (my[v]!=-1 && dy[v]==dis) continue;
            if (my[v]==-1 || dfs(my[v]))
            {
                my[v]=u;
                mx[u]=v;
                return true;
            }
        }
    }
    return false;
}

int MaxMatch()
{
    int ans=0;
    memset(mx,-1,sizeof(mx));
    memset(my,-1,sizeof(my));
    while (SearchP())
    {
        memset(vis,0,sizeof(vis));
        for (int i = 1; i <= uN; ++i) // 顶点编号从1开始
        {
            if (mx[i]==-1 && dfs(i))
                ans++;
        }
    }
    return ans;
}
```

### 最大流Dinic

``` {.cpp}
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;
#define INF 1<<29
#define MAXN 100000

struct Edge
{
    int from, to, cap, flow;
    Edge(int f, int t, int c, int fw):from(f),to(t),cap(c),flow(fw) {}
};

struct Dinic
{
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];

    void init()
    {
        for (int i = 0; i < n; ++i) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap)
    {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!Q.empty())
        {
            int x = Q.front(); Q.pop();
            for (int i = 0; i < G[x].size(); ++i)
            {
                Edge &e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a)
    {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int &i = cur[x]; i < G[x].size(); ++i)
        {
            Edge &e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0)
            {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int Maxflow(int s, int t)
    {
        this->s = s; this->t = t;
        int flow = 0;
        while (BFS())
        {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
};
```

### 最大流EK

``` {.cpp}
#include <queue>
#include <vector>
#include <cstdio>

using namespace std;
#define MAXN 10000
#define INF 1<<29

struct Edge
{
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f):from(u),to(v),cap(c),flow(f) {}
};

struct EdmondsKarp
{
    int n, m;
    vector<Edge> edges;
    vector<int> G[MAXN];
    int a[MAXN];
    int p[MAXN];

    void init(int n)
    {
        for (int i = 0; i < n; ++i) G[i].clear();
            edges.clear();
    }

    void AddEdge(int from, int to, int cap)
    {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int Maxflow(int s, int t)
    {
        int flow = 0;
        for (;;)
        {
            memset(a, 0, sizeof(a));
            queue<int> Q;
            Q.push(s);
            a[s] = INF;
            while (!Q.empty())
            {
                int x = Q.front(); Q.pop();
                for (int i = 0; i < G[x].size(); ++i)
                {
                    Edge &e = edges[G[x][i]];
                    if (!a[e.to] && e.cap > e.flow)
                    {
                        p[e.to] = G[x][i];
                        a[e.to] = min(a[x], e.cap - e.flow);
                        Q.push(e.to);
                    }
                }
                if (a[t]) break;
            }
            if (!a[t]) break;
            for (int u = t; u != s; u = edges[p[u]].from)
            {
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
};
```

### 最小费用最大流EK

``` {.cpp}
// hdu5988 最小费用最大流 Tips: log将乘转换为加
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn=210;
const int inf=1<<29;
const double eps=1e-8;
struct Edge
{
    int from,to,cap,flow;
    double cost;
    Edge() {}
    Edge(int from,int to,int cap,int flow,double cost):from(from),to(to),cap(cap),flow(flow),cost(cost) {}
};

struct MCMF
{
    int n,m,s,t;
    vector<Edge> edges;
    vector<int> G[maxn];
    int inq[maxn];
    double d[maxn];
    int p[maxn];
    int a[maxn];

    void init(int n) {
        this->n=n;
        for (int i=0;i<n;i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from,int to,int cap,double cost) {
        edges.push_back(Edge(from,to,cap,0,cost));
        edges.push_back(Edge(to,from,0,0,-cost));
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BellmanFord(int s,int t,int &flow,double &cost) {
        for (int i=0;i<=n;i++) d[i]=inf;
        memset(inq,0,sizeof(inq));
        d[s]=0; inq[s]=1; p[s]=0; a[s]=inf;

        queue<int> Q;
        Q.push(s);
        while (!Q.empty()) {
            int u=Q.front(); Q.pop();
            inq[u]=0;
            for (int i=0;i<G[u].size();i++) {
                Edge &e=edges[G[u][i]];
                if (e.cap>e.flow && d[e.to]>d[u]+e.cost+eps) {
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=G[u][i];
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if (!inq[e.to]) { Q.push(e.to); inq[e.to]=1; }
                }
            }
        }
        if (d[t]==inf) return false;
        flow+=a[t];
        cost+=d[t]*a[t];
        int u=t;
        while (u!=s) {
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
        return true;
    }

    double Mincost(int s,int t) {
        int flow=0;
        double cost=0;
        while (BellmanFord(s,t,flow,cost));
        return cost;
    }
};

int t,n,m;
int a[maxn],b[maxn],c[maxn];
int main() {
    MCMF mc;
    scanf("%d",&t);
    while (t--) {
        scanf("%d%d",&n,&m);
        mc.init(n*2+1);
        int st=0,ed=n*2+1;
        for (int i=0;i<n;i++) {
            scanf("%d%d",&a[i],&b[i]);
            c[i]=a[i]-b[i];
        }
        int u,v,cap;
        double p;
        for (int i=0;i<m;i++) {
            scanf("%d%d%d%lf",&u,&v,&cap,&p);
            p=-log10(1-p);
            if (cap>0) mc.AddEdge(u,v,1,0);
            if (cap-1>0) mc.AddEdge(u,v,cap-1,p);
        }
        for (int i=0;i<n;i++) {
            if (c[i]>0) mc.AddEdge(st,i+1,c[i],0);
            else if (c[i]<0) mc.AddEdge(i+1,ed,-c[i],0);
        }
        double ans=mc.Mincost(st,ed);
        printf("%.2f\n", 1.0-pow(10,-ans));
    }
    return 0;
}
```

### 最小生成树(Prim)

``` {.cpp}
#include <cstdio>
#include <cstring>

#define MAXN 1000
#define INF 1<<29
bool vis[MAXN];
int lowc[MAXN],d[MAXN][MAXN];

void prim(int n)
{
    memset(vis,0,sizeof(vis));
    for (int i = 0; i < MAXN; ++i)
        lowc[i]=INF;

    for (int i = 0; i < n; ++i)
    {
        int minn=INF,k;
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j]&&minn>lowc[j])
            {
                minn=lowc[j];
                k=j;
            }
        }
        vis[k]=1;
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j]&&lowc[j]>d[k][j])
                lowc[j]=d[k][j];
        }
    }
}

int main()
{
    /* code */
    return 0;
}
```

### 最小生成树 Kruskal

``` {.cpp}
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 100*(100-1)/2+10
struct Edge
{
    int u,v,c;
};
int N;
int F[MAXN];
Edge E[MAXN];

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x]=findd(F[x]);
}

bool cmp(Edge e1,Edge e2)
{
    return e1.c<e2.c;
}

int main()
{
    while (scanf("%d",&N)==1&&N)
    {
        memset(F,-1,sizeof(F));
        int end=N*(N-1)/2;
        for (int i = 0; i < end; ++i)
            scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].c);
        sort(E,E+end,cmp);
        int ans=0;
        for (int i = 0; i < end; ++i)
        {
            int a=findd(E[i].u),b=findd(E[i].v);
            if (a!=b)
            {
                F[a]=b;
                ans+=E[i].c;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

### 最小生成树计数

``` {.cpp}
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
```

### 严格次小生成树

``` {.cpp}
// bzoj1977
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e5+10;
const int maxm=3e5+10;
int n,m,cnt;
LL ans,sum;
int fa[maxn][18],dep[maxn],head[maxn],maxx[maxn][18],minn[maxn][18];
bool used[maxn],vis[maxn];
struct Line
{
    int u,v,w;
    bool operator <(const Line&n1) const { return w<n1.w; }
}line[maxm];
struct Node
{
    int to,w,next;
}edge[maxm];

int findd(int x) { return x==fa[x][0]?x:fa[x][0]=findd(fa[x][0]); }

void add(int u,int v, int w) {
    edge[cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void kruskal() {
    for (int i=1;i<=n;i++) fa[i][0]=i;
    for (int i=1;i<=m;i++) {
        int a=findd(line[i].u),b=findd(line[i].v);
        if (a!=b) {
            fa[a][0]=b; sum+=line[i].w;
            add(line[i].u,line[i].v,line[i].w);
            add(line[i].v,line[i].u,line[i].w);
            used[i]=1;
        }
    }
}

void bfs() {
    memset(dep,0,sizeof(dep));
    memset(vis,0,sizeof(vis));
    fa[1][0]=0;
    queue<int> q;
    q.push(1);
    vis[1]=1;
    while (!q.empty()) {
        int u=q.front(); q.pop();
        for (int i=head[u];i!=-1;i=edge[i].next) {
            int v=edge[i].to;
            if (!vis[v]) {
                vis[v]=1;
                dep[v]=dep[u]+1;
                fa[v][0]=u;
                maxx[v][0]=edge[i].w;
                q.push(v);
            }
        }
    }
}

void pre_work() {
    for (int i=1;i<=17;i++)
        for (int j=1;j<=n;j++) {
            if (dep[j]>=(1<<i)) {
                fa[j][i]=fa[fa[j][i-1]][i-1];
                maxx[j][i]=max(maxx[j][i-1],maxx[fa[j][i-1]][i-1]);
                minn[j][i]=min(minn[j][i-1],minn[fa[j][i-1]][i-1]);
                if (maxx[j][i-1]>maxx[fa[j][i-1]][i-1] && maxx[fa[j][i-1]][i-1]>minn[j][i])
                    minn[j][i]=maxx[fa[j][i-1]][i-1];
                else if (maxx[j][i-1]<maxx[fa[j][i-1]][i-1] && maxx[j][i-1]>minn[j][i])
                    minn[j][i]=maxx[j][i-1];
            }
        }
}

int lca_get_value(int u,int v,int w) {
    if (dep[u]<dep[v]) swap(u,v);
    int l=u,r=v,mid=dep[u]-dep[v];
    int lca=0;
    for (int i=0; (1<<i)<=mid; i++)
        if ((1<<i)&mid) l=fa[l][i];
    if (l==r) lca=l;
    else {
        for (int i=17;i>=0;i--) {
            if (fa[l][i]!=fa[r][i]) {
                l=fa[l][i];
                r=fa[r][i];
            }
        }
        lca=fa[r][0];
    }
    l=u,r=v;
    int now=0;
    for (int i=17;i>=0;i--) {
        if (dep[l]-dep[lca]>=(1<<i)) {
            if (maxx[l][i]!=w) now=max(now,maxx[l][i]);
            else now=max(now,minn[l][i]);
            l=fa[l][i];
        }
        if (dep[r]-dep[lca]>=(1<<i)) {
            if (maxx[r][i]!=w) now=max(now,maxx[r][i]);
            else now=max(now,minn[r][i]);
            r=fa[r][i];
        }
    }
    return now;
}

void solve() {
    kruskal();
    bfs();
    pre_work();
    for (int i=1;i<=m;i++) {
        if (!used[i]) {
            LL tmp=lca_get_value(line[i].u,line[i].v,line[i].w);
            if (ans==0 && tmp!=line[i].w) ans=sum-tmp+line[i].w;
            if (tmp<line[i].w && ans>sum-tmp+line[i].w)
                ans=sum-tmp+line[i].w;
        }
    }
    printf("%lld\n", ans);
}

int main() {
    ans=0; cnt=0; sum=0;
    memset(used,0,sizeof(used));
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++) scanf("%d%d%d",&line[i].u,&line[i].v,&line[i].w);
    sort(line+1,line+1+m);
    solve();
    return 0;
}
```

### 最短路Bellman

``` {.cpp}
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
#define MAXN 2010
struct Edge
{
    int u,v,c;
    Edge(int _u,int _v,int _c):u(_u),v(_v),c(_c) {}
};
vector<Edge> E;
int N;
int F[MAXN];
char str[MAXN][10];

int dis(char s1[10],char s2[10])
{
    int l1=strlen(s1),l2=strlen(s2);
    int cnt=0,
        l=l1>l2?l1:l2;
    for (int i = 0; i < l1; ++i)
        if (s1[i]!=s2[i])
            cnt++;
    return cnt;
}

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x]=findd(F[x]);
}

bool cmp(Edge e1,Edge e2)
{
    return e1.c<e2.c;
}

int main()
{
    while (scanf("%d",&N)==1 && N)
    {
        E.clear();
        memset(F,-1,sizeof(F));
        memset(str,0,sizeof(str));
        for (int i = 0; i < N; ++i)
        {
            scanf("%s",str[i]);
            for (int j = 0; j < i; ++j)
                E.push_back(Edge(i,j,dis(str[i],str[j])));
        }
        sort(E.begin(), E.end(), cmp);

        int ans=0;
        for (int i = 0; i < E.size(); ++i)
        {
            int a=findd(E[i].u),b=findd(E[i].v);
            if (a!=b)
            {
                F[a]=b;
                ans+=E[i].c;
            }
        }
        printf("The highest possible quality is 1/%d.\n", ans);
    }
    return 0;
}
```

### 最短路Dijkstra(队列实现)

``` {.cpp}
#include <queue>
#define INF (1<<29)
#define MAX 500010

struct qnode
{
    int v, c;
    qnode(int _v=0, int _c=0):v(_v), c(_c) {}
    bool operator <(const qnode &r) const
    {
        return c > r.c;
    }
};
struct Edge
{
    int v, cost;
    Edge(int _v=0, int _cost=0):v(_v), cost(_cost) {}
};
vector<Edge> E[MAX]; // 记得初始化
bool vis[MAX],dis[MAX];

// n个顶点 1~n
void dijk(int start, int n)
{
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= n; ++i) dis[i] = INF;
    priority_queue<qnode> que;
    while (!que.empty()) que.pop();
    dis[start] = 0;
    que.push(qnode(start, 0));
    qnode tmp;
    while (!que.empty())
    {
        tmp = que.top();
        que.pop();
        int u = tmp.v;
        if (vis[u]) continue;
        vis[u] = 1;
        for (i = 0; i < E[u].size(); ++i)
        {
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if (!vis[v] && dis[v] > dis[u] + cost)
            {
                dis[v] = dis[u] + cost;
                que.push(qnode(v, dis[v]));
            }
        }
    }
}

void add_edge(int u, int v, int w)
{
    E[u].push_back(Edge(v, w));
}
```

### 最短路Dijkstra

``` {.cpp}
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=50;
const int inf=1<<29;
int n,m,cnt;
int mp[maxn][maxn];
bool used[maxn];
int dis[maxn];

void dijk() {
    for (int i=2;i<=n;i++) dis[i]=inf;
    dis[1]=0;
    for (int i=1;i<=n-1;i++) {
        int mn=inf,mi;
        for (int j=1;j<=n;j++) {
            if (!used[j] && mn>dis[j]) {
                mn=dis[j]; mi=j;
            }
        }
        used[mi]=1;
        for (int j=1;j<=n;j++) {
            dis[j]=min(dis[j],dis[mi]+mp[mi][j]);
        }
    }
}

int main() {
    //freopen("1.txt","r",stdin);
    while (scanf("%d%d",&n,&m)!=EOF&&(n||m)) {
        for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) mp[i][j]=inf;
        int u,v,w;
        for (int i=1;i<=m;i++) {
            scanf("%d%d%d",&u,&v,&w);
            mp[v][u]=mp[u][v]=w;
        }
        int mx=0;
        for (int i=2;i<=n-1;i++) {
            memset(used,0,sizeof(used));
            used[i]=1;
            dijk();
            mx=max(mx,dis[n]);
            used[i]=0;
        }
        if (mx==inf) puts("Inf");
        else printf("%d\n",mx);
    }
    return 0;
}
```

### 最短路Floyd

``` {.cpp}
#include <cstdio>
#include <cstring>

#define INF 1<<20
#define MAX_N 110
bool W[MAX_N][MAX_N];
int D[MAX_N];
int N, M, i, j, k, l;

int main()
{
    int N, M;
    while (scanf("%d%d", &N, &M) > 1 && N)
    {
        memset(D, 0, sizeof(D));
        memset(W, 0, sizeof(W));
        for (i = 1; i <= M; ++i)
        {
            scanf("%d%d", &j, &k);
            W[j][k] = 1;
        }

        // floyd
        for (i = 1; i <= N; ++i)
            for (j = 1; j <= N; ++j)
                for (k = 1; k <= N; ++k)
                    if (W[j][i] && W[i][k]) // 传递闭包
                        W[j][k] = 1;

        for (i = 1; i <= N; ++i)
            for (j = 1; j <= N; ++j)
            {
                D[i] += W[i][j];
                D[j] += W[i][j];
            }

        l = 0;
        for (i = 1; i <= N; ++i)
            if (D[i] == N - 1)
                l++;

        printf("%d\n", l);
    }
    return 0;
}
```

### 最短路SPFA(判负环)

``` {.cpp}
#include <vector>
#include <cstring>
const int inf=1<<29;
const int maxn=110;

struct Edge
{
    int v,w,nx;
}edge[maxn<<1];
int cnt;
int head[maxn]
bool vis[maxn];
int dis[maxn],num[maxn];

void _init() {
    cnt=0;
    memset(head,-1,sizeof(head));
}

void add(int u,int v,int w) {
    edge[cnt].v = v; edge[cnt].w = w;
    edge[cnt++].nx = head[u];
    edge[cnt].v = u; edge[cnt].w = w;
    edge[cnt++].nx = head[v];
}

// n个顶点 1~n
// 返回bool 是否存在负环
bool spfa(int start, int n) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) dis[i] = inf;
    dis[start] = 0;
    vis[start] = 1;
    queue<int> que;
    que.push(start);
    while (!que.empty()) {
        int u = que.front(); que.pop();
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = edge[i].nx) {
            int v = edge[i].v;
            cnt[v] = cnt[u] + 1;
            if (cnt[v] > n) return false; // 存在负环
            if (dis[v] > dis[u] + edge[i].w) {
                dis[v] = dis[u] + edge[i].w;
                if (!vis[v]) {
                    vis[v] = 1;
                    que.push(v);
                }
            }
        }
    }
    return true;
}
```

### 次短路Dijk

``` {.cpp}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=55;
const int inf=1<<30;
struct Edge{
    int v,w;
};
vector<Edge>vet[MAXN];
struct Node{
    int v,dist;
    int mark;//标记，1为最短路，2为次短路；
    bool operator < (const Node &p) const {
        if(p.dist!=dist)
            return p.dist<dist;

        return p.v<v;//这儿如果不按顶点的大小排序，就wa了。
    }
};
int n,m,s,e;
int dist[MAXN][3];
int dp[MAXN][3];
bool visited[MAXN][3];
//dp[i][1]表示到达点i最短的路有多少条，dp[i][2]表示次短的条数 
//dist[i][1]表示到达点i最短路的长度,dist[i][2]表示次短路的长度
/*
    用v去松驰u时有四种情况 (设当前dist[v][cas])
    情况1：dist[v][cas]+w(v,u)<dist[u][1]，找到一个更短的距离，则把原来最短的距离作为次短的距离，同时更新最短的.即
    dist[u][2]=dist[u][1]  
    dist[u][1]=dist[v][cas]+w(v,u);  
    dp[u][2]=dp[u][1]  
    dp[u][1]=dp[v][cas]，
    把Node(dist[u][1],u,1)和Node(dist[u][2],u,2)放入队列
    
    情况2：dist[v][cas]+w(v,u)==dist[u][1]，找到一条新的相同距离的最短路，则dp[u][1]+=dp[v][cas],其他不用更新,也不入队
    
    情况3：dist[v][cas]+w(v,u)<dist[u][2]，不可以更新最短距离，但可以更新次短的，则更新dist[u][2]和dp[u][2] 
    dist[u][2]=dist[v][cas]+w(v,u); 
    dp[u][2]=dp[v][cas];
    把Node(dist[u][2],u,2)放入队列
    
    情况4：dist[v][cas]+w(v,u)==dist[u][2] 找到一条新的相同距离的次短路,则dp[u][2]+=dp[v][cas],其他不更新。
*/
 
 
 
void Dijkstra(int start,int end){
    for(int i=0;i<n;i++){
        dist[i][1]=dist[i][2]=inf;
    }
    memset(dp,0,sizeof(dp));
    memset(visited,false,sizeof(visited));
    priority_queue<Node>Q;
    Node p,q;
    dist[start][1]=0;
    dp[start][1]=1;
    p.dist=0,p.mark=1,p.v=start;
    Q.push(p);
    while(!Q.empty()){
        p=Q.top();
        Q.pop();
        if(visited[p.v][p.mark])continue;
        //if(dist[p.v][p.mark]!=p.dist)continue;
        visited[p.v][p.mark]=true;
        for(int i=0;i<vet[p.v].size();i++){
            int v=vet[p.v][i].v;
            int w=vet[p.v][i].w;
            if(!visited[v][1]&&p.dist+w<dist[v][1]){
                //可能为次短路
                if(dist[v][1]!=inf){
                    q.v=v,q.dist=dist[v][1],q.mark=2;
                    dist[v][2]=dist[v][1];
                    dp[v][2]=dp[v][1];
                    Q.push(q);
                }
                dist[v][1]=p.dist+w;
                dp[v][1]=dp[p.v][p.mark];
                q.v=v,q.dist=dist[v][1],q.mark=1;
                Q.push(q);
            }else if(!visited[v][1]&&p.dist+w==dist[v][1]){
                dp[v][1]+=dp[p.v][p.mark];
            }else if(!visited[v][2]&&p.dist+w<dist[v][2]){
                dist[v][2]=p.dist+w;
                dp[v][2]=dp[p.v][p.mark];
                q.dist=dist[v][2],q.v=v,q.mark=2;
                Q.push(q);
            }else if(!visited[v][2]&&p.dist+w==dist[v][2]){
                dp[v][2]+=dp[p.v][p.mark];
            }
        }
    }
}


int main(){
    while(~scanf("%d%d%d%d",&n,&m,&s,&e)){
        for(int i=0;i<n;i++)vet[i].clear();
        for(int i=1;i<=m;i++){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            Edge p;
            p.v=v,p.w=w;
            vet[u].push_back(p);
        }
        Dijkstra(s,e);
        printf("%d %d\n",dist[e][2],dp[e][2]);
    }
    return 0;
}
```

### 次短路SPFA

``` {.cpp}
#include<bits/stdc++.h>
using namespace std;
const int MAXR=100000+50;
const int MAXN=5000+50;
const int INF=0x7fffffff;
struct edge
{
    int to;
    int len;
};
vector<edge> E[MAXN];
int n,r,dis[MAXN],inque[MAXN],dis1[MAXN],dis2[MAXN];
int u[MAXR],v[MAXR],w[MAXR];

void addedge(int u,int v,int w) {
    E[u].push_back((edge){v,w});
    E[v].push_back((edge){u,w});
}

void init() {
    scanf("%d%d",&n,&r);
    for (int i=1;i<=r;i++) {
        scanf("%d%d%d",&u[i],&v[i],&w[i]);
        addedge(u[i],v[i],w[i]);
    }
}

void spfa(int S,int T) {
    for (int i=1;i<=n;i++) inque[i]=0,dis[i]=INF;
    queue<int> que;
    que.push(S);
    inque[S]=1;dis[S]=0;
    while (!que.empty()) {
        int head=que.front();que.pop();
        inque[head]=0;
        for (int i=0;i<E[head].size();i++) {
            int nowdis=dis[head]+E[head][i].len,to=E[head][i].to;
            if (nowdis<dis[to]) {
                dis[to]=nowdis;
                if (!inque[to]) {
                    que.push(to);
                    inque[to]=1;
                }
            }
        }
    }
}

void solve() {
    spfa(1,n);
    for (int i=1;i<=n;i++) dis1[i]=dis[i];
    spfa(n,1);
    for (int i=1;i<=n;i++) dis2 [i]=dis[i];
    int mx=dis1[n],ans=INF;
    for (int i=1;i<=r;i++) {
        int now=dis1[u[i]]+dis2[v[i]]+w[i];
        if (now!=mx) ans=min(ans,now);
        now=dis1[v[i]]+dis2[u[i]]+w[i];
        if (now!=mx) ans=min(ans,now);
    }
    printf("%d",ans);
}

int main() {
    init();
    solve();
    return 0;    
}
```

### Tarjan强连通分量

``` {.cpp}
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
```

### Tarjan求割点和桥

``` {.cpp}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

#define N 201
vector<int>G[N];
int n,m,low[N],dfn[N];
bool is_cut[N];
int father[N];
int tim=0;
void input()
{
    scanf("%d%d",&n,&m);
    int a,b;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a,&b);
        G[a].push_back(b);/*邻接表储存无向边*/
        G[b].push_back(a);
    }
}
void Tarjan(int i,int Father)
{
    father[i]=Father;/*记录每一个点的父亲*/
    dfn[i]=low[i]=tim++;
    for(int j=0;j<G[i].size();++j)
    {
        int k=G[i][j];
        if(dfn[k]==-1)
        {
            Tarjan(k,i);
            low[i]=min(low[i],low[k]);
        }
        else if(Father!=k)/*假如k是i的父亲的话，那么这就是无向边中的重边，有重边那么一定不是桥*/
            low[i]=min(low[i],dfn[k]);//dfn[k]可能！=low[k]，所以不能用low[k]代替dfn[k],否则会上翻过头了。
    }
}
void count()
{
    int rootson=0;
    Tarjan(1,0);
    for(int i=2;i<=n;++i)
    {
        int v=father[i];
        if(v==1)
        rootson++;/*统计根节点子树的个数，根节点的子树个数>=2,就是割点*/
        else{
            if(low[i]>=dfn[v])/*割点的条件*/
            is_cut[v]=true;
        }
    }
    if(rootson>1)
    is_cut[1]=true;
    for(int i=1;i<=n;++i)
    if(is_cut[i])
    printf("%d\n",i);
    for(int i=1;i<=n;++i)
    {
        int v=father[i];
        if(v>0&&low[i]>dfn[v])/*桥的条件*/
        printf("%d,%d\n",v,i);
    }
    
}
int main()
{
    input();
    memset(dfn,-1,sizeof(dfn));
    memset(father,0,sizeof(father));
    memset(low,-1,sizeof(low));
    memset(is_cut,false,sizeof(is_cut));
    count();
    return 0;
}
```

### 图论汇总

``` {.cpp}
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 1000;
const int INF = 0x3f3f3f3f;

//染色
//判断结点u所在的连通分量是否为二分图
//未染色结点值为0， 已染色结点值为1/2.
int color[MAXN];
bool bipartite(int u) {
    for(int i = 0; i < G[u].size(); i++){
        int v = G[u][i];                      //枚举每条边(u, v)
        if(color[v] == color[u]) return false;//结点v已着色，且和结点u的颜色冲突
        if(!color[v]) {
            color[v] = 3 - color[u];          //给结点v着与结点u相反的颜色
            if(!bipartite(v)) return false;
        }
    }
    return true;
}

//无向图求桥求割
struct Edge{
    int v, w;
    bool cut;
    Edge(int v, int w, int cnt = false) : v(v), w(w), cut(cut) {}
};
bool iscut[MAXN];
vector<Edge> G[MAXN];
int dfs_clock, low[MAXN], pre[MAXN];

int dfs(int u, int fa) {    //u在DFS树中的父节点是fa
    int lowu = pre[u] = ++dfs_clock;
    bool flag = false;
    int child = 0;          //子节点数目
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].v;
        if(!pre[v]) {
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);         //用后代的low函数更新u的low函数
            if(lowv >= pre[u]) {
                if(lowv > pre[u]) G[u][i].cut = true;
                iscut[u] = true;
            }
        } else if(v == fa) {
            if(flag) lowu = min(lowu, pre[v]);
            flag = true;
        } else lowu = min(lowu, pre[v]);       //用反向边更新u的low函数
    }
    if(fa < 0 && child == 1) iscut[u] = 0;
    low[u] = lowu;
    return lowu;
}

//有向图的强连通分量
vector<int> G[MAXN];
int pre[MAXN], low[MAXN], sccno[MAXN], dfs_clock, scc_cnt;
stack<int> S;

void Tarjan(int u) {
    pre[u] = low[u] = ++dfs_clock;
    S.push(u);
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!pre[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(!sccno[v]) low[u] = min(low[u], pre[v]);
    }
    if(low[u] == pre[u]) {
        scc_cnt++;
        while(true) {
            int x = S.top();
            S.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}

void find_scc(int n) {
    dfs_clock = scc_cnt = 0;
    memset(sccno, 0 , sizeof(sccno));
    memset(pre, 0, sizeof(pre));
    for(int i = 0; i < n; i++)
        if(!pre[i]) Tarjan(i);
}

//2-SAT
struct TwoSAT {
    stack<int> S;
    vector<int> G[MAXN*2];
    int n, dfs_clock, scc_cnt;
    int pre[MAXN*2], low[MAXN*2], sccno[MAXN*2];

    void init(int n) {
        this->n = n;
        for(int i = 0; i < MAXN*2; i++) g[i].clear();
    }

    void addEdge(int x, int xv, int y, int yv) {
        x = x*2 + xv;
        y = y*2 + yv;
        g[x].push_back(y);
    }

    void dfs(int u) {
        pre[u] = low[u] = ++dfs_clock;
        S.push(u);
        for(int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if(!pre[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if(!sccno[v]) low[u] = min(low[u], pre[v]);
        }
        if(low[u] == pre[u]) {
            scc_cnt++;
            while(true) {
                int x = S.top();
                S.pop();
                sccno[x] = scc_cnt;
                if(x == u) break;
            }
        }
    }

    void find_scc() {
        dfs_clock = scc_cnt = 0;
        memset(pre, 0, sizeof pre);
        memset(sccno, 0, sizeof sccno);
        for(int i = 0; i < n*2; i++) if(!pre[i]) dfs(i);
    }

    bool solve() {
        find_scc();
        for(int i = 0; i < n; i++)
            if(sccno[i*2] == sccno[i*2+1]) return false;
        return true;
    }
};


//Dijkstra(O(n2))
bool vis[MAXN];
int n, d[MAXN];
int w[MAXN][MAXN];
int fa[MAXN];
void Dijkstra(int s) {
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < n; i++) d[i] == (i == s ? 0 : INF);
    for(int i = 0; i < n; i++) {
        int x, m = INF;
        for(int y = 0; y < n; y++) if(!vis[y] && d[y] <= m) m = d[x=y];
        vis[x] = true;
        for(int y = 0; y < n; y++)
        if(d[y] > d[x] + w[x][y]) {
            d[y] = d[x] + w[x][y];
            fa[y] = x;
        }
    }
}

//Dijkstra+HeapNode(O(m*lgn))
struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};
struct HeapNode {
    int d, u;
    HeapNode() {}
    HeapNode(int d, int u) : d(d), u(u) {}

    bool operator < (const HeapNode& rhs) const {
        return d > rhs.d;
    }
};
struct Dijkstra {
    int n, m;
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool done[MAXN];
    int d[MAXN];
    int p[MAXN];

    void init(int n) {
        this -> n = n;
        for(int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }

    void addEdge(int u, int v, int w) {
        edges.push_back(Edge(u, v, w));
        G[u].push_back(edges.size()-1);
    }

    void dijkstra(int s) {
        priority_queue<HeapNode> Q;
        for(int i = 0; i <= n; i++) d[i] = INF;
        d[s] = 0;
        memset(done, 0, sizeof(done));
        Q.push(HeapNode(0,s));
        while(!Q.empty()) {
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if(done[u]) continue;
            done[u] = true;
            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(d[e.v] > d[u] + e.w) {
                    d[e.v] = d[u] + e.w;
                    p[e.v] = G[u][i];
                    Q.push(HeapNode(d[e.v], e.v));
                }
            }
        }
    }
};

//Floyed算法
void Floyed() {
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
}

//SPFA(BFS)
void SPFA(int s) {
    queue<int> Q;
    d[s] = 0;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to, w = edge[i].w;
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w;
                Q.push(v);
            }
        }
    }
}

//SPFA(DFS)
bool spfa(int u) {
    vis[u] = 1;
    for(int v = 1; v <= n; v++) {
        if(mp[u][v] && d[u] + e[v] > d[v] && d[u] + e[v] > 0) {
            d[v] = d[u] + e[v];
            if(!vis[v]) {
                if(spfa(v)) return true;
            } else return reach[v][n];
        }
    }
    vis[u] = 0;
    return d[n] > 0;
}

//两个条件下的最短路 HDU1245
void SPFA() {
    for(int i = 0; i < MAXN; i++) dis[i] = step[i] = INF, vis[i] = 0;
    queue<int> Q;
    dis[0] = step[0] = 0, vis[0] = 1;
    Q.push(0);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        vis[u] = 0;
        for(int j = 0; j < G[u].size(); j++) {
            int v = G[u][j].v;
            double len = G[u][j].dist;
            if(abs(dis[v]-dis[u]-len) <= EPS) {
                if(step[v] > step[u]+1)
                    step[v] = step[u]+1;
            } else if(dis[v] >= dis[u]+len) {
                dis[v] = dis[u]+len;
                step[v] = step[u]+1;
                if(!vis[v]) {
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

//Prim
int Prim() {
    int s = 0, cnt = 1, ans = 0, pos, low[MAXN];
    bool vis[MAXN];
    for(int i = 0; i <= n; i++) low[i] = INF, vis[i] = false;
    vis[s] = true;
    while(true) {
        if(cnt == n) break;
        int mn = INF;
        for(int j = 1; j < n; j++) {
            if(!vis[j] && low[j] > dist[s][j]) low[j] = dist[s][j];
            if(!vis[j] && mn > low[j]) mn = low[pos=j];
        }
        vis[s=pos] = true;
        ans += mn;
        cnt++;
    }
    return ans;
}

//Kruskal
void Kruskal() {
    ans = 0;
    for(int i = 0; i <= n; i++) fa[i] = i;
    for(unsigned i = 0; i < G.size(); i++) {
        int u = G[i].u, v = G[i].v, w = G[i].w;
        int x = Find(u), y = Find(v);
        if(x != y) {
            ans += w;
            fa[y] = x;
        }
    }
    printf("%d\n", ans);
}

//匈牙利算法（二分图最大匹配）O(|E|*sqrt(|V|))
bool vis[MAXN];
vector<int> G[MAXN];
int n, m, k, head[MAXN];

bool match(int x) {
    for(unsigned i = 0; i < G[x].size(); i++) {
        if(!vis[G[x][i]]) {
            vis[G[x][i]] = true;
            if(head[G[x][i]] == -1 || match(head[G[x][i]])) {
                head[G[x][i]] = x;
                return true;
            }
        }
    }
    return false;
}

int hungary() {
    int res = 0;
    memset(head, -1, sizeof(head));
    for(int i = 0; i < n; i++) {
        memset(vis, 0, sizeof(vis));
        if(match(i)) res++;
    }
    return res;
}


//最小树形图
/********************************************************************
* 给定一个有向图， 求以某个给定顶点为根的有向生成树(也就是说沿着
  这N-1条边可以从根走到任意点)，使权和最小。
* 判断是否存在最小树形图，以根为起点DFS一遍即可。
*********************************************************************/
double G[MAXN][MAXN];
int used[MAXN], pass[MAXN], eg[MAXN], more, Queue[MAXN], n, m;

inline void combine(int id, double& sum) {
    int tot = 0, from;
    for(; id != 0 && !pass[id]; id = eg[id]) {
        Queue[tot++] = id;
        pass[id] = 1;
    }
    for(from = 0; from < tot && Queue[from] != id; ++from);
    if(from == tot) return;
    more = 1;
    for(int i = from; i < tot; i++) {
        sum += G[eg[Queue[i]]][Queue[i]];
        if(i != from) {
            used[Queue[i]] = 1;
            for(int j = 1; j <= n; j++) if(!used[j]) {
                    if(G[Queue[i]][j] < G[id][j])
                        G[id][j] = G[Queue[i]][j];
                }
        }
    }
    for(int i = 1; i <= n; ++i) if(!used[i] && i != id) {
            for(int j = from; j < tot; ++j) {
                int k = Queue[j];
                if(G[i][id] > G[i][k] - G[eg[k]][k])
                    G[i][id] = G[i][k] - G[eg[k]][k];
            }
        }
}

inline double mdst(int root) {
    double sum = 0;
    memset(used, 0, sizeof(used));
    for(more = 1; more; ) {
        more = 0;
        memset(eg, 0, sizeof(eg));
        for(int i = 1; i <= n; ++i)
    }
}

//最大流Dinic算法(O(N^2*M))
struct Edge{
    int from, to, cap, flow;
    Edge() {}
    Edge(int from, int to, int cap, int flow) : from(from), to(to), cap(cap), flow(flow) {}
};

struct Dinic {
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];


    void AddEdge(int from, int to, int cap) {
//        cout << from << "<=====> " << to <<  "   "<< cap << endl;
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS() {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while(!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for(int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a) {
        if(x == t || a == 0) return a;
        int flow = 0, f;
        for(int& i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0 ) {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    int MaxFlow(int s, int t) {
        this-> s = s;
        this-> t = t;
        int flow = 0;
        while(BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
//        cout << flow << endl;
        return flow;
    }
};

//最小费用最大流
//是否在队列中
bool vis[MAXN];
//a可改尽量 p上一条弧 d费用
int a[MAXN], p[MAXN], d[MAXN];
//最大流, 最小费用
int flow, cost, n, m;

struct Edge {
    int from, to, cap, flow, cost;
    Edge() {}
    Edge(int from, int to, int cap, int flow, int cost) : from(from), to(to), cap(cap), flow(flow), cost(cost) {}
};

vector<Edge> edges;
vector<int> G[MAXN];

inline void init() {
    flow = cost = 0;
    for(int i = 0; i <= n; i++) G[i].clear();
    edges.clear();
}

void addEdge(int from, int to, int cap, int cost) {
    edges.push_back(Edge(from, to, cap, 0, cost));
    edges.push_back(Edge(to, from, 0, 0, -cost));
    int m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
}

bool spfa(int s, int t, int& flow, int& cost) {
    for(int i = 0; i <= n; i++) d[i] = INF;
    memset(vis, false, sizeof(vis));
    d[s] = 0, vis[s] = true, p[s] = 0, a[s] = INF;
    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for(int i = 0; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                d[e.to] = d[u] + e.cost;
                p[e.to] = G[u][i];
                a[e.to] = min(a[u], e.cap - e.flow);
                if(!vis[e.to]) Q.push(e.to), vis[e.to] = 1;
            }
        }
    }
    if(d[t] == INF) return false;
    flow += a[t], cost += d[t] * a[t];
    int u = t;
    while(u != s) {
        edges[p[u]].flow += a[t];
        edges[p[u]^1].flow -= a[t];
        u = edges[p[u]].from;
    }
    return true;
}

int main() {
    return 0;
}
```

数据结构
--------

### 单调栈维护凸包

``` {.cpp}
// 一个元素向左遍历的第一个比它小的数的位置就是将它插入单调栈时栈顶元素的值，若栈为空，则说明不存在这么一个数。然后将此元素的下标存入栈，就能类似迭代般地求解后面的元素
// hdu5033 单调栈维护凸包
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=1e6+10;
const double PI=acos(-1.0);
int t,n,m;
struct Build
{
    Build() { ang[0]=ang[1]=0; }
    double x,h;
    double ang[2];
    int id;
    bool flag;
    bool operator <(const Build&b) const { return x<b.x; }
}b[maxn<<1],q[maxn<<1];

bool cmp1(const Build&b1,const Build&b2) { return b1.x<b2.x; }
bool cmp2(const Build&b1,const Build&b2) { return b1.id<b2.id; }

inline double cal(Build &b1,Build&b2) {
    double dx=fabs(b1.x-b2.x);
    double dy=b2.h-b1.h;
    return dy/dx;
}

int main() {
    int cas=0;
    scanf("%d",&t);
    while (t--) {
        scanf("%d",&n);
        for (int i=0;i<n;i++) {
            scanf("%lf%lf",&b[i].x,&b[i].h);
            b[i].flag=false;
            b[i].id=i;
        }
        scanf("%d",&m);
        for (int i=n;i<n+m;i++) {
            scanf("%lf",&b[i].x);
            b[i].h=0;
            b[i].flag=true;
            b[i].id=i;
        }
        n+=m;
        sort(b,b+n,cmp1);
        q[0]=b[0];
        int top=0;
        for (int i=1;i<n;i++) {
            if (!b[i].flag) {
                while (top && cal(b[i],q[top])<cal(q[top],q[top-1]))
                    top--;
                q[++top]=b[i];
            } else {
                int tmp=top;
                while (tmp && cal(b[i],q[tmp])<cal(b[i],q[tmp-1]))
                    tmp--;
                b[i].ang[0]=cal(b[i],q[tmp]);
            }
        }

        q[0]=b[n-1];
        top=0;
        for (int i=n-2;i>=0;i--) {
            if (!b[i].flag) {
                while (top && cal(b[i],q[top])<cal(q[top],q[top-1]))
                    top--;
                q[++top]=b[i];
            } else {
                int tmp=top;
                while (tmp && cal(b[i],q[tmp])<cal(b[i],q[tmp-1]))
                    tmp--;
                b[i].ang[1]=cal(b[i],q[tmp]);
            }
        }
        printf("Case #%d:\n", ++cas);
        sort(b,b+n,cmp2);
        for (int i=0;i<n;i++) {
            if (b[i].flag) {
                double ans=(PI-atan(b[i].ang[0])-atan(b[i].ang[1]))/PI*180.0;
                printf("%lf\n", ans);
            }
        }
    }
    return 0;
}
```

### 单调队列

``` {.cpp}
#include <cstdio>
using namespace std;
const int N = 1e6 + 5;
int a[N], q[N], t[N];
int front, rear, n, k;

#define NOTMONO (!op && a[i] < q[rear - 1]) || (op && a[i] > q[rear - 1])
void getMonoQueue(int op) //op = 0 时单增队列  op = 1 时单减队列
{
    front = rear = 0;
    for(int i = 0; i < n; ++i)
    {
        while( rear > front && (NOTMONO)) --rear;
        t[rear] = i;      //记录滑窗滑到i点的时间
        q[rear++] = a[i];
        while(t[front] <= i - k) ++front;  //保证队首元素在滑窗之内
        if(i > k - 2)
            printf("%d%c", q[front], i == n - 1 ? '\n' : ' '); // 输出滑窗内最值
    }
}

int main()
{
    while (~scanf("%d%d", &n, &k))
    {
        for(int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        getMonoQueue(0); //单增队列维护最小值
        getMonoQueue(1); //单减队列维护最大值
    }

    return 0;
}
```

### 莫队算法

``` {.cpp}
// bzoj2038 小Z的袜子 莫队算法 对查询分块
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn=5e4+10;
int n,m;
int pos[maxn],L[maxn],R[maxn];
LL a[maxn],s[maxn];
struct Node
{
    LL a,b,l,r,id;
}q[maxn];
LL ans;

LL pw(LL x) { return x*x; }
LL gcd(LL a,LL b) { return b==0?a:gcd(b,a%b); }
inline bool cmp1(const Node&n1,const Node&n2) { return pos[n1.l]==pos[n2.l]?n1.r<n2.r:n1.l<n2.l; }
inline bool cmp2(const Node&n1,const Node&n2) { return n1.id<n2.id; }

inline void update(int k,int add) {
    ans-=pw(s[a[k]]);
    s[a[k]]+=add;
    ans+=pw(s[a[k]]);
}

void solve() {
    for (int i=1,l=1,r=0;i<=m;i++) {
        for (;l<q[i].l;l++) update(l,-1);
        for (;l>q[i].l;l--) update(l-1,1);
        for (;r<q[i].r;r++) update(r+1,1);
        for (;r>q[i].r;r--) update(r,-1);
        if (q[i].l==q[i].r) {
            q[i].a=0; q[i].b=1;
            continue;
        }
        q[i].a=ans-(q[i].r-q[i].l+1);
        q[i].b=(q[i].r-q[i].l+1)*(q[i].r-q[i].l);
        LL k=gcd(q[i].a,q[i].b);
        q[i].a/=k; q[i].b/=k;
    }
}

int main() {
    ans=0;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for (int i=1;i<=m;i++) {
        scanf("%lld%lld",&q[i].l,&q[i].r);
        q[i].a=q[i].b=0;
        q[i].id=i;
    }
    int t=(int)sqrt(n);
    for (int i=1;i<=t;i++) {
        L[i]=(i-1)*t+1;
        R[i]=i*t;
    }
    if (R[t]<n) ++t,L[t]=R[t-1]+1,R[t]=n;
    for (int i=1;i<=t;i++) for (int j=L[i];j<=R[i];j++) pos[j]=i;
    sort(q+1,q+1+m,cmp1);
    solve();
    sort(q+1,q+1+m,cmp2);
    for (int i=1;i<=m;i++) printf("%lld/%lld\n", q[i].a,q[i].b);
    return 0;
}
```

### 并查集

``` {.cpp}
// hdu3038 并查集
// 向量思想
#include <cstdio>
#include <cstring>
#define MAXN 200010
int N, M, par[MAXN], val[MAXN];

int findd(int x) {
    if (par[x] == -1) return x;
    int t = findd(par[x]);
    val[x] += val[par[x]];
    return par[x] = t;
}

int main() {
    while (scanf("%d%d", &N, &M) > 1 && N) {
        int A, B, S, ans = 0;
        memset(par, -1, sizeof(par));
        memset(val, 0, sizeof(val));
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &A, &B, &S);
            A = A - 1;
            int t1 = findd(A);
            int t2 = findd(B);
            if (t1 != t2) {
                par[t2] = t1;
                val[t2] = val[A] - val[B] + S;
            } else {
                if (val[B] - val[A] != S) ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

### 树状数组

``` {.cpp}
int bit[MAXN],n;
int sum(int i) {
    int s=0;
    while (i>0) {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}

void add(int i,int x) {
    while (i<=n) {
        bit[i]+=x;
        i+=i&-i;
    }
}
```

### 二维树状数组

``` {.cpp}
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=4096+12;
int n,m;
int ap[maxn][maxn];

void update(int x,int y,int z) {
    for (int i=x;i<=n;i+=i&-i)
        for (int j=y;j<=m;j+=j&-j)
            ap[i][j]+=z;
}

int query(int x,int y) {
    int sum=0;
    for (int i=x;i;i-=i&-i)
        for (int j=y;j;j-=j&-j)
            sum+=ap[i][j];
    return sum;
}

int main() {
    memset(ap,0,sizeof(ap));
    scanf("%d%d",&n,&m);
    int t1,a,b,c,d;
    while (scanf("%d",&t1)!=EOF) {
        scanf("%d%d%d",&a,&b,&c);
        if (t1==1) {
            update(a,b,c);
        } else if (t1==2) {
            scanf("%d",&d);
            if (a>c) swap(a,c);
            if (b>d) swap(b,d);
            printf("%d\n", query(c,d)-query(a-1,d)-query(c,b-1)+query(a-1,b-1));
        }
    }
    return 0;
}
```

### 点分治

``` {.cpp}
// poj1741 求树中两个节点d[x]+d[y]<k有多少个 点分治
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf=1<<29;
const int maxn=1e4+10;
int n,k;
int head[maxn],size[maxn],dis[maxn],mxson[maxn];
bool vis[maxn];
struct Edge
{
    int to,w,next;
}edge[maxn<<1];
int cnt,tot,root,sum; // sum 子树大小

void _init() {
    cnt=tot=root=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
}

inline void add(int u,int v,int w) {
    edge[cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

inline void dfs_root(int u,int f) {
    mxson[u]=0;
    size[u]=1;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (vis[v]||v==f) continue;
        dfs_root(v,u);
        size[u]+=size[v];
        mxson[u]=max(mxson[u],size[v]);
    }
    mxson[u]=max(mxson[u],sum-size[u]); // sum-size[u] !!!
    if (mxson[u]<mxson[0]) {
        mxson[0]=mxson[u];
        root=u;
    }
}

inline void dfs_dis(int u,int f,int dist) {
    dis[++tot]=dist;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (vis[v]||v==f) continue;
        dfs_dis(v,u,dist+edge[i].w);
    }
}

inline int calc(int u,int dist) {
    tot=0;
    dfs_dis(u,u,dist);
    sort(dis+1,dis+1+tot);
    int res=0;
    int i=1,j=tot;
    for (int i=1;i<j;i++) {
        while (dis[i]+dis[j]>k&&i<j) j--;
        res+=(j-i);
    }
    return res;
}

inline int dfs(int u) {
    mxson[0]=inf;
    dfs_root(u,u);
    vis[root]=1;
    int res=calc(root,0);
    for (int i=head[root];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (vis[v]) continue;
        res-=calc(v,edge[i].w);
        sum=size[v];
        res+=dfs(v);
    }
    return res;
}

int main() {
    while (scanf("%d%d",&n,&k)!=EOF && (n||k)) {
        _init();
        int u,v,w;
        for (int i=1;i<n;i++) {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w); add(v,u,w);
        }
        sum=n;
        printf("%d\n", dfs(1));
    }
    return 0;
}
```

### 线段树区间乘

``` {.cpp}
// bzoj1798 本题要求对p取模 记得开 long long!!!
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e5+10;
int n,m,p;
int a[maxn];
struct Node
{
    int l,r,sum,add,mul;
}val[maxn<<2];

inline void pushup(LL k) {
    val[k].sum=(val[k<<1].sum+val[k<<1|1].sum)%p;
}

inline void add_node(LL k,LL num) {
    val[k].add=(val[k].add+num)%p;
    val[k].sum=(val[k].sum+(val[k].r-val[k].l+1)*num%p)%p;
}

inline void mul_node(LL k,LL num) {
    val[k].mul=(val[k].mul*num)%p;
    val[k].add=(val[k].add*num)%p;
    val[k].sum=(val[k].sum*num)%p;
}

inline void pushdown(LL k) {
    if (val[k].mul!=1) {
        mul_node(k<<1,val[k].mul);
        mul_node(k<<1|1,val[k].mul);
        val[k].mul=1;
    }
    if (val[k].add!=0) {
        add_node(k<<1,val[k].add);
        add_node(k<<1|1,val[k].add);
        val[k].add=0;
    }
}

void build(LL k,LL x,LL y) {
    val[k].l=x; val[k].r=y;
    val[k].add=0; val[k].sum=0;
    val[k].mul=1;
    if (x==y) {
        val[k].sum=a[x];
        return;
    }
    LL mid=(x+y)>>1;
    build(k<<1,x,mid);
    build(k<<1|1,mid+1,y);
    pushup(k);
}

void updateAdd(LL k,LL x,LL y,LL v) {
    if (x>val[k].r||y<val[k].l) return;
    if (val[k].l>=x&&val[k].r<=y) {
        val[k].add=(val[k].add+v)%p;
        val[k].sum=(val[k].sum+(val[k].r-val[k].l+1)*v%p)%p;
        return;
    }
    pushdown(k);
    LL mid=(val[k].l+val[k].r)>>1;
    if (mid>=x) updateAdd(k<<1,x,y,v);
    if (mid<y)  updateAdd(k<<1|1,x,y,v);
    pushup(k);
}

void updateMul(LL k,LL x,LL y,LL v) {
    if (x>val[k].r||y<val[k].l) return;
    if (val[k].l>=x&&val[k].r<=y) {
        val[k].mul=(val[k].mul*v)%p;
        val[k].add=(val[k].add*v)%p;
        val[k].sum=(val[k].sum*v)%p;
        return;
    }
    pushdown(k);
    LL mid=(val[k].l+val[k].r)>>1;
    if (mid>=x) updateMul(k<<1,x,y,v);
    if (mid<y)  updateMul(k<<1|1,x,y,v);
    pushup(k);
}

LL query(LL k,LL x,LL y) {
    if (x>val[k].r||y<val[k].l) return 0;
    if (val[k].l>=x&&val[k].r<=y) return val[k].sum%p;
    pushdown(k);
    LL mid=(val[k].l+val[k].r)>>1;
    LL res=0;
    if (mid>=x) res=(res+query(k<<1,x,y))%p;
    if (mid<y)  res=(res+query(k<<1|1,x,y))%p;
    return res;
}

int main() {
    scanf("%d%d",&n,&p);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    scanf("%d",&m);
    int t1,t2,t3,t4;
    for (int i=1;i<=m;i++) {
        scanf("%d",&t1);
        if (t1==1) {
            scanf("%d%d%d",&t2,&t3,&t4);
            updateMul(1,t2,t3,t4);
        } else if (t1==2) {
            scanf("%d%d%d",&t2,&t3,&t4);
            updateAdd(1,t2,t3,t4);
        } else if (t1==3) {
            scanf("%d%d",&t2,&t3);
            printf("%lld\n", query(1,t2,t3));
        }
    }
    return 0;
}
```

### 线段树区间和区间开方

``` {.cpp}
// bzoj3211  线段树模板题
// pushup：
// (1)build的结尾，当叶子节点分别有对应的值后，它的父亲们就等于它们求和。
// (2)update的结尾，因为此时当前根的左右孩子已经更新了，故它也需要更新。

// pushdown(延迟标记):
// *pushdown会出现在一切要从当前结点往下的位置
// query和update中，要先把add的值传给两个儿子。

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e5+10;
int n,m;
int a[maxn];
LL sum[maxn<<2];
bool flag[maxn<<2];

void pushup(int k) {
    sum[k]=sum[k<<1]+sum[k<<1|1];
    flag[k]=flag[k<<1]&flag[k<<1|1];
}

void build(int k,int l,int r) {
    if (l==r) {
        sum[k]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    pushup(k);
}

void update(int k,int l,int r,int x,int y) {
    if (flag[k]) return;
    if (x>r||y<l) return;
    if (l==r) {
        sum[k]=(LL)sqrt(sum[k]);
        if (sum[k]==1||sum[k]==0) flag[k]=1;
        return;
    }
    int mid=(l+r)>>1;
    // -> pushdown 此题不需要
    update(k<<1,l,mid,x,y);
    update(k<<1|1,mid+1,r,x,y);
    pushup(k);
}

LL query(int k,int l,int r,int x,int y) {
    if (x>r||y<l) return 0;
    if (x<=l && y>=r) return sum[k];
    int mid=(l+r)>>1;
    // -> pushdown 此题不需要
    LL res=0;
    if (mid>=x) res+=query(k<<1,l,mid,x,y);
    if (mid<y)  res+=query(k<<1|1,mid+1,r,x,y);
    return res;
}

int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    scanf("%d",&m);
    int t1,t2,t3;
    for (int i=1;i<=m;i++) {
        scanf("%d%d%d",&t1,&t2,&t3);
        if (t1==1) printf("%lld\n", query(1,1,n,t2,t3));
        else update(1,1,n,t2,t3);
    }
    return 0;
}
```

### 线段树扫描线

``` {.cpp}
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
```

### 分块

``` {.cpp}
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1e6+10;
LL num[maxn],add[maxn],sum[maxn];
int pos[maxn],L[maxn],R[maxn];
int n,m;
char op[5];

void change(int l,int r,LL val) {
    int p1=pos[l],p2=pos[r];
    if (p1==p2) {
        for (int i=l;i<=r;i++) num[i]+=val;
        sum[p1]+=val*(r-l+1);
    } else {
        for (int i=p1+1;i<=p2-1;i++) add[i]+=val;
        for (int i=l;i<=R[p1];i++) num[i]+=val;
        sum[p1]+=val*(R[p1]-l+1);
        for (int i=L[p2];i<=r;i++) num[i]+=val;
        sum[p2]+=val*(r-L[p2]+1);
    }
}

LL query(int l,int r) {
    LL res=0;
    int p1=pos[l],p2=pos[r];
    if (p1==p2) {
        for (int i=l;i<=r;i++) res+=num[i];
        res+=add[p1]*(r-l+1);
    } else {
        for (int i=p1+1;i<=p2-1;i++) res+=sum[i]+add[i]*(R[i]-L[i]+1);
        for (int i=l;i<=R[p1];i++) res+=num[i];
        res+=add[p1]*(R[p1]-l+1);
        for (int i=L[p2];i<=r;i++) res+=num[i];
        res+=add[p2]*(r-L[p2]+1);
    }
    return res;
}

int main() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%lld",&num[i]);
    int t=sqrt(n);
    for (int i=1;i<=t;i++) {
        L[i]=(i-1)*t+1;
        R[i]=i*t;
    }
    if (R[t]<n) t++, L[t]=R[t-1]+1, R[t]=n;
    for (int i=1;i<=t;i++)
        for (int j=L[i];j<=R[i];j++) {
            sum[i]+=num[j];
            pos[j]=i;
        }

    int u,v,w;
    for (int i=1;i<=m;i++) {
        scanf("%s%d%d",op,&u,&v);
        if (op[0]=='Q') printf("%lld\n", query(u,v));
        else if (op[0]=='C') scanf("%d",&w),change(u,v,w);
    }
    return 0;
}
```

### ST算法求RMQ问题

``` {.cpp}
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+10;
const int maxm=1e6+10;
int n,m;
int a[maxn],f[maxn][25],logN[maxn];

int main() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);

    logN[0]=-1;
    for (int i=1;i<=n;i++) logN[i]=logN[i>>1]+1,f[i][0]=a[i];
    for (int j=1;j<25;j++)
        for (int i=1;i+(1<<j)-1<=n;i++)
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);

    int l,r;
    for (int i=1;i<=m;i++) {
        scanf("%d%d",&l,&r);
        int s=logN[r-l+1];
        printf("%d\n", max(f[l][s],f[r-(1<<s)+1][s]));
    }    
    return 0;
}
```

### KDTree(二维最近符合条件点)

``` {.cpp}
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
```

### 树链剖分+动态线段树

``` {.cpp}
// bzoj3531
// 对于需要n棵线段树维护的情况 可以通过动态线段树(即节点动态生成)
// 来节约内存 以免MLE
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> P;
const int maxn=1e5+10;
int n,m,cnt,tot,idx;
int root[maxn],w[maxn],s[maxn];
int head[maxn],seg[maxn],rev[maxn],dep[maxn],top[maxn],sz[maxn],fa[maxn],son[maxn];
struct Edge
{
    int to,next;
}edge[maxn<<1];
struct SegNode
{
    int l,r;
    LL sum,mx;
}tree[maxn*50];

void _init() {
    memset(head,-1,sizeof(head));
    cnt=tot=idx=0;
}

void add(int u,int v) {
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void dfs1(int u,int f) {
    fa[u]=f;
    dep[u]=dep[f]+1;
    sz[u]=1;
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (v==f) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        if (sz[v]>sz[son[u]]) son[u]=v;
    }
}

void dfs2(int u,int f) {
    seg[u]=++tot;
    rev[tot]=u;
    top[u]=f;
    if (son[u]) dfs2(son[u],f);
    for (int i=head[u];i!=-1;i=edge[i].next) {
        int v=edge[i].to;
        if (v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}

void update(int &k,int l,int r,int x,int val) {
    if (!k) k=++idx;
    if (l==r&&l==x) {
        tree[k].sum=tree[k].mx=val;
        return;
    }
    int mid=(l+r)>>1;
    if (mid>=x) update(tree[k].l,l,mid,x,val);
    if (mid<x) update(tree[k].r,mid+1,r,x,val);
    tree[k].sum=tree[tree[k].l].sum+tree[tree[k].r].sum;
    tree[k].mx=max(tree[tree[k].l].mx,tree[tree[k].r].mx);
}

// 1->sum  0->max
LL query(int k,int l,int r,int x,int y,int op) {
    if (x>r||y<l) return 0;
    if (x<=l&&y>=r) {
        if (op) return tree[k].sum;
        else return tree[k].mx;
    }
    int mid=(l+r)>>1;
    LL res=0;
    if (mid>=x) {
        if (op) res+=query(tree[k].l,l,mid,x,y,op);
        else res=max(res,query(tree[k].l,l,mid,x,y,op));
    }
    if (mid<y) {
        if (op) res+=query(tree[k].r,mid+1,r,x,y,op);
        else res=max(res,query(tree[k].r,mid+1,r,x,y,op));
    }
    return res;
}

LL ask(int u,int v,int op) {
    int k=root[s[u]];
    LL res=0;
    while (top[u]!=top[v]) {
        if (dep[top[u]]<dep[top[v]]) swap(u,v);
        if (op) res+=query(k,1,n,seg[top[u]],seg[u],op);
        else res=max(res,query(k,1,n,seg[top[u]],seg[u],op));
        u=fa[top[u]];
    }
    if (dep[u]>dep[v]) swap(u,v);
    if (op) res+=query(k,1,n,seg[u],seg[v],op);
    else res=max(res,query(k,1,n,seg[u],seg[v],op));
    return res;
}

int main() {
    _init();
    scanf("%d%d",&n,&m);
    int u,v;
    for (int i=1;i<=n;i++) scanf("%d%d",&w[i],&s[i]);
    for (int i=1;i<n;i++) {
        scanf("%d%d",&u,&v);
        add(u,v); add(v,u);
    }
    dfs1(1,1);
    dfs2(1,1);
    for (int i=1;i<=n;i++) update(root[s[i]],1,n,seg[i],w[i]);
    char op[5];
    for (int i=1;i<=m;i++) {
        scanf("%s%d%d",op,&u,&v);
        if (op[1]=='C') {
            update(root[v],1,n,seg[u],w[u]);
            update(root[s[u]],1,n,seg[u],0);
            s[u]=v;
        }
        if (op[1]=='W') {
            update(root[s[u]],1,n,seg[u],v);
            w[u]=v;
        }
        if (op[1]=='S') {
            printf("%lld\n", ask(u,v,1));
        }
        if (op[1]=='M') {
            printf("%lld\n", ask(u,v,0));
        }
    }
    return 0;
}
```

### 字典树Trie

``` {.cpp}
const int maxn=400010;
char buf[maxn];
int sum[maxn];
int tree[maxn][26];
int tot;

void insert(int n) {
    int root=0;
    for (int i=0;i<n;i++) {
        int id=buf[i]-'a';
        if (!tree[root][id])
            tree[root][id]=++tot;
        sum[tree[root][id]]++;
        root=tree[root][id];
    }
}

int find(int n) {
    int root=0;
    for (int i=0;i<n;i++) {
        int id=buf[i]-'a';
        if (!tree[root][id])
            return 0;
        root=tree[root][id];
    }
    return sum[root];
}
```

数论
----

### 分解质因子

``` {.cpp}
#include <vector>

using namespace std;

void solve(int n)
{
    vector<int> v;
    for (int i = 2; i*i <= n; ++i)
    {
        if (n%i==0)
        {
            v.push_back(i);
            while (n%i==0) n/=i;
        }
    }
    if (n>1) v.push_back(n);
}
```

### 容斥原理求互素数个数

``` {.cpp}
int solve (int n, int r) {
    vector<int> p;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            p.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        p.push_back (n);

    int sum = 0;
    for (int msk=1; msk<(1<<p.size()); ++msk) {
        int mult = 1, bits = 0;
        for (int i=0; i<p.size(); ++i)
            if (msk & (1<<i)) {
                ++bits;
                mult *= p[i];
            }

        int cur = r / mult;
        if (bits % 2 == 1)
            sum += cur;
        else
            sum -= cur;
    }

    return r - sum;
}
```

### 扩展欧几里得算法

``` {.cpp}
// ax + by = gcd(a, b)
// 返回值是 gcd(a, b)
int extend_Euclid(int a, int b, int &x, int &y)
{
    if(b==0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int r = extend_Euclid(b, a%b, y, x);
    y -= a/b*x; //这里已经是递归，回溯的过程了，x,y已经颠倒了
    return r;
}
```

### 欧拉函数

``` {.cpp}
// 欧拉函数被定义为小于或等于n的数中与n互质的个数
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=3e6+5;

int get_phi1(int n) {
    int ans=n;
    for (int i = 2; i*i <= n; ++i) {
        if (n%i==0) {
            ans=ans/i * (i-1);
            while (n%i==0) n/=i;
        }
    }
    if (n>1) ans=ans/n*(n-1);
    return ans;
}

long long phi[maxn];
void get_phi2(int n) {
    memset(phi,0,sizeof(phi));
    phi[1]=1;
    for (int i = 2; i <= n; ++i)
        if (!phi[i]) {
            for (int j = i; j <= n; j+=i) {
                if (!phi[j]) phi[j]=j;
                phi[j]=phi[j]/i * (i-1);
            }
        }
}

int main() {
    printf("%d\n", get_phi1(7));
    get_phi2(1000);
    for (int i = 0; i < 20; ++i)
        printf("%lld ", phi[i]);
    printf("\n");
    return 0;
}
```

### 求逆元

``` {.cpp}
// https://www.cnblogs.com/chendl111/p/5671470.html
#define LL long long

// 扩展欧几里得算法求逆元
// gcd(a, b) > 1时逆不存在
int ex_gcd_inverse(int a, int b, int &x, int &y) {
    int ret, tmp;
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ret = ex_gcd_inverse(b, a % b, x, y);
    tmp = x;
    x = y;
    y = tmp - a / b * y;
    return ret;
}

// 由于费马小定理，a^(p-1)=1(mod p)-->1/a=a^(p-2)(mod p),
// 故a的逆元为a^p-2.
// 注意这个方法要求模的数必须为质数，传入a和mod-2即可得到结果
LL quick_inverse(LL n, LL p, LL mod) {
    LL ret = 1,exponent = p;
    for (LL i = exponent; i; i >>= 1, n = n * n % mod) {
        if (i & 1) {
            ret = ret * n % mod;
        }
    } 
    return ret;
}

// 递推 1~n
int inv[N];
void get_inverse(int n, int p) {
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
}

// 反向递推 n!~1!
int invf[N], factor[N];
void get_factorial_inverse(int n, int p) {
    factor[0] = 1;
    for (int i = 1; i <= n; ++i) {
        factor[i] = i * factor[i - 1] % p;
    }
    invf[n] = quick_inverse(factor[n], p);
    for (int i = n-1; i >= 0; --i) {
        invf[i] = invf[i + 1] * (i + 1) % p;
    }
}
```

### 素数打表

``` {.cpp}
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
const int maxn=1e6+5;
const int maxm=1e7+5;
int n;
bool visit[maxm];
int p1[maxn]; 
// p1的大小大概估计一下再开数组。大概是（x/lnx）
int pnum; // 素数个数

void getprime1(int n) {
    memset(visit, false, sizeof(visit));
    int num = 0;
    for (int i = 2; i <= n; ++i) {
        if ( !visit[i] )  p1[num++] = i;
        for (int j = 0; j <= num && i * p1[j] <= n ;  j++) {
            visit[ i  *  p1[j] ]  =  true;
            if (i % p1[j] == 0) break; ///此处是重点，避免了很多的重复判断，比如i=9,现在素数是2,3,5,7,进入二重循环，visit[2*9]=1;visit[3*9]=1；这个时候9%3==0，要跳出。因为5*9可以用3*15来代替，如果这个时候计算了，i=15的时候又会被重复计算一次，所以这里大量避免了重复运算。
        }
    }
    pnum = num;
}

bool p2[maxn];
void getprime2(int n) {
    memset(p2,1,sizeof(p2));
    p2[0]=p2[1]=0;
    for (int i=2;i<n;i++) {
        if (i>n/i) continue;
        for (int j=i+i;j<n;j+=i)
            p2[j]=0;
    }
}

int main() {
    scanf("%d",&n);
    getprime2(n);
    for (int i = 0; i < n; ++i) {
        if (p2[i])
            printf("%d ", i);
    }
    return 0;
}
```

### 欧拉降幂

``` {.cpp}
// cf906D Power Tower 欧拉降幂应用
// n^x mod m=n^(φ(m)+x%φ(m)) mod m 式子当且仅当x>φ(m)时满足
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;
#define MOD(a,b) (a<b?a:a%b+b) // 保证取模方式一致 不然结果会出错
const int maxn=1e5+10;
LL n,m,mod;
LL a[maxn];
map<LL,LL> mp;

LL qpow(LL a,LL b,LL mod) {
    LL res=1;
    while (b) {
        if (b&1) res=MOD(res*a,mod);
        a=MOD(a*a,mod);
        b>>=1;
    }
    return res;
} 

LL phi(LL n) {
    LL res=n;
    if (mp.find(n)!=mp.end()) return mp[n];
    for (LL i=2;i*i<=n;i++) {
        if (n%i==0) {
            res=res/i*(i-1);
            while (n%i==0) n/=i;
        }
    }
    if (n>1) res=res/n*(n-1);
    return mp[n]=res;
}

LL solve(LL l,LL r,LL mod) {
    if (l==r||mod==1) return MOD(a[l],mod);
    return qpow(a[l],solve(l+1,r,phi(mod)),mod);
}

int main() {
    scanf("%lld%lld",&n,&mod);
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
    scanf("%lld",&m);
    LL l,r;
    while (m--) {
        scanf("%lld%lld",&l,&r);
        printf("%lld\n", solve(l,r,mod)%mod);
    }
    return 0;
}
```

### Lucas

``` {.cpp}
long long F[100010];  
void init(long long p)  
{  
    F[0] = 1;  
    for(int i = 1;i <= p;i++)  
        F[i] = F[i-1]*i % (1000000007);  
}  
long long inv(long long a,long long m)  
{  
    if(a == 1)return 1;  
    return inv(m%a,m)*(m-m/a)%m;  
}  

// 求解C(n,m)%p, n和m是非负整数, p是质数.
long long Lucas(long long n,long long m,long long p)  
{  
    long long ans = 1;  
    while(n&&m)  
    {  
        long long a = n%p;  
        long long b = m%p;  
        if(a < b)return 0;  
        ans = ans*F[a]%p*inv(F[b]*F[a-b]%p,p)%p;  
        n /= p;  
        m /= p;  
    }  
    return ans;  
}  
```

其余
----

### 矩阵快速幂

``` {.cpp}
/* 
    快速幂算法中矩阵上应用
    MOD mat维数 根据题意改变 
*/
const int MOD=100000;
struct Matrix
{
    int mat[110][110], n;
    Matrix() {}
    Matrix(int _n)
    {
        n = _n;
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                mat[i][j]=0;
    }
    Matrix operator *(const Matrix &b) const
    {
        Matrix ret(n);
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                for (int k=0;k<n;k++)
                {
                    int temp=(long long)mat[i][k]*b.mat[k][j]%MOD;
                    ret.mat[i][j]=(ret.mat[i][j]+temp)%MOD;
                }

        return ret;
    }
};

Matrix pow_M(Matrix a, int n)
{
    Matrix ret(a.n);
    for (int i=0;i<ret.n;i++)
        ret.mat[i][i]=1;
    Matrix tmp(a);
    while (n>0)
    {
        if (n&1) ret=ret*tmp;
        tmp=tmp*tmp;
        n>>=1;
    }
    return ret;
}
```

### 归并排序

``` {.cpp}
const int maxn = 100000;
int num[maxn];
void merge_sort(int l, int r) 
{
    int mid, p, q, i, j, len;

    if(l >= r)    return ;
    mid = (l + r) >> 1;
    len = r - l + 1;

    p = l; q = mid + 1;
    j = l;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    for(i = 0; i < len; ++i) {
        if((q > r) || (num[p] < num[q] && p <= mid)) {
            t[j++] = num[p++];
        } else {
            t[j++] = num[q++];
        }
    }
    for(i = l; i <= r; ++i)
        num[i] = t[i];
}
```

### 极角排序

``` {.cpp}
struct point
{
    double x,y;
};

double cross(double x1,double y1,double x2,double y2) //计算叉积
{
    return (x1*y2-x2*y1);
}

double compare(point a,point b,point c)
{
    return cross((b.x-a.x),(b.y-a.y),(c.x-a.x),(c.y-a.y));
}

bool cmp0(const point& a, const point& b) //利用complex类按极角从小到大排序
{
    complex<double> c1(a.x,a.y); //头文件 #include<complex>
    complex<double> c2(b.x,b.y);
    if( arg(c1) == arg(c2))
        return a.x<b.x;
    return arg(c1) < arg(c2);
}

bool cmp1(point a,point b)//利用atan2()函数按极角从小到大排序
{
    if(atan2(a.y,a.x)!=atan2(b.y,b.x))
        return atan2(a.y,a.x)<atan2(b.y,b.x);
    else return a.x<b.x;
}

bool cmp2(point a,point b) //利用叉积按极角从小到大排序
{
    point c; //原点
    c.x = 0;
    c.y = 0;
    if(compare(c,a,b)==0)
        return a.x<b.x;
    else return compare(c,a,b)>0;
}

int Quadrant(point a)　　   //象限排序
{
    if(a.x>0&&a.y>=0)  return 1;
    if(a.x<=0&&a.y>0)  return 2;
    if(a.x<0&&a.y<=0)  return 3;
    if(a.x>=0&&a.y<0)  return 4;
}


bool cmp3(point a,point b)  //先按象限从小到大排序 再按极角从小到大排序
{
    if(Quadrant(a)==Quadrant(b))
        return cmp1(a,b);
    else Quadrant(a)<Quadrant(b);
}
```

### 数位DP

``` {.cpp}

typedef long long ll;  
int a[20];  
ll dp[20][state]; // 不同题目状态不同  
ll dfs(int pos,/*state变量*/,bool lead/*前导零*/,bool limit/*数位上界变量*/)//不是每个题都要判断前导零  
{  
    //递归边界，既然是按位枚举，最低位是0，那么pos==-1说明这个数我枚举完了  
    if(pos==-1) return 1; /*这里一般返回1，表示你枚举的这个数是合法的，那么这里就需要你在枚举时必须每一位都要满足题目条件，也就是说当前枚举到pos位，一定要保证前面已经枚举的数位是合法的。不过具体题目不同或者写法不同的话不一定要返回1 */  
    // 第二个就是记忆化(在此前可能不同题目还能有一些剪枝)  
    if(!limit && !lead && dp[pos][state]!=-1) return dp[pos][state];  
    /*常规写法都是在没有限制的条件记忆化，这里与下面记录状态是对应，具体为什么是有条件的记忆化后面会讲*/  
    int up=limit?a[pos]:9; // 根据limit判断枚举的上界up;这个的例子前面用213讲过了  
    ll ans=0;  
    // 开始计数  
    for(int i=0;i<=up;i++) // 枚举，然后把不同情况的个数加到ans就可以了  
    {  
        if() ...  
        else if()...  
        ans+=dfs(pos-1,/*状态转移*/,lead && i==0,limit && i==a[pos]) //最后两个变量传参都是这样写的  
        /*这里还算比较灵活，不过做几个题就觉得这里也是套路了 
        大概就是说，我当前数位枚举的数是i，然后根据题目的约束条件分类讨论 
        去计算不同情况下的个数，还有要根据state变量来保证i的合法性，比如题目 
        要求数位上不能有62连续出现,那么就是state就是要保存前一位pre,然后分类， 
        前一位如果是6那么这意味就不能是2，这里一定要保存枚举的这个数是合法*/  
    }  
    //计算完，记录状态  
    if(!limit && !lead) dp[pos][state]=ans;  
    /*这里对应上面的记忆化，在一定条件下时记录，保证一致性，当然如果约束条件不需要考虑lead，这里就是lead就完全不用考虑了*/  
    return ans;  
}  
ll solve(ll x)  
{  
    int pos=0;  
    while(x) // 把数位都分解出来  
    {  
        a[pos++]=x%10; // 个人老是喜欢编号为[0,pos),看不惯的就按自己习惯来，反正注意数位边界就行  
        x/=10;  
    }  
    return dfs(pos-1/*从最高位开始枚举*/,/*一系列状态 */,true,true); // 刚开始最高位都是有限制并且有前导零的，显然比最高位还要高的一位视为0嘛  
}  
int main()  
{  
    ll le,ri;  
    while(~scanf("%lld%lld",&le,&ri))  
    {  
        // 初始化dp数组为-1,这里还有更加优美的优化,后面讲  
        printf("%lld\n",solve(ri)-solve(le-1));  
    }  
}  

// 例题hdu2089
// 给定区间[n,m],求在n到m中没有“62“或“4“的数的个数。如62315包含62，88914包含4，这两个数都是不合法的
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define LL long long
int a[10];
LL dp[10][2];
int l,r;

LL dfs(int pos,int pre,int state,bool limit)
{
    if (pos==-1) return 1;
    if (!limit && dp[pos][state]!=-1) return dp[pos][state];
    int up=limit?a[pos]:9;
    int tmp=0;
    for (int i=0;i<=up;i++)
    {
        if (pre==6 && i==2) continue;
        if (i==4) continue;
        tmp+=dfs(pos-1,i,i==6,limit&&i==a[pos]);
    }
    if (!limit) dp[pos][state]=tmp;
    return tmp;
}

LL solve(int x)
{
    int cnt=0;
    while (x>0)
    {
        a[cnt++]=x%10;
        x/=10;
    }
    return dfs(cnt-1,-1,0,true);
}

int main()
{
    while (scanf("%d%d",&l,&r)!=EOF && (l||r))
    {
        memset(dp,-1,sizeof(dp));
        printf("%lld\n", solve(r)-solve(l-1));
    }
    return 0;
}
```

### 欧拉序

``` {.cpp}
vector<int> g[40010];
int len_a,a[80020],len_b,b[80020];

// dfs(1,0)
void dfs(int u,int fa)
{
    a[++len_a]=u; 
    b[++len_b]=u;
    int sz=g[u].size();
    for(int i=0; i<sz; i++)
    {
        if(g[u][i]!=fa)
        {
            dfs(g[u][i],u);
            a[++len_a]=u; // dfs到加进, dfs回加进, 总共加入度遍 --- 欧拉序 1
        }
    }
    b[++len_b]=u; // dfs进加进, dfs最后一次回加进, 总共加两遍 --- 欧拉序 2
}

/*
用处:
    1. 求LCA
    2. 求子树的权值之和
*/
```

### DFS序

``` {.cpp}
vector<int> G[MAXN];
int T,n,m;
int tot;
int le[MAXN<<1],ri[MAXN<<1],id[MAXN];

// dfs(1,0)
void dfs(int u,int fa)
{
    tot++;
    id[tot]=u;
    le[u]=ri[u]=tot;
    int sz=G[u].size();
    for (int i=0;i<sz;i++)
    {
        int v=G[u][i];
        if (v!=fa)
        {
            dfs(v,u);
            ri[u]=max(ri[u],ri[v]);
        }
    }
}
```

### 背包

``` {.cpp}
#include <iostream>  
#include <cstring>  
using namespace std;  
#define maxV 1000  
  
int f[maxV], v;  
  
void ZeroOnePack(int ci, int wi) {  
    for (int j = v; j >= 0; j--)   
        if (j >= ci)  
            f[j] = max(f[j], f[j - ci] + wi);  
}  
  
void CompletePack(int ci, int wi) {  
    for (int j = 0; j <= v; j++)   
        if (j >= ci)  
            f[j] = max(f[j], f[j - ci] + wi);  
}  
  
void MultiplePack(int ni, int ci, int wi) {  
    if (ni * ci >= v) {  
        CompletePack(ci, wi);  
        return;  
    }  
    int k = 1, amount = ni;  
    while (k < ni) {  
        ZeroOnePack(ci * k, wi * k);  
        amount -= k;  
        k *= 2;  
    }  
    ZeroOnePack(ci * amount, wi * amount);  
}  
  
int main(void) {  
    int cases, n, ni, ci, wi;  
    freopen("4.txt", "r", stdin);  
    cin >> cases;  
    while (cases--) {  
        memset(f, 0, sizeof(f));  
        cin >> n >> v;  
        for (int i = 0; i < n; i++) {  
            cin >> ni >> ci >> wi;  
            if (ni == 1) ZeroOnePack(ci, wi);  
            else if (ni == -1) CompletePack(ci, wi);  
            else MultiplePack(ni, ci, wi);  
        }  
        for (int i = 0; i <= v; i++) cout << f[i] << " "; cout << endl;  
        cout << f[v] << endl;  
    }  
}  
```

### 蔡勒公式

``` {.cpp}
bool isMonday(int year,int month,int day)
{
    if(month < 3) { year -= 1;  month += 12; }
    int c = int (year / 100), y = year - 100 * c;
    int w = int ( c / 4) - 2 * c + y + int ( y / 4 ) +(26 * ( month + 1 ) / 10) + day - 1;
    w = (w % 7 + 7) % 7;

    if (w == 1) return 1; // Monday
    else return 0;
}
```

### 高精度

``` {.cpp}
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct BigInteger {  
    typedef unsigned long long LL;  
  
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;
  
    BigInteger& clean(){while(!s.back()&&s.size()>1)s.pop_back(); return *this;}  
    BigInteger(LL num = 0) {*this = num;}  
    BigInteger(string s) {*this = s;}  
    BigInteger& operator = (long long num) {  
        s.clear();  
        do {  
            s.push_back(num % BASE);  
            num /= BASE;  
        } while (num > 0);  
        return *this;  
    }  
    BigInteger& operator = (const string& str) {  
        s.clear();  
        int x, len = (str.length() - 1) / WIDTH + 1;  
        for (int i = 0; i < len; i++) {  
            int end = str.length() - i*WIDTH;  
            int start = max(0, end - WIDTH);  
            sscanf(str.substr(start,end-start).c_str(), "%d", &x);  
            s.push_back(x);  
        }  
        return (*this).clean();  
    }  
  
    BigInteger operator + (const BigInteger& b) const {  
        BigInteger c; c.s.clear();  
        for (int i = 0, g = 0; ; i++) {  
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;  
            int x = g;  
            if (i < s.size()) x += s[i];  
            if (i < b.s.size()) x += b.s[i];  
            c.s.push_back(x % BASE);  
            g = x / BASE;  
        }  
        return c;  
    }  
    BigInteger operator - (const BigInteger& b) const {  
        assert(b <= *this); // 减数不能大于被减数  
        BigInteger c; c.s.clear();  
        for (int i = 0, g = 0; ; i++) {  
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;  
            int x = s[i] + g;  
            if (i < b.s.size()) x -= b.s[i];  
            if (x < 0) {g = -1; x += BASE;} else g = 0;  
            c.s.push_back(x);  
        }  
        return c.clean();  
    }  
    BigInteger operator * (const BigInteger& b) const {  
        int i, j; LL g;  
        vector<LL> v(s.size()+b.s.size(), 0);  
        BigInteger c; c.s.clear();  
        for(i=0;i<s.size();i++) for(j=0;j<b.s.size();j++) v[i+j]+=LL(s[i])*b.s[j];  
        for (i = 0, g = 0; ; i++) {  
            if (g ==0 && i >= v.size()) break;  
            LL x = v[i] + g;  
            c.s.push_back(x % BASE);  
            g = x / BASE;  
        }  
        return c.clean();  
    }  
    BigInteger operator / (const BigInteger& b) const {  
        assert(b > 0);  // 除数必须大于0  
        BigInteger c = *this;       // 商:主要是让c.s和(*this).s的vector一样大  
        BigInteger m;               // 余数:初始化为0  
        for (int i = s.size()-1; i >= 0; i--) {  
            m = m*BASE + s[i];  
            c.s[i] = bsearch(b, m);  
            m -= b*c.s[i];  
        }  
        return c.clean();  
    }  
    BigInteger operator % (const BigInteger& b) const { //方法与除法相同  
        BigInteger c = *this;  
        BigInteger m;  
        for (int i = s.size()-1; i >= 0; i--) {  
            m = m*BASE + s[i];  
            c.s[i] = bsearch(b, m);  
            m -= b*c.s[i];  
        }  
        return m;  
    }  
    // 二分法找出满足bx<=m的最大的x  
    int bsearch(const BigInteger& b, const BigInteger& m) const{  
        int L = 0, R = BASE-1, x;  
        while (1) {  
            x = (L+R)>>1;  
            if (b*x<=m) {if (b*(x+1)>m) return x; else L = x;}  
            else R = x;  
        }  
    }  
    BigInteger& operator += (const BigInteger& b) {*this = *this + b; return *this;}  
    BigInteger& operator -= (const BigInteger& b) {*this = *this - b; return *this;}  
    BigInteger& operator *= (const BigInteger& b) {*this = *this * b; return *this;}  
    BigInteger& operator /= (const BigInteger& b) {*this = *this / b; return *this;}  
    BigInteger& operator %= (const BigInteger& b) {*this = *this % b; return *this;}  
  
    bool operator < (const BigInteger& b) const {  
        if (s.size() != b.s.size()) return s.size() < b.s.size();  
        for (int i = s.size()-1; i >= 0; i--)  
            if (s[i] != b.s[i]) return s[i] < b.s[i];  
        return false;  
    }  
    bool operator >(const BigInteger& b) const{return b < *this;}  
    bool operator<=(const BigInteger& b) const{return !(b < *this);}  
    bool operator>=(const BigInteger& b) const{return !(*this < b);}  
    bool operator!=(const BigInteger& b) const{return b < *this || *this < b;}  
    bool operator==(const BigInteger& b) const{return !(b < *this) && !(b > *this);}  
};  
  
ostream& operator << (ostream& out, const BigInteger& x) {  
    out << x.s.back();  
    for (int i = x.s.size()-2; i >= 0; i--) {  
        char buf[20];  
        sprintf(buf, "%08d", x.s[i]);  
        for (int j = 0; j < strlen(buf); j++) out << buf[j];  
    }  
    return out;  
}  
  
istream& operator >> (istream& in, BigInteger& x) {  
    string s;  
    if (!(in >> s)) return in;  
    x = s;  
    return in;  
}
```

### Base64

``` {.cpp}
#include <cstdio>
#include <cstring>

static const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encodeblock(unsigned char in[3], unsigned char out[4], int len) {
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}

void encode(FILE *infile, FILE *outfile) {
    unsigned char in[3], out[4];
    int i, len;

    while (!feof(infile)) {
        len = 0;
        for (i = 0; i < 3; i++) {
            in[i] = (unsigned char) getc(infile);
            if (!feof(infile)) {
                len++;
            } else {
                in[i] = 0;
            }
        }
        if (len) {
            encodeblock(in, out, len);
            for (i = 0; i < 4; i++) {
                putc(out[i], outfile);
            }
        }
    }
}

unsigned char decode_char2code(unsigned char c)
{
    if (c >= '0' && c <= '9') return c-'0'+52;
    if (c >= 'a' && c <= 'z') return c-'a'+26;
    if (c >= 'A' && c <= 'Z') return c-'A';
    if (c == '+') return 62;
    if (c == '/') return 63;
    return 0; // '='
}

int decode(unsigned char in[], unsigned char out[])
{
    int t = 0;
    int len = strlen(in);
    while (in[len - 1] == '=') len--;
    for (int i = 0; i < len; i++)
        in[i] = decode_char2code(in[i]);

    for (int i = 0; i < len; i++)
    {
        out[t++] = ((in[i] << 2) | (in[i + 1] >> 4));
        if (i + 2 < len)
            out[t++] = ((in[i + 1] << 4) | (in[i + 2] >> 2));
        if (i + 3 < len)
            out[t++] = ((in[i + 2] << 6) | in[i + 3]);
    }
    return t; // 解码后长度
}
```

### DFS子集生成

``` {.cpp}
// 子集生成 生成[0, n)的所有子集.
// 用法：
// dfs(n,0);
// void dfs(int n,int cur) {
//     for(int i=0;i<cur;++i)
//         printf("%d ",a[i]);
//     printf("\n");
//     int MIN=(cur?a[cur-1]+1:0);
//     for (int i=MIN; i<n; i++) {
//         a[cur]=i;
//         dfs(n,cur+1);
//     }
// }
#include<iostream>
using namespace std;
int visit[100];//用来判断这个数字是否被访问过 如 visit[2]=1;说明数字2被访问过 
int a[100];//0-(n-1)存放数字 
void dfs(int index,int n)
{
    if(index==n)//终止条件 
    {
        for(int i=0;i<n;i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<endl;
        return;
    }
    for(int i=1;i<=n;i++)//判断数字是否被访问过 
    {
        if(visit[i]==0)
        {
            visit[i]=1;
            a[index]=i;
            dfs(index+1,n);
            visit[i]=0;
        }
    }
}
int main()
{   int n;  
    cin>>n;
    dfs(0,n);//前者表示目前是第几个数字，后者表示 n(用来进行终止条件判断的)
    return 0;
}
```

### LCS & LIS

``` {.cpp}
// 最长公共子序列
const int maxn = 10000;
int dp[maxn];
int a[maxn],b[maxn];
int LCS(int n, int m) {
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; i++) {
        int tmp = 0; // 存 i 确定, 且 a[i] > b[j] 时最大的 dp[j]
        for(int j = 1; j <= m; j++) {
            if(a[i] > b[j] && dp[j] > tmp)
                tmp = dp[j];
            else if(a[i] == b[j])
                dp[j] = tmp+1;
        }
    }

    int ans = 0;
    for(int i = 1; i <= m; i++)
        ans = max(ans, dp[i]);
    return ans;
}

// 最长上升子序列
const int maxn = 10000;
int dp[maxn];
int a[maxn];
int LIS(int sign) {
    fill(dp,dp+maxn,inf);
    int ans = 0;
    for(int i=0;i<n;i++){
        int index = upper_bound(dp,dp+ans,a[i]*sign) - dp;//这个是求不严格的序列，如果要求严格的就用lower_bound
        dp[index] = a[i]*sign;
        ans = max(ans,index+1);
    }
    return ans;
}
int lins() { return LIS(1); } // 求上升的
int lnds() { return LIS(-1); } //求下降的
```

### 读入优化

``` {.cpp}
inline int read() {
    int ret=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
        ret=(ret<<1)+(ret<<3)+ch-'0',ch=getchar();
    return ret;
}
```
