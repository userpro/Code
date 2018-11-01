#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;
#define MAX 200000
#define INF 2<<20
typedef struct _POS
{
    int i, step, flag;
} pos;
pos dis[MAX];

int main()
{
    int N, K;
    pos * p, *p1, *p2, *p3;
    queue<pos*> q;
    for (int i = 0; i < MAX; ++i)
    {
        dis[i].i = i; dis[i].step = INF; dis[i].flag = 0;
    }
    while (scanf("%d %d", &N, &K) != EOF && N >= 0)
    {
        dis[N].step = 0;
        q.push(&dis[N]);
        while (!q.empty())
        {
            p = q.front();
            if (p->i + 1 < MAX)
            {
                p1 = &dis[p->i+1];
                if (p1->flag == 0)
                {
                    p1->flag = 1;
                    if (p1->step > p->step + 1)
                        p1->step = p->step + 1;
                    q.push(p1);
                }
            }
            if (p->i * 2 < MAX)
            {
                p2 = &dis[p->i*2];
                if (p2->flag == 0)
                {
                    p2->flag = 1;
                    if (p2->step > p->step + 1)
                        p2->step = p->step + 1;

                    q.push(p2);
                }
            }
            if (p->i - 1 >= 0)
            {
                p3 = &dis[p->i-1];
                if (p3->flag == 0)
                {
                    p3->flag = 1;
                    if (p3->step > p->step + 1)
                        p3->step = p->step + 1;
                    q.push(p3);
                }
            }
            q.pop();
        }
        printf("%d\n", dis[K].step);
    }
    return 0;
}