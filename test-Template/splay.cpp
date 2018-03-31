/**************************************************************
    Problem: 1036
    User: fox_pro
    Language: C++
    Result: Accepted
    Time:3048 ms
    Memory:2712 kb
****************************************************************/
 
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 30000 + 10;
template<class T> inline void gmax(T &a, T b){if (a < b) a = b;}
const int l = 0, r = 1;
struct node
{
    int key, v, sum, mx;
    node *ch[2], *p;
    bool dir(){ return p->ch[r] == this; }
    bool isroot(){ return !p || (p->ch[l] != this && p->ch[r] != this); }
    void pushup()
    {
        sum = mx = v;
        if (ch[l]) sum += ch[l]->sum, gmax(mx, ch[l]->mx);
        if (ch[r]) sum += ch[r]->sum, gmax(mx, ch[r]->mx);
    }
    void rotate()
    {
        bool d = dir();
        node *x = p, *y = x->p;
        if (x->ch[d] = ch[!d]) ch[!d]->p = x;
        ch[!d] = x; x->p = this;
        if (p = y)
        {
            if (y->ch[l] == x) y->ch[l] = this;
            if (y->ch[r] == x) y->ch[r] = this;
        }
        x->pushup();
    }
} tree[maxn], *sp = tree + 1;
 
node* newnode(int v)
{
    sp->ch[l] = sp->ch[r] = sp->p = NULL;
    sp->sum = sp->mx = sp->v = v;
    return sp++;
}
 
void splay(node *x)
{
    while (!x->isroot())
    {
        if (x->p->isroot())
            x->rotate();
        else
            if (x->dir() == x->p->dir())
                x->p->rotate(), x->rotate();
            else
                x->rotate(), x->rotate();
    }
    x->pushup();
}
 
node* expose(node* x)
{
    node *t = NULL;
    for ( ; x; x = x->p)
    {
        splay(x);
        x->ch[r] = t;
        (t = x)->pushup();
    }
    return t;
}
 
struct arc
{
    int e;
    arc *pre;
    arc(){}
    arc(int e, arc *pre)
        : e(e), pre(pre){}
} *head[maxn], mem[maxn * 2], *sp2 = mem;
inline void addarc(int x, int y)
{
    head[x] = new (sp2++) arc(y, head[x]);
    head[y] = new (sp2++) arc(x, head[y]);
}
 
queue<int> que;
bool vis[maxn];
void bfs()
{
    que.push(1); vis[1] = true; tree[1].key = 1;
    while (!que.empty())
    {
        int x = que.front(); que.pop();
        for (arc *p = head[x]; p; p = p->pre)
            if (!vis[p->e])
            {
                que.push(p->e);
                vis[p->e] = true;
                tree[p->e].p = &tree[x];
                tree[p->e].key = tree[x].key + 1;
            }
    }
}
 
char cmd[20];
int x, y, n, m;
 
int main()
{
    //freopen("count.in", "r", stdin);
    //freopen("count.out", "w", stdout);
 
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d%d", &x, &y), addarc(x, y);
    for (int i = 1; i <= n; i++)
        scanf("%d", &x), newnode(x);
    bfs();
     
    scanf("%d\n", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s%d%d\n", cmd, &x, &y);
        if (cmd[0] == 'C')
        {
            splay(&tree[x]);
            tree[x].v = y; tree[x].pushup();
        }
        else
        if (cmd[1] == 'S')
        {
            if (tree[x].key < tree[y].key) swap(x, y);
            int ans = 0; node *lca;
            expose(&tree[x]);
            ans += (lca = expose(&tree[y]))->v;
            if (lca->ch[r]) ans += lca->ch[r]->sum;
            if (x != y) splay(&tree[x]), ans += tree[x].sum;
            printf("%d\n", ans);
        }
        else
        {
            if (tree[x].key < tree[y].key) swap(x, y);
            int ans = -0x7fffffff; node *lca;
            expose(&tree[x]);
            ans = (lca = expose(&tree[y]))->v;
            if (lca->ch[r]) gmax(ans, lca->ch[r]->mx);
            if (x != y) splay(&tree[x]), gmax(ans, tree[x].mx);
            printf("%d\n", ans);
        }
    }
     
    //fclose(stdin); fclose(stdout);
    return 0;
}
