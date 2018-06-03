[TOC]

## 组合数学
### 指数型母函数

![](/Users/zdz/Documents/GitHub/Code/Template/组合数学/指数型母函数性质.jpg)
![](/Users/zdz/Documents/GitHub/Code/Template/组合数学/指数型母函数应用.jpg)

```c++
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

```c++
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

```c++
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

## 图论
### 链式前向星

```c++
void add(int u,int v,int w)  
{  
    edge[cnt].w = w;  
    edge[cnt].to = v;  
    edge[cnt].next = head[u];  
    head[u] = cnt++;  
} 
```

### 二分匹配(匈牙利算法)

```c++
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

```c++
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

```c++
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

```c++
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

### 最小生成树(Prim)

```c++
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

```c++
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

### 最短路Bellman

```c++
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

### 最短路Dijkstra

```c++
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

### 最短路Floyd

```c++
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

### 最短路SPFA

```c++
#define MAX 310

bool vis[MAX];
int dis[MAXN], edge[MAXN][MAXN];

// n个顶点 1~n
void spfa(int start, int n)
{
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) dis[i] = INF;
    dis[start] = 0;
    vis[start] = 1;
    queue<int> que;
    que.push(start);
    while (!que.empty())
    {
        int t = que.front(); que.pop();
        vis[t] = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (dis[i] > dis[t] + edge[t][i])
            {
                dis[i] = dis[t] + edge[t][i];
                if (!vis[i])
                {
                    vis[i] = 1;
                    que.push(i);
                }
            }
        }
    }
}
```

### Tarjan强连通分量

```c++
// Belong 数组存强连通分量
int DFN[MAXN],LOW[MAXN],Stap[MAXN],Belong[MAXN];
bool instack[MAXN];
int Stop,Dindex,Bcnt;
void Tarjan(int u)
{
    int tmp;
    DFN[u]=LOW[u]=++Dindex;
    instack[u]=true;
    Stap[++Stop]=u;
    int sz=G[u].size();
    for (int i=0;i<sz;i++)
    {
        int v=G[u][i];
        if (!DFN[v])
        {
            Tarjan(v);
            if (LOW[v]<LOW[u])
                LOW[u]=LOW[v];
        }
        else if (instack[v] && DFN[v]<LOW[u])
            LOW[u]=DFN[v];
    }
    if (DFN[u]==LOW[u])
    {
        Bcnt++;
        do
        {
            tmp=Stap[Stop--];
            instack[tmp]=false;
            Belong[tmp]=Bcnt;
        }
        while (tmp!=u);
    }
}

void _init()
{
    CLR(DFN,0);
    CLR(LOW,0);
    CLR(instack,0);
    CLR(Belong,-1);
}

void solve()
{
    int i;
    Stop=Bcnt=Dindex=0;
    memset(DFN,0,sizeof(DFN));
    for (i=1;i<=N;i++)
        if (!DFN[i])
            Tarjan(i);
}
```

### Tarjan求割点和桥

```c++
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

```c++
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

## 数据结构
### 单调栈

```c++
// 一个元素向左遍历的第一个比它小的数的位置就是将它插入单调栈时栈顶元素的值，若栈为空，则说明不存在这么一个数。然后将此元素的下标存入栈，就能类似迭代般地求解后面的元素
Stack<int> S;
for(int i=1 ;i<=n ;i++){
    while(S.size() && a[S.top()] >= a[i]) S.pop();

    if(S.empty())     L[i] = 0;
    else              L[i] = S.top();

    S.push(i);
}
```

### 单调队列

```c++
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

### 字典树

```c++
#define MAXN 400010

char buf[MAXN];
int sum[MAXN];
int tree[MAXN][26];
int tot;

void insert(int n)
{
    int root=0;
    for (int i=0;i<n;i++)
    {
        int id=buf[i]-'a';
        if (!tree[root][id])
            tree[root][id]=++tot;
        sum[tree[root][id]]++;
        root=tree[root][id];
    }
}

int find(int n)
{
    int root=0;
    for (int i=0;i<n;i++)
    {
        int id=buf[i]-'a';
        if (!tree[root][id])
            return 0;
        root=tree[root][id];
    }
    return sum[root];
}
```

### 并查集

```c++
// 查并集
// 向量思想
#include <cstdio>
#include <cstring>

#define MAXN 200010
int N, M, par[MAXN], val[MAXN];

int findd(int x)
{
    if (par[x] == -1) return x;
    int t = findd(par[x]);
    val[x] += val[par[x]];
    return par[x] = t;
}

int main()
{
    while (scanf("%d%d", &N, &M) > 1 && N)
    {
        int A, B, S, ans = 0;
        memset(par, -1, sizeof(par));
        memset(val, 0, sizeof(val));
        for (int i = 0; i < M; ++i)
        {
            scanf("%d%d%d", &A, &B, &S);
            A = A - 1;
            int t1 = findd(A);
            int t2 = findd(B);
            if (t1 != t2)
            {
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

```c++

#include <iostream>  
#include <string>  
using namespace std;  
const int N=1010;  
int bit[N];  
int n;  
int lowbit(int i)  
{  
    return i&(-i);  
}  
int insert(int i,int x)  
{  
    while(i<=n)  
    {  
        bit[i]+=x;  
        i+=lowbit(i);  
    }  
    return 0;  
}  
int query(int i)  
{  
    int sum=0;  
    while(i)  
    {  
        sum+=bit[i];  
        i-=lowbit(i);  
    }  
    return sum;  
}  
int main()  
{  
    while(cin>>n)  
    {  
        int ans=0;  
        memset(bit,0,sizeof(bit));  
        for(int i=1;i<=n;i++)  
        {  
            int a;  
            cin>>a;  
            insert(a,1);  
            ans+=i-query(a);  
        }  
        cout<<ans<<endl;  
    }  
    return 0;  
}  
```

### 线性基

```c++
struct L_B{
    long long d[61],p[61];
    int cnt;
    L_B()
    {
        memset(d,0,sizeof(d));
        memset(p,0,sizeof(p));
        cnt=0;
    }
    bool insert(long long val)
    {
        for (int i=60;i>=0;i--)
            if (val&(1LL<<i))
            {
                if (!d[i])
                {
                    d[i]=val;
                    break;
                }
                val^=d[i];
            }
        return val>0;
    }
    long long query_max()
    {
        long long ret=0;
        for (int i=60;i>=0;i--)
            if ((ret^d[i])>ret)
                ret^=d[i];
        return ret;
    }
    long long query_min()
    {
        for (int i=0;i<=60;i++)
            if (d[i])
                return d[i];
        return 0;
    }
    void rebuild()
    {
        for (int i=60;i>=0;i--)
            for (int j=i-1;j>=0;j--)
                if (d[i]&(1LL<<j))
                    d[i]^=d[j];
        for (int i=0;i<=60;i++)
            if (d[i])
                p[cnt++]=d[i];
    }
    long long kthquery(long long k)
    {
        int ret=0;
        if (k>=(1LL<<cnt))
            return -1;
        for (int i=60;i>=0;i--)
            if (k&(1LL<<i))
                ret^=p[i];
        return ret;
    }
}
L_B merge(const L_B &n1,const L_B &n2)
{
    L_B ret=n1;
    for (int i=60;i>=0;i--)
        if (n2.d[i])
            ret.insert(n1.d[i]);
    return ret;
}
```

### 线段树

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define MAXN 100010
#define CLR(a,b) memset(a,b,sizeof(a))

LL num[MAXN];
struct SegTree
{
    #define Mid ((l+r)>>1)
    #define lson l,m,rt<<1
    #define rson m+1,r,rt<<1|1
    LL _sum[MAXN<<2], _lazy[MAXN<<2];

    void PushDown(int rt)
    {
        if (_lazy[rt])
        {
            _sum[rt << 1] += _lazy[rt];  
            _sum[rt << 1 | 1] += _lazy[rt];  
            _lazy[rt << 1] += _lazy[rt];  
            _lazy[rt << 1 | 1] += _lazy[rt];  
            _lazy[rt] = 0; 
        }
    }

    inline void PushUp(int rt)
    {
        _sum[rt]=_sum[rt<<1]+_sum[rt<<1|1];
    }

    void Build(LL l, LL r, LL rt)
    {
        _lazy[rt]=0;
        if (l==r)
        {
            _sum[rt]=num[l];
            return;
        }
        LL m=Mid;
        Build(lson);
        Build(rson);
        PushUp(rt);
    }

    void UpdateRange(LL L, LL R, LL val, LL l, LL r, LL rt)
    {
        if (L<=l && r<=R)
        {
            _sum[rt]+=val;
            _lazy[rt]+=val;
            return;
        }
        PushDown(rt);
        LL m=Mid;
        if (L<=m) UpdateRange(L,R,val,lson);
        if (R>m) UpdateRange(L,R,val,rson);
        PushUp(rt);
    }

    void UpdateOne(LL pos, LL val, LL l, LL r, LL rt)
    {
        if (l==r && r==pos)
        {
            _sum[rt]=val;
            return;
        }
        LL m=Mid;
        if (pos<=m) UpdateOne(pos,val,lson);
        else UpdateOne(pos,val,rson);
        PushUp(rt);
    }

    LL Query(LL L, LL R, LL l, LL r, LL rt)
    {
        if (L<=l && r<=R)
            return _sum[rt];
        PushDown(rt);
        LL m=Mid;
        LL ans=0;
        if (L<=m) ans+=Query(L,R,lson);
        if (R>m) ans+=Query(L,R,rson);
        return ans;
    }
};

SegTree st;
int main()
{
    return 0;
}
```

### AC自动机

```c++
#include <cstdio>
#include <cstring>
#include <queue>

#define CH 26
#define MAXN 500005
using namespace std;

struct Trie
{
    int next[MAXN][CH], fail[MAXN], end[MAXN];
    int root;
    int tot;
    int newnode()
    {
        for (int i=0;i<CH;i++)
            next[tot][i]=-1;
        end[tot++]=0;
        return tot-1;
    }
    void init()
    {
        tot=0;
        root=newnode();
    }
    void insert(char buf[])
    {
        int len=strlen(buf);
        int now=root;
        for (int i=0;i<len;i++)
        {
            int k=buf[i]-'a';
            if (next[now][k]==-1)
                next[now][k]=newnode();
            now=next[now][k];
        }
        end[now]++;
    }

    void build()
    {
        queue<int> que;
        fail[root]=root;
        for (int i=0;i<CH;i++)
        {
            if (next[root][i]==-1)
                next[root][i]=root;
            else
            {
                fail[next[root][i]]=root;
                que.push(next[root][i]);
            }
        }

        while (!que.empty())
        {
            int now=que.front();
            que.pop();
            for (int i=0;i<CH;i++)
            {
                if (next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else
                {
                    fail[next[now][i]]=next[fail[now]][i];
                    que.push(next[now][i]);
                }
            }
        }
    }

    int query(char buf[])
    {
        int len=strlen(buf);
        int now=root;
        int res=0;
        for (int i=0;i<len;i++)
        {
            now=next[now][buf[i]-'a'];
            int temp=now;
            while (temp!=root)
            {
                res+=end[temp];
                end[temp]=0;
                temp=fail[temp];
            }
        }
        return res;
    }
};
```

### RMQ

```c++
// https://blog.csdn.net/niushuai666/article/details/6624672/

void RMQ1(int num) //预处理->O(nlogn)  
{  
    for(int j = 1; j < 20; ++j)  
        for(int i = 1; i <= num; ++i)  
            if(i + (1 << j) - 1 <= num)  
            {  
                maxsum[i][j] = max(maxsum[i][j - 1], maxsum[i + (1 << (j - 1))][j - 1]);  
                minsum[i][j] = min(minsum[i][j - 1], minsum[i + (1 << (j - 1))][j - 1]);  
            }  
} 

void RMQ(int _n)
{
    int i,j,k;
    for (i=1;i<=_n;i++)
        rmax[i][0]=f[i];
    k=log((double)(_n+1))/log(2.0);
    for (j=1;j<=k;j++)
        for (i=1;i+(1<<j)-1<=_n;i++)
            rmax[i][j]=max(rmax[i][j-1], rmax[i+(1<<(j-1))][j-1]);
}

int rmq_max(int l,int r)
{
    if (l>r)
        return 0;
    int k=log((double)(r-l+1))/log(2.0);
    return max(rmax[l][k], rmax[r-(1<<k)+1][k]);
}
```

## 数论
### 分解质因子

```c++
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

```c++
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

```c++
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

```c++
// 欧拉函数被定义为小于或等于n的数中与n互质的个数
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn=3e6+5;

int get_phi1(int n)
{
    int m=sqrt(n+0.5);
    int ans=n;
    for (int i = 2; i <= m; ++i)
    {
        if (n%i==0)
        {
            ans=ans/i * (i-1);
            while (n%i==0) n/=i;
        }
    }
    if (n>1) ans=ans/n*(n-1);
    return ans;
}

long long phi[maxn];
void get_phi2(int n)
{
    memset(phi,0,sizeof(phi));
    phi[1]=1;
    for (int i = 2; i <= n; ++i)
        if (!phi[i])
        {
            for (int j = i; j <= n; j+=i)
            {
                if (!phi[j]) phi[j]=j;
                phi[j]=phi[j]/i * (i-1);
            }
        }
}

int main()
{
    printf("%d\n", get_phi1(7));
    get_phi2(1000);
    for (int i = 0; i < 20; ++i)
        printf("%lld ", phi[i]);
    printf("\n");
    return 0;
}
```

### 求逆元

```c++
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

```c++
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

const int maxn=1e6+5;
const int maxm=1e7+5;
bool visit[maxm];
int prime1[maxn]; 
// prime1的大小大概估计一下再开数组。大概是（x/lnx）
int pnum; // 素数个数

void getprime1(int n)
{
    memset(visit, false, sizeof(visit));
    int num = 0;
    for (int i = 2; i <= n; ++i)
    {
        if ( !visit[i] )  prime1[num++] = i;
        for (int j = 1; j <= num && i * prime1[j] <= n ;  j++)
        {
            visit[ i  *  prime1[j] ]  =  true;
            if (i % prime1[j] == 0) break; ///此处是重点，避免了很多的重复判断，比如i=9,现在素数是2,3,5,7,进入二重循环，visit[2*9]=1;visit[3*9]=1；这个时候9%3==0，要跳出。因为5*9可以用3*15来代替，如果这个时候计算了，i=15的时候又会被重复计算一次，所以这里大量避免了重复运算。
        }
    }
    pnum = num;
}

bool prime2[maxn+10];

void getprime2(int n)
{
    memset(prime2,1,sizeof(prime2));
    prime2[0]=prime2[1]=0;
    for (int i = 2; i < n; ++i)
    {
        if (prime2[i])
        {
            for (int j = i*i; j < n; j+=i)
                prime2[j]=0;
        }
    }
}

int main()
{
    scanf("%d",&n);
    getprime2(n);
    for (int i = 0; i < n; ++i)
    {
        if (prime2[i])
            printf("%d ", i);
    }
    return 0;
}
```

### 高斯消元法

```c++
#define MAX 110
int N,M;

double a[MAX][MAX],ans[MAX];

inline int sgn(double x) { return (x>eps)-(x<-eps); }

int gauss()
{
    int equ,var; // equ个方程 var个变量
    equ=N*M, var=N*M;
    
    bool free_x[MAX];
    int i,j,k;  
    int max_r; // 当前这列绝对值最大的行.  
    int col; // 当前处理的列.  
    double temp;  
    // 转换为阶梯阵.  
    col=0; // 当前处理的列.  
    memset(free_x,true,sizeof(free_x));  
    for(k=0;k<equ&&col<var;k++,col++)  
    {  
        max_r=k;  
        for(i=k+1;i<equ;i++) //找出当前这列绝对值最大的行
        {  
            if(sgn(fabs(a[i][col])-fabs(a[max_r][col]))>0)  
                max_r=i;  
        }  
        if(max_r!=k)  
        { // 与第k行交换.  
            for(j=k;j<var+1;j++)  
                swap(a[k][j],a[max_r][j]);  
        }  
        if(sgn(a[k][col])==0)  
        { // 说明该col列第k行以下全是0了，则处理当前行的下一列.  
            k--; continue;  
        }  
        for(i=k+1;i<equ;i++)  
        { // 枚举要删去的行，即将第k行以下的第col个变量的系数都变为0  
            if (sgn(a[i][col])!=0)  
            {  
                temp=a[i][col]/a[k][col];  
                for(j=col;j<var+1;j++)  
                {  
                    a[i][j]=a[i][j]-a[k][j]*temp;  
                }  
            }  
        }  
    }  

    for(i=k;i<equ;i++)//此时开始的行的所有变量前面的系数都为0，方程结果应该也为0  
    {   
        if (sgn(a[i][col])!=0)  //如果不为0则说明无解 
            return 0;  
    }  

    if(k<var)//如果存在自由元，自由元个数为var-k   
    {  
        for(i=k-1;i>=0;i--)  
        {  
            int free_x_num=0;  //自由变元的个数
            int free_index;  //自由变元的序号  

            for(j=0;j<var;j++)  
            {  
                if (sgn(a[i][j])!=0&&free_x[j])  
                    free_x_num++,free_index=j;  
            }  
            if(free_x_num>1) continue;  //该行中的不确定的变元的个数超过1个,无法求解,它们仍然为不确定的变元  
            //只有一个不确定的变元free_index,可以求解出该变元,且该变元是确定的
            temp=a[i][var];  
            for(j=0;j<var;j++)  
            {  
                if(sgn(a[i][j])!=0&&j!=free_index)  
                    temp-=a[i][j]*ans[j];  
            }  
            ans[free_index]=temp/a[i][free_index];  
            free_x[free_index]=0;  
        }  
        return var-k;  //返回自由元个数 
    }  

    for (i=var-1;i>=0;i--) //不存在自由元的话 
    {  
        temp=a[i][var];  
        for(j=i+1;j<var;j++)  
        {  
            if(sgn(a[i][j])!=0)  
                temp-=a[i][j]*ans[j];  
        }  
        ans[i]=temp/a[i][i];  
    }  
    return 1;  
}
```

### FFT

```c++
const int maxn = 2e5 + 10;
const double pi = acos(-1);

ll c[maxn];
ll d[maxn];

struct cplx {
    double r, i;
    cplx(double r = 0, double i = 0) : r(r), i(i) {}
    cplx operator + (const cplx &a) const {
        return cplx(r + a.r, i + a.i);
    }
    cplx operator - (const cplx &a) const {
        return cplx(r - a.r, i - a.i);
    }
    cplx operator * (const cplx &a) const {
        return cplx(r * a.r - i * a.i, r * a.i + i * a.r);
    }
} a[maxn << 2], b[maxn << 2];

void rader(cplx *f, int len)
{
    int j = len >> 1;
    for(int i = 1; i < len - 1; i++)
    {
        if(i < j) swap(f[i], f[j]);
        int k = len >> 1;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
}

void FFT(cplx *f, int len, int t)
{
    rader(f, len);
    for(int h = 2; h <= len; h <<= 1)
    {
        cplx wn(cos(- t * 2 * pi / h), sin(- t * 2 * pi / h));
        for(int j = 0; j < len; j += h)
        {
            cplx e(1, 0);
            for(int k = j; k < j + h / 2; k++)
            {
                cplx u = f[k];
                cplx v = e * f[k + h / 2];
                f[k] = u + v;
                f[k + h / 2] = u - v;
                e = e * wn;
            }
        }
    }
    if(t == -1) for(int i = 0; i < len; i++) f[i].r /= len;
}

void Conv(cplx *a, cplx *b, int len)
{
    FFT(a, len, 1);
    FFT(b, len, 1);
    for(int i = 0; i < len; i++) a[i] = a[i] * b[i];
    FFT(a, len, -1);
}
```

### LCM

```c++
int gcd(int a,int b)
{
    return a%b==0?b:gcd(b,a%b);
}

int lcm(int a, int b)
{
    return a*b/gcd(a,b);
}
```

### Lucas

```c++
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

## 其余
### 快速幂

```c++
#define LL long long

LL qpow(LL x,LL y)
{
    LL res = 1;
    while(y){
        if(y&1) res = x * res % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}
```

### 矩阵快速幂

```c++
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

```c++
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

### 快速排序

```c++
void quickSort(char *arr, int left, int right){
    int i = left, j = right;
    char mid = arr[(i+j)/2];
    while(i <= j)
    {
        while(arr[i] < mid) i++;
        while(arr[j] > mid) j--;
        if(i <= j)
        {
            int tmp;
            tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            i ++; j --;
        }
    }
    if(i < right) quickSort(arr,i, right);
    if(left < j) quickSort(arr,left, j);
}
```

### 极角排序

```c++
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

### 区间DP

```c++
// 如果第i件不能重复利用 dp[i][j]=dp[i+1][j]+1;
// 如果在i+1到j中 有和第i件相同的衣服 是否要重复利用 dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]);
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 110
int dp[MAXN][MAXN],cloth[MAXN];
int T,N,ci;
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        for (int Case=1;Case<=T;Case++)
        {
            scanf("%d",&N);
            for (int i=1;i<=N;i++)
                scanf("%d",&cloth[i]);

            for (int i=1;i<=N;i++)
                for (int j=1;j<=N;j++)
                    dp[i][j]=j-i+1;

            // 方式一
            // for (int i=N-1;i>=1;i--)
            //     for (int j=i+1;j<=N;j++)
            //     {
            //         dp[i][j]=dp[i+1][j]+1;
            //         for (int k=i+1;k<=j;k++)
            //             if (cloth[i]==cloth[k])
            //                 dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]);
            //     }

            // 方式二
            for (int l=1;l<=N;l++)
                for (int i=1;i+l<=N;i++)
                {
                    int j=i+l;
                    dp[i][j]=dp[i+1][j]+1;
                    for (int k=i+1;k<=j;k++)
                        if (cloth[k]==cloth[i])
                            dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]);
                }

            printf("Case %d: %d\n", Case,dp[1][N]);
        }
    }
    return 0;
}
```

### 数位DP

```c++

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

```c++
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

```c++
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

```c++
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

```c++
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

```c++
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

```c++
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

```c++
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

### KMP

```c++
void kmp_pre(int n)
{
    int i,j;
    j=nx[0]=-1;
    i=0;
    while (i<n)
    {
        while (j!=-1 && a[i]!=a[j]) j=nx[j];
        nx[++i]=++j;
    }
}

int kmp_count(int n, int m)
{
    prekmp(n);
    int i,j,ans;
    i=j=ans=0;
    while (i<m)
    {
        if (j==-1 || x[j]==y[i])
        {
            i++; j++;
        } else {
            j=nx[j];
        }
        if (j>=n)
        {
            ans++;
            j=nx[j];
        }
    }
    return ans;
}
```

### LCS & LIS

```c++
// 最长公共子序列
const int maxn = 10000;
int dp[maxn];
int a[maxn],b[maxn];
int LCS(int n, int m)
{
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; i++)
    {
        int tmp = 0; // 存 i 确定, 且 a[i] > b[j] 时最大的 dp[j]
        for(int j = 1; j <= m; j++)
        {
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
int LIS(int sign)
{
    fill(dp,dp+maxn,inf);
    int ans = 0;
    for(int i=0;i<n;i++){
        int index = upper_bound(dp,dp+ans,a[i]*sign) - dp;//这个是求不严格的序列，如果要求严格的就用lower_bound
        dp[index] = a[i]*sign;
        ans = max(ans,index+1);
    }
    return ans;
}


int lins()
{
    return LIS(1);// 求上升的
}

int lnds()
{
    return LIS(-1);//求下降的
}
```

### SG函数

```c++
// SG计算方法
// 1.可选步数为1~m的连续整数，直接取模即可，SG(x) = x % (m+1);
// 2.可选步数为任意步，SG(x) = x;
// 3.可选步数为一系列不连续的数，用getSG()计算

//f[]需要从小到大排序
//f[N]:可改变当前状态的方式，N为方式的种类，f[N]要在getSG之前先预处理
//SG[]:0~n的SG函数值
//S[]:为x后继状态的集合
int f[N],SG[MAXN],S[MAXN];
void getSG(int n)
{
    memset(SG,0,sizeof(SG));
    //因为SG[0]始终等于0，所以i从1开始
    for(int i = 1; i <= n; i++)
    {
        //每一次都要将上一状态 的 后继集合 重置
        memset(S,0,sizeof(S));
        for(int j = 0; f[j] <= i && j <= N; j++)
            S[SG[i-f[j]]] = 1;  //将后继状态的SG函数值进行标记
        for(int j = 0;; j++) 
            if(!S[j]) //查询当前后继状态SG值中最小的非零值
            {
                SG[i] = j;
                break;
            }
    }
}


// -------
// 注意 S数组要按从小到大排序 SG函数要初始化为-1 对于每个集合只需初始化1遍  
// n是集合s的大小 S[i]是定义的特殊取法规则的数组 
int s[MAXN];
bool vis[MAXN];
void dfsSG(int x)
{
    if (sg[x]!=-1)
        return sg[x];
    memset(vis,0,sizeof(vis));
    for (int i=1;i<=n;i++)
        if (x>=s[i])
        {
            dfsSG(x-s[i]);
            vis[sg[x-s[i]]]=1;
        }

    for (int i=1;;++i)
        if (!vis[i])
        {
            e=i;
            return sg[x]=i;
        }
}
```

### 点分治

```c++
// https://blog.csdn.net/qq_39553725/article/details/77542223
// 点分治模版题
// 【例题1】【poj1741】tree 
// 给一颗n个节点的树, 每条边上有一个距离v. 定义d(u,v)为u到v的最小距离. 给定k值, 求有多少点对（u, v）使u到v的距离小于等于k.  
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

const int maxn = 10010;
struct Edge
{
    int v,w;
    int next;
} edge[maxn<<1];
int head[maxn];
int sim[maxn]; // sim数组存以i为根节点的子树的节点数量（即子树大小）
int mxson[maxn]; // mxson数组存以i节点为根的子树中的最大子树
bool vis[maxn];
int Smer,MX; // Smer为这棵树（当前处理树）的大小. MX记录当前已经找到的最小 最大子树值.
int root,ans;

int N,K; // N个顶点 树中点对之间距离不超过K的
int cnt;

void add(int u,int v,int w)
{
    edge[cnt].v=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void getroot(int u,int fa)
{
    sim[u] = 1; mxson[u] = 0;
    for(int i = head[u]; i!=-1; i = edge[i].next)
    {
        int v = edge[i].v;
        if(vis[v]||v == fa)continue;
        getroot(v,u);
        sim[u] = sim[u] + sim[v];
        mxson[u] = max(mxson[u],sim[v]);
    }
    mxson[u] = max(mxson[u],Smer - sim[u]); // 使用到了容斥原理的思想(后面还会用到), 求出的是经过父亲节点的子树大小
    if(mxson[u]<MX){root = u; MX = mxson[u];}
}

int dis[maxn],dcnt;
void getdis(int u,int fa,int dist)
{
    dis[++dcnt]=dist;
    for (int i=head[u]; i!=-1; i=edge[i].next)
    {
        int v=edge[i].v;
        if (vis[v]||v==fa) continue;
        getdis(v,u,dist+edge[i].w);
    }
    return;
}

int solve(int sta,int len1)
{
    dcnt=0;
    CLR(dis,0);
    getdis(sta,0,len1);
    sort(dis+1,dis+dcnt+1);
    int L=1,R=dcnt,ret=0;
    while (L<=R) // 二分
    {
        if (dis[R]+dis[L]<=K) 
        {
            ret=ret+R-L;
            L++;
        }
        else
            R--;
    }
    return ret;
}

void Divide(int tr)
{
    ans = ans + solve(tr,0); // 对于当前点, 求解经过此点的所有贡献(solve)
    vis[tr] = true;
    for(int i = head[tr]; i!=-1; i = edge[i].next) // 然后进行分治, 分别处理此点的每一棵子树
    {
        int v = edge[i].v;
        if(vis[v])continue;
        ans = ans - solve(v,edge[i].w); // 容斥原理去除非法答案
        Smer = sim[v]; root = 0;
        MX = INF; getroot(v,0);
        Divide(root);
    }
    return;
}

int main()
{
    while (scanf("%d%d",&N,&K)!=EOF && (N||K))
    {
        int u,v,w;
        cnt=0;
        CLR(head,-1);
        for (int i=0;i<N-1;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);
            add(v,u,w);
        }
        ans=0;
        CLR(vis,0);
        MX=INF; Smer=N; getroot(1,0);
        Divide(root);
        printf("%d\n", ans);
    }
    return 0;
}
```
