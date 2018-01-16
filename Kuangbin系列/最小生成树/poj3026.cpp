#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
#define INF 1<<29
#define MAXN 110
int N,R,C;
bool vis[MAXN];
char A[MAXN][MAXN];
int B[MAXN][MAXN],D[MAXN][MAXN],cost[MAXN][MAXN];
int lowc[MAXN];
int my_move[][2]={{-1,0},{1,0},{0,-1},{0,1}};

void prim(int n)
{
    memset(vis,0,sizeof(vis));
    for (int i = 0; i < n; ++i)
        lowc[i]=INF;

    int ans=0;
    lowc[0]=0;
    for (int i = 0; i < n; ++i)
    {
        int mn=INF,k;
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j]&&mn>lowc[j])
            {
                mn=lowc[j];
                k=j;
            }
        }
        if (mn==INF)
        {
            printf("-1\n");
            return;
        }
        vis[k]=1;
        ans+=mn;
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j]&&lowc[j]>cost[k][j])
                lowc[j]=cost[k][j];
        }
    }
    printf("%d\n", ans);
}


void bfs(int sx,int sy)
{
    memset(D,-1,sizeof(D));
    D[sx][sy]=0;
    queue<pair<int,int> > que;
    while (!que.empty()) que.pop();
    que.push(make_pair(sx,sy));
    while (!que.empty())
    {
        pair<int,int> t=que.front(); que.pop();
        if (B[t.first][t.second]!=-1)
            cost[B[sx][sy]][B[t.first][t.second]]=D[t.first][t.second];
        for (int i = 0; i < 4; ++i)
        {
            int tx=t.first+my_move[i][0], ty=t.second+my_move[i][1];
            if (ty>=R||tx>=C||tx<0||ty<0||A[tx][ty]=='#'||D[tx][ty]!=-1) continue;
            D[tx][ty]=D[t.first][t.second]+1;
            que.push(make_pair(tx,ty));
        }
    }
}

int main()
{
    scanf("%d",&N);
    while (N--)
    {
        scanf("%d%d",&C,&R);
        gets(A[0]); // 注意poj的discuss
        for (int i = 0; i < R; ++i)
            gets(A[i]);

        memset(B,-1,sizeof(B));
        int cnt=0;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (A[i][j]=='A'||A[i][j]=='S')
                    B[i][j]=cnt++;

        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (B[i][j]!=-1)
                    bfs(i,j);

        prim(cnt);
    }
    return 0;
}