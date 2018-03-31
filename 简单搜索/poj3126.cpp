#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>

using namespace std;
#define INF 1<<30
#define MAX 10001

typedef struct _pos
{
    int dis;
    int num;
} pos;

bool prime[MAX], visit[MAX];
pos primes[MAX];

void update(int t1, int n, queue<pos*> &q)
{
    if (visit[t1])
    {
        if (t1 != n)
        {
            if (prime[t1])
            {
                if (primes[t1].dis > primes[n].dis + 1) 
                    primes[t1].dis = primes[n].dis + 1;
                q.push(&primes[t1]);
            }
        }
        visit[t1] = false;
    }
}

void bfs(int a, int b)
{
    primes[a].num = a; primes[b].num = b;
    primes[a].dis = 0;
    if (a == b)
    {
        primes[b].dis = primes[a].dis;
        return;
    }

    pos* t;
    int t1, i, n;
    queue<pos*> q;
    q.push(&primes[a]);
    visit[a] = false;
    while (!q.empty())
    {
        t = q.front();
        n = t->num;
        for (i = 0; i < 10; ++i)
        {
            t1 = n - n%10 + i;
            update(t1, n, q);
        }
        for (i = 0; i < 10; ++i)
        {
            t1 = n - n/10%10*10 + i*10;
            update(t1, n, q);
        }
        for (i = 0; i < 10; ++i)
        {
            t1 = n - n/100%10*100 + i*100;
            update(t1, n, q);
        }
        for (i = 1; i < 10; ++i)
        {
            t1 = n - n/1000*1000 + i*1000;
            if (visit[t1])
            update(t1, n, q);
        }
        q.pop();
    }
}

int main()
{
    int i, j, N, a, b;
    memset(prime, true, sizeof(prime));
    for (i = 2; i < sqrt(MAX); ++i)
        if (prime[i])
        {
            j = i;
            while (j < MAX)
            {
                j += i;
                prime[j] = false;
            }
        }


    while (scanf("%d", &N) != EOF && N != 0)
    {
        while (N--)
        {
            memset(visit, true, sizeof(visit));
            for (i = 0; i < MAX; ++i) 
            {
                primes[i].dis = INF;
                primes[i].num = i;
            }
            scanf("%d %d", &a, &b);
            bfs(a, b);
            printf("%d\n", primes[b].dis);
        }
    }

    return 0;
}