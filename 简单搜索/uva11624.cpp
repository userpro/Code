#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

#define MAX 1001
char mp[MAX][MAX];
bool wall[MAX][MAX], visit1[MAX][MAX], visit2[MAX][MAX];
int dis[MAX][MAX];
pair<int, int> t, Joe;
int T, R, C;

void update(pair<int, int> &p1, pair<int, int> p2, queue<pair<int, int> > &q, int t)
{
    if (wall[p2.first][p2.second] != 0) return;
    if (t == 1)
    {
        if (!visit1[p2.first][p2.second])
        {
            wall[p2.first][p2.second] = t;
            visit1[p2.first][p2.second] = 1;
            q.push(p2);
        }
    } else if (t == 0)
    {
        if (!visit2[p2.first][p2.second])
        {
            visit2[p2.first][p2.second] = 1;
            if (dis[p1.first][p1.second] + 1 < dis[p2.first][p2.second])
                dis[p2.first][p2.second] = dis[p1.first][p1.second] + 1;
            q.push(p2);
        }
    }
}

void bfs(pair<int, int> &p, queue<pair<int, int> > &q, int t)
{
    int a, b;
    a = p.first; b = p.second;
    if (a-1 >= 0)
        update(p,make_pair(a-1, b),q,t);
    if (a+1 < R)
        update(p,make_pair(a+1, b),q,t);
    if (b-1 >= 0)
        update(p,make_pair(a, b-1),q,t);
    if (b+1 < C)
        update(p,make_pair(a, b+1),q,t);
}

int main()
{
    int i, j, k, flag, m;
    while (scanf("%d", &T) != EOF && T)
    {
        for (i = 0; i < T; ++i)
        {
            flag = 1;
            memset(wall, 0, sizeof(wall));
            memset(mp, 0, sizeof(mp));
            memset(visit1, 0, sizeof(visit1));
            memset(visit2, 0, sizeof(visit2));
            memset(dis, 0x7f, sizeof(dis));
            queue<pair<int, int> > q1, q11, q2, q22;
            scanf("%d %d", &R, &C);
            for (j = 0; j < R; ++j)
            {
                getchar();
                for (k = 0; k < C; ++k)
                {
                    scanf("%c", &mp[j][k]);
                    if (mp[j][k] == '#') wall[j][k] = 1;
                    else if (mp[j][k] == 'J')
                    {
                        Joe.first = j;
                        Joe.second = k;
                    } else if (mp[j][k] == 'F')
                    {
                        wall[j][k] = 1;
                        visit1[j][k] = 1;
                        q1.push(make_pair(j, k));
                    }
                }
            }

            q2.push(Joe);
            visit2[Joe.first][Joe.second] = 1;
            dis[Joe.first][Joe.second] = 0;
            while (flag && (!q1.empty() || !q2.empty()))
            {
                while (!q1.empty())
                {
                    t = q1.front();
                    bfs(t, q11, 1);
                    q1.pop();
                }
                swap(q1, q11);
                while (!q2.empty())
                {
                    t = q2.front();
                    bfs(t, q22, 0);
                    if (t.first == R-1 || t.first == 0 || t.second == C-1 || t.second == 0)
                        flag = 0;
                    q2.pop();
                }
                swap(q2, q22);
            }

            if (!flag)
                printf("%d\n", dis[t.first][t.second]+1);
            else
                printf("IMPOSSIBLE\n");
        }
    }
    return 0;
}