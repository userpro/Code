#include <cstdio>
#include <cstring>
#include <cmath>

#define DIS(a,b) sqrt((a.x-b.x)*(a.x-b.x)*1.0 + (a.y-b.y)*(a.y-b.y))
#define MAXN 1010
#define MAXD 20010
struct Pos
{
    int x, y;
    Pos() {}
    Pos(int _x, int _y):x(_x),y(_y) {}
};
Pos comp[MAXN];
bool is_repair[MAXN];
int N, par[MAXN];
double D;

void init(int n)
{
    for (int i = 1; i <= n; ++i)
        par[i] = i;
}

int findd(int x)
{
    if (par[x] == x) return x;
    else return par[x] = findd(par[x]);
}

void unite(int x, int y)
{
    x = findd(x); y = findd(y);
    if (x == y) return;
    else par[y] = x;
}

int main()
{
    memset(is_repair, 0, sizeof(is_repair));
    scanf("%d%lf", &N, &D);
    int x, y;
    for (int i = 1; i <= N; ++i)
    {
        scanf("%d%d", &x, &y);
        comp[i] = Pos(x, y);
    }
    int n1, n2;
    char c;
    init(N);
    while (getchar() && scanf("%c", &c) > 0)
    {
        if (c == 'O')
        {
            scanf("%d", &n1);
            is_repair[n1] = 1;
            for (int i = 1; i <= N; ++i)
                if (i != n1 && is_repair[i] && findd(i) != findd(n1) && DIS(comp[i], comp[n1]) <= D)
                    unite(i, n1);
        }
        else if (c == 'S')
        {
            // init(N);
            // for (int i = 1; i <= N; ++i)
            // {
            //     if (is_repair[i])
            //     {
            //         for (int j = 1; j <= N; ++j)
            //             if (i!=j && is_repair[j] && findd(i) != findd(j) && DIS(comp[i], comp[j]) <= D)
            //                 unite(i, j);
            //     }
            // }
            scanf("%d%d", &n1, &n2);
            if (findd(n1) == findd(n2))
                printf("SUCCESS\n");
            else
                printf("FAIL\n");
        }
    }
    return 0;
}