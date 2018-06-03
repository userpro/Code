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
#define MAXN 200010

vector<int> G[MAXN];
int n;

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

void solve()
{
    int i;
    Stop=Bcnt=Dindex=0;
    memset(DFN,0,sizeof(DFN));
    for (i=1;i<=n;i++)
        if (!DFN[i])
            Tarjan(i);
}

void _init()
{
    for (int i=0;i<=n;i++)
        G[i].clear();
    CLR(DFN,0);
    CLR(LOW,0);
    CLR(instack,0);
    CLR(Belong,-1);
}

int main(int argc, char const *argv[])
{
    while (scanf("%d",&n)!=EOF)
    {
        _init();
        int a;
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&a);
            if (!a)
            {
                G[i].push_back(a);
                G[a].push_back(i);
            }
        }
        for (int i=1;i<=n;i++)
            if (!DFN[i])
                Tarjan(i);

        int ans=0;
        for (int i=0;i<=n;i++)
            if (Belong[i]!=-1)
                ans++;

        printf("%d\n", ans);
        if (ans==n)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}