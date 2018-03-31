#include <stdio.h>

using namespace std;
#define uint unsigned long long

uint gcd(uint a, uint b)
{
    if (b == 0) return a;
    return gcd(b, a%b);
}

uint lcm(uint a, uint b)
{
    return a*b/gcd(a,b);
}

int main()
{
    uint N, M, i, j, t1, t2;
    while (scanf("%llu", &N) != EOF && N != 0)
    {
        for (j = 0; j < N; ++j)
        {
            scanf("%llu", &M);
            scanf("%llu", &t1);
            for (i = 0; i < M-1; ++i)
            {
                scanf("%llu", &t2);
                t1 = lcm(t1, t2);
            }
            printf("%llu\n", t1);
        }
    }
    return 0;
}