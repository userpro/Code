const int maxn=5010;
// Belong 数组存强连通分量
vector<int> G[maxn];
int DFN[maxn],LOW[maxn],Stap[maxn],Belong[maxn];
bool instack[maxn];
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
    for (int i=0;i<maxn;i++) G[i].clear();
    memset(DFN,0,sizeof(DFN));
    memset(LOW,0,sizeof(LOW));
    memset(instack,0,sizeof(instack));
    memset(Belong,-1,sizeof(Belong));
}

void solve(int n)
{
    int i;
    Stop=Bcnt=Dindex=0;
    memset(DFN,0,sizeof(DFN));
    for (i=1;i<=n;i++)
        if (!DFN[i])
            Tarjan(i);
}