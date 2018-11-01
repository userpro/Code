#include <stdio.h>
#include <queue>
#include <list>
#include <string>
using namespace std;

#define INF 2<<20
#define MAX 101
typedef struct _pos
{
    int dis, A, B, flag;
    char t;
    struct _pos * pre;
} pos;
pos dp[MAX][MAX];

int A, B, C;
queue<pos*> q, q1;
list<string> S;

void print_S(pos *p)
{
    pos *t = p;
    while (t->pre)
    {
        if (t->t == 'A')
            S.push_back(string("FILL(1)"));
        else if (t->t == 'B')
            S.push_back(string("FILL(2)"));
        else if (t->t == 'C')
            S.push_back(string("POUR(1,2)"));
        else if (t->t == 'D')
            S.push_back(string("POUR(2,1)"));
        else if (t->t == 'E')
            S.push_back(string("DROP(1)"));
        else if (t->t == 'F')
            S.push_back(string("DROP(2)"));
        else
            S.push_back(string("None"));

        t = t->pre;
    }
    while (!S.empty())
    {
        printf("%s\n", S.back().c_str());
        S.pop_back();
    }
}

void update(pos *t, pos *p, char c)
{
    if (dp[p->A][p->B].flag) 
        return;
    else
        dp[p->A][p->B].flag = 1;
    
    dp[p->A][p->B].t = c;
    if (dp[t->A][t->B].dis + 1 < dp[p->A][p->B].dis)
    {
        dp[p->A][p->B].pre = t;
        dp[p->A][p->B].dis = dp[t->A][t->B].dis + 1;
    }
    
    if (p->A == C || p->B == C) q1.push(p);
    else q.push(p);
}

int main()
{
    pos *t, *t1, *t2, *t3, *t4, *t5, *t6, *m;
    int i, j, k;
    while (scanf("%d %d %d", &A, &B, &C) != EOF && A != 0)
    {
        for (i = 0; i < MAX; ++i)
            for (j = 0; j < MAX; ++j)
            {
                dp[i][j].A = i;
                dp[i][j].B = j;
                dp[i][j].t = 0;
                dp[i][j].flag = 0;
                dp[i][j].dis = INF;
                dp[i][j].pre = NULL;
            }
        
        dp[0][0].dis = 0;
        dp[0][0].flag = 1;
        q.push(&dp[0][0]);
        while (!q.empty())
        {
            t = q.front();
            t1 = &dp[A][t->B];
            t2 = &dp[t->A][B];
            if (t->A > (B - t->B))
                t3 = &dp[t->A - (B - t->B)][B];
            else
                t3 = &dp[0][t->A + t->B];

            if (t->B > (A - t->A))
                t4 = &dp[A][t->B - ((A - t->A))];
            else
                t4 = &dp[t->A + t->B][0];

            t5 = &dp[0][t->B];
            t6 = &dp[t->A][0];

            update(t, t1, 'A');
            update(t, t2, 'B');
            update(t, t3, 'C');
            update(t, t4, 'D');
            update(t, t5, 'E');
            update(t, t6, 'F');

            q.pop();
        }

        k = INF;
        while (!q1.empty())
        {
            t = q1.front();
            if (k > t->dis)
            {
                k = t->dis;
                m = t;
            }
            q1.pop();
        }
        if (k != INF)
        {
            printf("%d\n", k);
            print_S(m);
        } else {
            printf("impossible\n");
        }
    }
    return 0;
}