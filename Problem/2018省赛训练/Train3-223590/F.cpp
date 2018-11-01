// 先dfs遍历, 得到这棵树的dfs序列, 并且记录每个结点的子孙(包括自己)的起始和结束位置, 以及每个结点的深度. 则对于1操作: v的每个子孙结点的变化情况为a[i] += x – (deep[i] – deep[v])* k;
 // 其中x + k * deep[v]对所有结点贡献相同,而deep[i] * k对每个结点的贡献度取决于结点i的深度. 所以可以用线段树, 对于每次操作一,所有v的子孙结点都加上x + k * deep[v], 然后对于deep[i] * k每次记录k, 到最后更新的时候再乘以结点的深度即可.
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
typedef long long ll;
const int maxn = 3 * 1e5 + 10;
const ll mod = 1e9 + 7;
using namespace std;

vector<int> G[maxn];
int node[maxn], id1[maxn], id2[maxn], dep[maxn];
ll xx[maxn << 2], kk[maxn << 2];
int k, n;

int Scan()
{
    int res = 0, ch, flag = 0;
    if((ch = getchar()) == '-')
        flag = 1;
    else if(ch >= '0' && ch <= '9')
        res = ch - '0';
    while((ch = getchar()) >= '0' && ch <= '9' )
        res = res * 10 + ch - '0';
    return flag ? -res : res;
}

ll Scan_l()
{
    ll res = 0;
    int ch, flag = 0;
    if((ch = getchar()) == '-')
        flag = 1;
    else if(ch >= '0' && ch <= '9')
        res = ch - '0';
    while((ch = getchar()) >= '0' && ch <= '9' )
        res = res * 10 + ch - '0';
    return flag ? -res : res;
}

void dfs(int u, int fa, int d) {
    node[k] = u;
    id1[u] = id2[u] = k;
    dep[k++] = d;
    for(int i = 0; i < G[u].size(); i++) {
        ll v = G[u][i];
        if(v == fa) continue;
        dfs(v, u, d + 1);
    }
    id2[u] = k - 1;
}

void pushdown(int rt) {
    xx[rt << 1] += xx[rt];
    xx[rt << 1] %= mod;
    xx[rt << 1 | 1] += xx[rt];
    xx[rt << 1 | 1] %= mod;
    kk[rt << 1] += kk[rt];
    kk[rt << 1] %= mod;
    kk[rt << 1 | 1] += kk[rt];
    kk[rt << 1 | 1] %= mod;
    xx[rt] = 0; kk[rt] = 0;
}

void update(int L, int R, int l, int r, int rt, ll c, ll d) {
    if(L <= l && r <= R) {
        xx[rt] = ((xx[rt] + c) % mod + mod) % mod;
        kk[rt] = ((kk[rt] + d) % mod + mod) % mod;
        return ;
    }
    pushdown(rt);
    int m = (l + r) / 2;
    if(L <= m) update(L, R, l, m, rt << 1, c, d);
    if(m < R) update(L, R, m + 1, r, rt << 1 | 1, c, d);
}

ll query(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) {
        return xx[rt] + dep[L] * kk[rt];
    }
    pushdown(rt);
    int m = (l + r) / 2;
    if(R <= m) return query(L, R, l, m, rt << 1);
    else return query(L, R, m + 1, r, rt << 1 | 1);
}

int main() {
    int t, g, q;
    t = Scan();
    while(t--) {
        k = 1;
        memset(xx, 0, sizeof xx);
        memset(kk, 0, sizeof kk);
        for(int i = 0; i < maxn; i++) G[i].clear();
        n = Scan();
        for(int i = 2; i <= n; i++) {
            g = Scan();
            G[g].push_back(i);
        }
        dfs(1, 0, 1);
        q = Scan();
        while(q--) {
            int op, root;
            ll x, y;
            op = Scan();
            if(op == 1) {
                root = Scan();
                x = Scan_l();
                y = Scan_l();
                update(id1[root], id2[root], 1, n, 1, x + dep[id1[root]] * y, -y);
            }
            if(op == 2) {
                root = Scan();
                printf("%I64d\n", (query(id1[root], id1[root], 1, n, 1) % mod + mod) % mod);
            }
        }
    }
    return 0;
}


// TLE
// #include <cstdio>
// #include <cstring>
// #include <algorithm>
// #include <queue>
// #include <vector>
// #include <map>
// #include <iostream>
// using namespace std;
// #define INF (1<<29)
// #define LL long long
// #define CLR(a,b) memset(a,b,sizeof(a))

// #define Mid ((l+r)>>1)
// #define lson l,m,rt<<1
// #define rson m+1,r,rt<<1|1

// #define MOD 1000000007
// #define MAXN 300010
// vector<int> G[MAXN];
// int T,n,q;
// int tot,deep;
// int st[MAXN],ed[MAXN],dep[MAXN],id[MAXN];
// LL kk[MAXN<<2],xx[MAXN<<2];

// void dfs(int u,int fa)
// {
//     tot++;
//     dep[u]=deep;
//     st[u]=tot;
//     deep++;
//     int sz=G[u].size();
//     for (int i=0;i<sz;i++)
//     {
//         if (G[u][i]!=fa)
//             dfs(G[u][i],u);
//     }
//     deep--;
//     ed[u]=tot;
// }

// void PushDown(int rt)
// {
//     xx[rt << 1] += xx[rt];  
//     xx[rt << 1] %= MOD;  
//     xx[rt << 1 | 1] += xx[rt];  
//     xx[rt << 1 | 1] %= MOD;  
//     kk[rt << 1] += kk[rt];  
//     kk[rt << 1] %= MOD;  
//     kk[rt << 1 | 1] += kk[rt];  
//     kk[rt << 1 | 1] %= MOD;  
//     xx[rt] = 0; kk[rt] = 0;  
// }

// void UpdateRange(LL L, LL R, LL c, LL k, LL l, LL r, LL rt)
// {
//     if (L<=l && r<=R)
//     {
//         xx[rt]=((xx[rt]+c)%MOD+MOD)%MOD;
//         kk[rt]=((kk[rt]+k)%MOD+MOD)%MOD;
//         return;
//     }
//     PushDown(rt);
//     LL m=Mid;
//     if (L<=m) UpdateRange(L,R,c,k,lson);
//     if (R>m) UpdateRange(L,R,c,k,rson);
// }

// LL Query(LL L, LL R, LL l, LL r, LL rt)
// {
//     if (L<=l && r<=R)
//         return xx[rt]+dep[L]*kk[rt];
//     PushDown(rt);
//     LL m=Mid;
//     if (R<=m) return Query(L,R,lson);
//     else return Query(L,R,rson);
// }

// int main()
// {
//     while (scanf("%d",&T)!=EOF)
//     {
//         while (T--)
//         {
//             CLR(xx,0); CLR(kk,0);
//             tot=0; deep=1;
//             scanf("%d",&n);
//             for (int i=0;i<=n;i++) G[i].clear();
//             int a;
//             for (int i=2;i<=n;i++)
//             {
//                 scanf("%d",&a);
//                 G[a].push_back(i);
//             }
//             dfs(1,0);

//             scanf("%d",&q);
//             LL rt,x,y;
//             for (int i=0;i<q;i++)
//             {
//                 scanf("%d",&a);
//                 if (a==1)
//                 {
//                     scanf("%lld%lld%lld",&rt,&x,&y);
//                     UpdateRange(st[rt],ed[rt],x+dep[st[rt]]*y,-y,1,n,1);
//                 } else if (a==2)
//                 {
//                     scanf("%lld",&rt);
//                     printf("%lld\n", (Query(st[rt],st[rt],1,n,1)%MOD+MOD)%MOD);
//                 }
//             }
//         }
//     }
//     return 0;
// }