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