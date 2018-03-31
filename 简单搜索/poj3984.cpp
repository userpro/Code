#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <list>

using namespace std;
#define INF 1<<20
#define MAX 5
typedef struct _pos
{
    int x, y;
    int dis;
    struct _pos *pre;
}pos;
int mp[MAX][MAX];
pos mmp[MAX][MAX];
bool visit[MAX][MAX];

void update(pos *p1, pos *p2, queue<pos*> &q)
{
    if (!visit[p2->x][p2->y] && mp[p2->x][p2->y] != 1)
    {
        if (p1->dis+1 < p2->dis)
        {
            p2->dis = p1->dis + 1;
            p2->pre = p1;
        }
        visit[p2->x][p2->y] = 1;
        q.push(&mmp[p2->x][p2->y]);
    }
}

void out(pos *p)
{
    list<string> l;
    pos *t;
    t = p;
    stringstream ss;
    while (t)
    {
        ss.str("");
        ss << "(" << t->x << ", " << t->y << ")" << endl;
        l.push_back(ss.str());
        t = t->pre;
    }
    while (!l.empty())
    {
        printf("%s", l.back().c_str());
        l.pop_back();
    }
}

int main()
{
    int i, j, k;
    queue<pos*> q;
    pos* p;
    memset(visit, 0, sizeof(visit));
    for (i = 0; i < MAX; ++i)
        for (j = 0; j < MAX; ++j)
        {
            scanf("%d", &mp[i][j]);
            mmp[i][j].x = i; mmp[i][j].y = j;
            mmp[i][j].dis = INF;
            mmp[i][j].pre = NULL;
        }

    mmp[0][0].dis = 0;
    q.push(&mmp[0][0]);
    while (!q.empty())
    {
        p = q.front();
        if (p->x-1>=0)
            update(p, &mmp[p->x-1][p->y], q);
        if (p->y-1>=0)
            update(p, &mmp[p->x][p->y-1], q);
        if (p->x+1<5)
            update(p, &mmp[p->x+1][p->y], q);
        if (p->y+1<5)
            update(p, &mmp[p->x][p->y+1], q);
        q.pop();
    }
    out(&mmp[4][4]);

    return 0;
}