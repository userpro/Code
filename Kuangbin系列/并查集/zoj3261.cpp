/*
带权并查集
离线反向执行
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>

using namespace std;
#define MAXN 10010
#define MAXM 20010
#define MAXQ 50010
struct Edge
{
    int u,v;
}edge[MAXM];
struct Cmd
{
    int ty,u,v;
}cmd[MAXQ];
int N,M,Q;
int F[MAXN];
int power[MAXN],num[MAXN],inx[MAXN];
int ans[MAXQ];
bool used[MAXM];
map<int, int> mp[MAXN];

int findd(int x)
{
    if (-1==F[x]) return x;
    return F[x]=findd(F[x]);
}

void unionn(int x,int y)
{
    int a=findd(x),b=findd(y);
    if (a!=b)
    {
        F[a]=b;
        if (num[a]>num[b])
        {
            inx[b]=inx[a];
            num[b]=num[a];
        }
        else if (num[a]==num[b]&&inx[b]>inx[a])
            inx[b]=inx[a];
    }
}

int main()
{
    char str[30];
    bool first=1;
    while (scanf("%d",&N)==1)
    {
        if (first) first=0;
        else printf("\n");
        memset(F,-1,sizeof(F));
        memset(used,1,sizeof(used));
        memset(ans,0,sizeof(ans));

        for (int i = 0; i < N; ++i)
        {
            scanf("%d",&power[i]);
            inx[i]=i;
            num[i]=power[i];
            mp[i].clear();
        }
        scanf("%d",&M);
        int u,v;
        for (int i = 0; i < M; ++i)
        {
            scanf("%d%d",&u,&v);
            if (u>v) swap(u,v);
            edge[i].u=u; edge[i].v=v;
            mp[u][v]=i;
        }
        scanf("%d",&Q);
        for (int i = 0; i < Q; ++i)
        {
            scanf("%s%d",str,&u);
            if (str[0]=='q')
                cmd[i].ty=1, cmd[i].u=u, cmd[i].v=-1;
            else
            {
                scanf("%d",&v);
                if (u>v) swap(u,v);
                cmd[i].ty=2, cmd[i].u=u, cmd[i].v=v;
                used[mp[u][v]]=0;
            }
        }
        for (int i = 0; i < M; ++i)
        {
            if (used[i])
                unionn(edge[i].u,edge[i].v);
        }
        int cnt=0;
        for (int i = Q-1; i>=0; --i)
        {
            if (cmd[i].ty==2)
            {
                unionn(cmd[i].u,cmd[i].v);
            }
            else
            {
                int t=findd(cmd[i].u);
                if (num[t]>power[cmd[i].u])
                    ans[cnt++]=inx[t];
                else
                    ans[cnt++]=-1;
            }
        }
        for (int i = cnt-1; i >=0; --i)
            printf("%d\n", ans[i]);
    }
    return 0;
}