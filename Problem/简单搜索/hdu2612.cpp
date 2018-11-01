#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
#define MAX 210
typedef struct _pos
{
    int x, y;
}pos;
bool vis[MAX][MAX];
char cmp[MAX][MAX];
int mp1[MAX][MAX], mp2[MAX][MAX];
int N, M, i, j, k;
char c;
pos Y, Mi, K;

void update(int x, int y, pos &p, queue<pos> &q, int mp[MAX][MAX])
{
    if (!vis[x][y] && mp[x][y] != -1)
    {
        pos e;
        vis[x][y] = 1;
        mp[x][y] = mp[p.x][p.y] + 1;
        e.x = x; e.y = y;
        q.push(e);
    }
}

void bfs(pos p, int mp[MAX][MAX])
{
    memset(vis, 0, sizeof(vis));
    pos s;
    queue<pos> q;
    q.push(p);
    while (!q.empty())
    {
        s = q.front();
        if (s.x-1>=0)
            update(s.x-1, s.y, s, q, mp);
        if (s.x+1<N)
            update(s.x+1, s.y, s, q, mp);
        if (s.y-1>=0)
            update(s.x, s.y-1, s, q, mp);
        if (s.y+1<M)
            update(s.x, s.y+1, s, q, mp);
        q.pop();
    }
}

int main()
{
    while (scanf("%d %d", &N, &M) != EOF && N)
    {
        pos t;
        queue<pos> kfc;
        memset(mp1, 0, sizeof(mp1));
        memset(mp2, 0, sizeof(mp2));
        for (i = 0; i < N; ++i)
        {
            getchar();
            for (j = 0; j < M; ++j)
            {
                scanf("%c", &c);
                cmp[i][j] = c;
                if (c == 'Y')
                {
                    Y.x = i; Y.y = j;
                } else if (c == 'M')
                {
                    Mi.x = i; Mi.y = j;
                } else if (c == '@')
                {
                    K.x = i; K.y = j;
                    kfc.push(K);
                } else if (c == '#')
                {
                    mp1[i][j] = -1;
                    mp2[i][j] = -1;
                }
            }
        }

        bfs(Y, mp1);
        bfs(Mi, mp2);

        k = 1<<20;
        while (!kfc.empty())
        {
            t = kfc.front();
            if (k > mp1[t.x][t.y] + mp2[t.x][t.y] && mp1[t.x][t.y] + mp2[t.x][t.y] != 0)
                k = mp2[t.x][t.y] + mp1[t.x][t.y];
            kfc.pop();
        }

        printf("%d\n", k*11);
    }
    return 0;
}