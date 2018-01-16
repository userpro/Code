#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
#define MAX 110
typedef struct _pos
{
    int a, b, c;
    int dis;
}pos;
bool visit[MAX][MAX][MAX];
int S, N, M, i, j, k, a, b, c, flag;

void update(pos s, pos e, queue<pos> &q)
{
    if (!visit[e.a][e.b][e.c] && flag)
    {
        if (e.a==S/2 && (e.b==S/2 || e.c==S/2))
            flag = 0;
        visit[e.a][e.b][e.c] = 1;
        e.dis=s.dis+1;
        q.push(e);
    }
}

void bfs()
{
    memset(visit, 0, sizeof(visit));
    pos s,e;
    queue<pos> q;
    flag = 1;
    s.a=S; s.b=0; s.c=0; s.dis=0;
    visit[S][0][0] = 1;
    q.push(s);
    while (flag && !q.empty())
    {
        s = q.front();
        if (s.a > 0)
        {
            if (s.b < N)
            {
                if (s.a > N-s.b)
                {
                    e.a = s.a-(N-s.b); e.b = N; e.c = s.c;
                }
                else {
                    e.a = 0; e.b = s.a+s.b; e.c = s.c;
                }
                update(s,e,q);
            }

            if (s.c < M)
            {
                if (s.a > M-s.c)
                {
                    e.a = s.a-(M-s.c); e.b = s.b; e.c = M;
                }
                else {
                    e.a = 0; e.b = s.b; e.c = s.a+s.c;
                }
                update(s,e,q);
            }
        }

        if (s.b > 0)
        {
            if (s.a < S)
            {
                if (s.b > S-s.a)
                {
                    e.a = S; e.b = s.b-(S-s.a); e.c = s.c;
                }
                else {
                    e.a = s.a+s.b; e.b = 0; e.c = s.c;   
                }
                update(s,e,q);
            }

            if (s.c < M)
            {
                if (s.b > M-s.c)
                {
                    e.a = s.a; e.b = s.b-(M-s.c); e.c = M;
                }
                else {
                    e.a = s.a; e.b = 0; e.c = s.b+s.c;
                }
                update(s,e,q);
            }
        }

        if (s.c > 0)
        {
            if (s.a < S)
            {
                if (s.c > S-s.a)
                {
                    e.a = S; e.b = s.b; e.c = s.c-(S-s.a);
                }
                else {
                    e.a = s.a+s.c; e.b = s.b; e.c = 0;
                }
                update(s,e,q);
            }

            if (s.b < N)
            {
                if (s.c > N-s.b)
                {
                    e.a = s.a; e.b = N; e.c = s.c-(N-s.b);
                }
                else {
                    e.a = s.a; e.b = s.b+s.c; e.c = 0;
                }
                update(s,e,q);
            }
        }

        q.pop();
    }

    if (!flag)
        printf("%d\n", s.dis+1);
    else
        printf("NO\n");
}

int main()
{
    while (scanf("%d %d %d", &S, &N, &M) != EOF && S)
    {
        if (S&1)
            printf("NO\n");
        else if (N==M)
            printf("1\n");
        else
            bfs();
    }
    return 0;
}