#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>

using namespace std;
#define MAXN 110
#define INF 1<<29
struct Node
{
    int x,y,c;
    struct Node *pre;
    friend bool operator< (Node a,Node b)
    {
        return a.c>b.c;
    }
}node[MAXN][MAXN];
int N,M;
char C[MAXN][MAXN];
int my_move[][2]={{1,0},{-1,0},{0,1},{0,-1}};
bool vis[MAXN][MAXN];

bool judge(int tx,int ty)
{
    if (tx<0||ty<0||tx>=N||ty>=M||C[tx][ty]=='X'||vis[tx][ty])
        return 1;
    return 0;
}

void bfs()
{
    memset(vis,0,sizeof(vis));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            node[i][j].x=i; node[i][j].y=j; node[i][j].c=INF;
            node[i][j].pre=NULL;
        }
    }

    priority_queue<Node> q;
    if (N==0||M==0)
    {
        printf("God please help our poor hero.\n");
        printf("FINISH\n");
        return;
    }
    if (C[N-1][M-1]>='1'&&C[N-1][M-1]<='9')
        node[N-1][M-1].c=C[N-1][M-1]-'0';
    else
        node[N-1][M-1].c=0;
    node[N-1][M-1].pre=NULL;
    vis[N-1][M-1]=1;
    q.push(node[N-1][M-1]);
    while (!q.empty())
    {
        Node t=q.top(); q.pop();
        if (t.x==0&&t.y==0) break;
        for (int i = 0; i < 4; ++i)
        {
            int tx=t.x+my_move[i][0],ty=t.y+my_move[i][1];
            if (judge(tx,ty)) continue;
            int dis=0;
            if (C[tx][ty]>='1'&&C[tx][ty]<='9')
                dis=node[t.x][t.y].c+C[tx][ty]-'0'+1;
            else
                dis=node[t.x][t.y].c+1;

            if (node[tx][ty].c>dis)
            {
                node[tx][ty].c=dis;
                node[tx][ty].pre=&node[t.x][t.y];
            }
            vis[tx][ty]=1;
            q.push(node[tx][ty]);
        }
    }
    if (node[0][0].c!=INF)
    {
        printf("It takes %d seconds to reach the target position, let me show you the way.\n", node[0][0].c);
        Node *t=&node[0][0];
        int cnt=0;
        while (t)
        {
            if (t->pre)
            {
                printf("%ds:(%d,%d)->(%d,%d)\n", ++cnt,t->x,t->y,t->pre->x,t->pre->y);
                if (C[t->pre->x][t->pre->y]>='0'&&C[t->pre->x][t->pre->y]<='9')
                {
                    int tmp=C[t->pre->x][t->pre->y]-'0';
                    for (int i = 0; i < tmp; ++i)
                        printf("%ds:FIGHT AT (%d,%d)\n", ++cnt,t->pre->x,t->pre->y);
                }
            }
            t=t->pre;
        }
    } else {
        printf("God please help our poor hero.\n");
    }
    
    printf("FINISH\n");
}

int main()
{
    while (scanf("%d%d",&N,&M)!=-1)
    {
        for (int i = 0; i < N; ++i)
            scanf("%s",C[i]);
        bfs();
    }
    return 0;
}