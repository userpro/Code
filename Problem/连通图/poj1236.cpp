#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
#define MAXN 110
struct Edge
{
    int v;
    int next;
} E[MAXN*MAXN];
int head[MAXN*MAXN];

int DFN[MAXN], LOW[MAXN];
int stk[MAXN];
int color[MAXN];
bool instack[MAXN];
int n,n1,Eindex,Bcnt,Stop,Dindex;

void add(int u, int v)
{
    E[Eindex].v=v;
    E[Eindex].next=head[u];
    head[u]=Eindex++;
}

void tarjan(int u)
{
    if (DFN[u])
        return;

    DFN[u]=LOW[u]=++Dindex;
    instack[u]=true;
    stk[++Stop]=u;
    for (int i=head[u]; i!=-1; i=E[i].next)
    {
        int v=E[i].v;
        if (!DFN[v])
        {
            tarjan(v);
            LOW[u]=min(LOW[u],LOW[v]);
        } else if (instack[v])
        {
            LOW[u]=min(LOW[u],DFN[v]);
        }
    }
    if (DFN[u]==LOW[u])
    {
        int v;
        Bcnt++;
        do {
            v=stk[Stop--];
            instack[v]=false;
            color[v]=Bcnt;
        } while (u!=v);
    }
}

int in[MAXN], out[MAXN];
int main()
{
    while (scanf("%d",&n)!=EOF)
    {
        memset(DFN,0,sizeof(DFN));
        memset(LOW,0,sizeof(LOW));
        memset(instack,false,sizeof(instack));
        memset(color,0,sizeof(color));
        memset(head,-1,sizeof(head));
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        Eindex=Bcnt=Stop=Dindex=0;
        for (int i=1;i<=n;i++)
        {
            while (scanf("%d",&n1) && n1)
                add(i,n1);
        }
        for (int i=1; i<=n; i++)
            if (!DFN[i])
                tarjan(i);

        for (int i=1;i<=n;i++)
        {
            for (int j=head[i];j!=-1;j=E[j].next)
            {
                int v=E[j].v;
                if (color[v]!=color[i])
                {
                    in[color[v]]++;
                    out[color[i]]++;
                }
            }
        }

        int ans1=0,ans2=0;
        for (int i=1;i<=Bcnt;i++)
        {
            if (!in[i]) ans1++;
            if (!out[i]) ans2++;
        }

        if (Bcnt==1) printf("1\n0\n");
        else printf("%d\n%d\n", ans1, max(ans1,ans2));
    }
    return 0;
}