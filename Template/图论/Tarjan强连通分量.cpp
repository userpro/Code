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