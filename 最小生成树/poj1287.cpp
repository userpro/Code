#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
#define MAXN 110
#define INF 1<<28
struct Node
{
    int v,c;
    Node(int _v,int _c):v(_v),c(_c){}
};
int P,R;
int dist[MAXN][MAXN];
bool vis[MAXN];

struct cmp
{
    bool operator ()(Node n1, Node n2)
    {
        return n1.c>n2.c;
    }
};

int main()
{
    int u,v,c;
    while (scanf("%d%d",&P,&R)==2&&P)
    {
        memset(vis,0,sizeof(vis));
        for (int i = 0; i < MAXN; ++i)
            for (int j = 0; j < MAXN; ++j)
                dist[i][j]=INF;
        for (int i = 0; i < R; ++i)
        {
            scanf("%d%d%d",&u,&v,&c);
            dist[v][u]=dist[u][v]=dist[u][v]>c?c:dist[u][v];
        }

        int ans=0;
        priority_queue<Node,vector<Node>,cmp> edge;
        queue<int> que;
        que.push(P);
        vis[P]=1;
        while (!que.empty())
        {
            int t=que.front(); que.pop();
            for (int i = 0; i < MAXN; ++i)
                if (dist[t][i]!=INF && !vis[i])
                    edge.push(Node(i,dist[t][i]));

            while (!edge.empty())
            {
                Node tmp=edge.top(); edge.pop();
                if (!vis[tmp.v])
                {
                    que.push(tmp.v);
                    vis[tmp.v]=1;
                    ans+=tmp.c;
                    break;
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}