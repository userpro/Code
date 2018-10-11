#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cmath>
using namespace std;

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

int n,m,s;
int tot;
struct node{int v,nxt;}E[1000010];
int head[1000010];
int fa[5000010][25];
int dep[1000010];

void add(int u,int v)
{
    E[++tot].nxt=head[u];
    E[tot].v=v;
    head[u]=tot;
}

void dfs(int u,int pa)
{
    dep[u]=dep[pa]+1;
    fa[u][0]=pa;
    for(int i=head[u];i;i=E[i].nxt)
    {
        int v=E[i].v;
        if(v!=pa) dfs(v,u);
    }
}

int lca(int x,int y)
{
    if(dep[x]-dep[y]<0) swap(x,y);//将u设为深度较深的结点
    int d=dep[x]-dep[y];

    for(int i=0;(1<<i)<=d;i++)
    if( (1<<i) & d ) x=fa[x][i];//抬升

    if(x==y) return x;//抬升后x==y，则其LCA就是y(或此时的x)
    else 
    {
        for(int i=(int)log(n);i>=0;i--)
        {
            if(fa[x][i]!=fa[y][i])
            {
                x=fa[x][i];
                y=fa[y][i];
            }
        }
        return fa[x][0];
    }
}

int main()
{
    n=read();m=read();s=read();
    for(int i=1;i<=n-1;i++)
    {
        int x=read(),y=read();
        add(x,y);add(y,x);
    }

    dfs(s,-1);
    //无根树转有根树，在这里调用是pa要设为-1

    //预处理fa数组
    for(int i=1;(1<<i)<=n;i++)
    for(int u=1;u<=n;u++)
    fa[u][i]=fa[ fa[u][i-1] ][i-1];

    while(m--)
    {
        int x=read(),y=read();
        int ans=lca(x,y);
        print(ans); printf("\n");
    }
    return 0;
} 

// ---------------------

// 本文来自 niiick 的CSDN 博客 ，全文地址请点击：https://blog.csdn.net/niiick/article/details/79333252?utm_source=copy 