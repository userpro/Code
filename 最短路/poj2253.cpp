#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
#define INF 2<<20
#define MAX 1001
#define max(a,b) (a>b?a:b)
typedef struct _pos
{
    double x, y;
}pos;
bool S[MAX];
pos P[MAX];
double D[MAX];
double m;
int N, i, j, k, l, cnt;

double dis(pos &p1, pos &p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

int main()
{
    cnt = 0;
    k = 1;
    while (scanf("%d", &N) != EOF && N)
    {
        memset(D, 0x7f, sizeof(D));
        memset(S, 0, sizeof(S));
        for (i = 0; i < N; ++i)
            scanf("%lf%lf", &P[i].x, &P[i].y);

        // dijk
        D[0] = 0;
        for (i = 0; i < N; ++i)
        {
            m = INF;
            for (j = 0; j < N; ++j)
            {
                if (!S[j] && m > D[j])
                {
                    m = D[j];
                    l = j;
                }
            }
            S[l] = 1;
            if (l == 1) break;
            for (j = 0; j < N; ++j)
            {
                if (!S[j] && D[j] > max(dis(P[j], P[l]), D[l]))
                    D[j] = max(dis(P[j], P[l]), D[l]);
            }

        }

        if (cnt++ > 0) printf("\n");
        printf("Scenario #%d\n", k++);
        printf("Frog Distance = %.3f\n", D[1]);
    }
    return 0;
}