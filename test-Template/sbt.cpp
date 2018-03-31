/**************************************************************
    Problem: 2733
    User: fox_pro
    Language: C++
    Result: Accepted
    Time:1696 ms
    Memory:8304 kb
****************************************************************/
 
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int maxn = 200000 + 2;
 
#define l 0
#define r 1
struct node
{
    node *ch[2];
    int v;
    int size;
    node(){}
    node(int v, node *lc, node *rc)
        : v(v), size(1) {ch[l] = lc; ch[r] = rc;}
}nil[maxn], *stack[maxn], *rt[maxn];
int sp = 0;
void init()
{
    nil->ch[l] = nil->ch[r] = nil;
    nil->size = 0;
    for (int i = 1; i < maxn; i++) stack[++sp] = nil + i;
}
node *newnode(int v)
{
    return new (stack[sp--]) node(v, nil, nil);
}
void deletenode(node *x)
{
    stack[++sp] = x;
}
void rotate(node*&x, bool d)
{
    node *t = x->ch[d];
    x->ch[d] = t->ch[!d];
    t->ch[!d] = x;
    t->size = x->size;
    x->size = x->ch[l]->size + x->ch[r]->size + 1;
    x = t;
}
void maintain(node*&x, bool d)
{
    if (x->ch[d] == nil) return;
    if (x->ch[d]->ch[d]->size > x->ch[!d]->size)
        rotate(x, d);
    else
    if (x->ch[d]->ch[!d]->size > x->ch[!d]->size)
        rotate(x->ch[d], !d), rotate(x, d);
    else
        return;
    maintain(x->ch[l], l); maintain(x->ch[r], r);
    maintain(x, l); maintain(x, r);
}
void insert(node* &x, int v)
{
    if (x == nil)
    {
        x = newnode(v);
        return;
    }
    x->size++;
    insert(x->ch[v >= x->v], v);
    maintain(x, v >= x->v);
}
void merge(node* &x, node* y)
{
    if (y->ch[l] != nil) merge(x, y->ch[l]);
    if (y->ch[r] != nil) merge(x, y->ch[r]);
    if (y == nil) return;
    insert(x, y->v);
    deletenode(y);
}
int select(node* x, int rk)
{
    int t = x->ch[l]->size + 1;
    if (rk == t) return x->v;
    if (rk < t) return select(x->ch[l], rk);
    else return select(x->ch[r], rk - t);
}
 
int p[maxn];
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}
 
void midorder(node *x)
{
    if (x == nil) return;
    midorder(x->ch[l]);
    printf("%d ", x->v);
    midorder(x->ch[r]);
}
 
int rank[maxn], num[maxn];
int main()
{
    //freopen("neverland.in", "r", stdin);
    //freopen("neverland.out", "w", stdout);
 
    init();
    int n, m, q;
    scanf("%d%d", &n, &m);
         
    for (int i = 1; i <= n; i++) scanf("%d", rank + i);
    for (int i = 1; i <= n; i++) rt[i] = newnode(rank[i]);
    for (int i = 1; i <= n; i++) num[rank[i]] = i;
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        x = find(x); y = find(y);
        if (x == y) continue;
        if (rt[x]->size < rt[y]->size) swap(x, y);
        merge(rt[x], rt[y]);
        p[y] = x;
    }
     
    scanf("%d\n", &q);
    for (int i = 1; i <= q; i++)
    {
        int x, y;
        char c;
        scanf("%c%d%d\n", &c, &x, &y);
        if (c == 'Q')
        {
            x = find(x);
            if (rt[x]->size < y)
                printf("-1\n");
            else
                printf("%d\n", num[select(rt[x], y)]);
        }
        else
        {
            x = find(x); y = find(y);
            if (x == y) continue;
            if (rt[x]->size < rt[y]->size) swap(x, y);
            merge(rt[x], rt[y]);
            p[y] = x;
        }
    }
     
    //fclose(stdin); fclose(stdout);
    return 0;
}
