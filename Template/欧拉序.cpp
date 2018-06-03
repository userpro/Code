vector<int> g[40010];
int len_a,a[80020],len_b,b[80020];

// dfs(1,0)
void dfs(int u,int fa)
{
    a[++len_a]=u; 
    b[++len_b]=u;
    int sz=g[u].size();
    for(int i=0; i<sz; i++)
    {
        if(g[u][i]!=fa)
        {
            dfs(g[u][i],u);
            a[++len_a]=u; // dfs到加进, dfs回加进, 总共加入度遍 --- 欧拉序 1
        }
    }
    b[++len_b]=u; // dfs进加进, dfs最后一次回加进, 总共加两遍 --- 欧拉序 2
}

/*
用处:
    1. 求LCA
    2. 求子树的权值之和
*/