#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define INF 1<<20
#define MAX 101
#define NQ queue<pair<int, int> >
#define NNQ queue<NQ>

char mp[MAX][MAX];
int mmp[MAX][MAX];
bool visit[MAX][MAX];

int T, N, M, i, j, k, l, m, n, step;

void update(int a, int b, int l, NQ &q)
{
    visit[a][b] = 1;
    mmp[a][b] = l;
    q.push(make_pair(a, b));
}

void bfs1(int a, int b, int l, NNQ &Q)
{
    NQ q, q1;
    pair<int, int> p = make_pair(a, b);
    q.push(p);
    while (!q.empty())
    {
        p = q.front();
        a = p.first; b = p.second;
        if (a - 1 >= 0 && mp[a-1][b] == '#' && !visit[a-1][b]) 
            update(a-1, b, l, q);
        if (a + 1 < N && mp[a+1][b] == '#' && !visit[a+1][b])
            update(a+1, b, l, q);
        if (b - 1 >= 0 && mp[a][b-1] == '#' && !visit[a][b-1])
            update(a, b-1, l, q);
        if (b + 1 < M && mp[a][b+1] == '#' && !visit[a][b+1])
            update(a, b+1, l, q);
        q1.push(p);
        q.pop();
    }
    Q.push(q1);
}

int _bfs2(pair<int, int> &p, pair<int, int> *pp)
{
    for (j = 0; j < N; ++j)
        for (k = 0; k < M; ++k)
            mmp[j][k] = INF;

    memset(visit, 0, sizeof(visit));
    int t, a, b;
    NQ q1;
    pair<int, int> p1;
    q1.push(p);
    mmp[p.first][p.second] = 0;
    if (pp)
    {
        q1.push(*pp);
        mmp[pp->first][pp->second] = 0;
    }
    while (!q1.empty())
    {
        p1 = q1.front();
        a = p1.first; b = p1.second;
        if (a - 1 >= 0 && mp[a-1][b] == '#' && !visit[a-1][b])
        {
            visit[a-1][b] = 1;
            if (mmp[a][b] + 1 < mmp[a-1][b])
                mmp[a-1][b] = mmp[a][b] + 1;
            q1.push(make_pair(a-1, b));
        }
        if (a + 1 < N && mp[a+1][b] == '#' && !visit[a+1][b])
        {
            visit[a+1][b] = 1;
            if (mmp[a][b] + 1 < mmp[a+1][b])
                mmp[a+1][b] = mmp[a][b] + 1;
            q1.push(make_pair(a+1, b));
        }
            
        if (b - 1 >= 0 && mp[a][b-1] == '#' && !visit[a][b-1])
        {
            visit[a][b-1] = 1;
            if (mmp[a][b] + 1 < mmp[a][b-1])
                mmp[a][b-1] = mmp[a][b] + 1;
            q1.push(make_pair(a, b-1));
        }
            
        if (b + 1 < M && mp[a][b+1] == '#' && !visit[a][b+1])
        {
            visit[a][b+1] = 1;
            if (mmp[a][b] + 1 < mmp[a][b+1])
                mmp[a][b+1] = mmp[a][b] + 1;
            q1.push(make_pair(a, b+1));
        }
            
        q1.pop();
    }

    t = 0;
    for (j = 0; j < N; ++j)
        for (k = 0; k < M; ++k)
            if (t < mmp[j][k] && mmp[j][k] != INF)
                t = mmp[j][k];

    return t;
}


int bfs2(NNQ &Q)
{
    int t1, t2, t3;
    NQ q;
    pair<int, int> p1, p2;
    t2 = t3 = INF;

    if (Q.size() == 2)
    {
   
        q = Q.front();
        while (!q.empty())
        {
            p1 = q.front();
            t1 = _bfs2(p1, NULL);
            if (t2 > t1) t2 = t1;
            q.pop();
        }
        Q.pop();

        q = Q.front();
        while (!q.empty())
        {
            p1 = q.front();
            t1 = _bfs2(p1, NULL);
            if (t3 > t1) t3 = t1;
            q.pop();
        }
        Q.pop();
        if (t3 > t2) t2 = t3;

    } else if (Q.size() == 1) {
        q = Q.front();
        while (!q.empty())
        {
            p1 = q.front();
            NQ q1(q);
            while (!q1.empty()) 
            {
                p2 = q1.front();
                t1 = _bfs2(p1, &p2);
                if (t2 > t1) t2 = t1;
                q1.pop();
            }
            q.pop();
        }
        Q.pop();
    } else {
        t2 = -1;
    }

    return t2;
}


int main()
{
    while (scanf("%d", &T) != EOF && T)
    { 
        step = 1;
        for (i = 0; i < T; ++i)
        {
            NNQ Q;
            scanf("%d %d", &N, &M);
            memset(mp, 0, sizeof(mp));
            memset(mmp, 0, sizeof(mmp));
            memset(visit, 0, sizeof(visit));
            for (j = 0; j < N; ++j)
            {
                getchar();
                for (k = 0; k < M; ++k)
                    scanf("%c", &mp[j][k]);
            }

            l = 0;
            for (j = 0; j < N; ++j)
                for (k = 0; k < M; ++k)
                    if (mp[j][k] == '#' && !visit[j][k])
                        bfs1(j, k, ++l, Q);

            if (l>2 || l <= 0)
                printf("Case %d: %d\n", step++, -1);
            else
                printf("Case %d: %d\n", step++, bfs2(Q));

        }
    }
    return 0;
}