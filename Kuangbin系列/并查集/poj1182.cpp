#include <cstdio>
#include <cstring>

#define MAXN 50020
int N, K, pre[MAXN], val[MAXN];

void initt(int n)
{
    for (int i = 0; i <= n; ++i)
    {
        pre[i] = i;
        val[i] = 0;
    }
}

int findd(int x)
{
    if (pre[x] == x) return x;
    int t = findd(pre[x]);
    val[x] = (val[x] + val[pre[x]]) % 3;
    return pre[x] = t;
}

int unionn(int tp, int x, int y)
{
    int a = findd(x), b = findd(y);
    if (a == b)
    {
        if ((val[x] - val[y] + 3) % 3 == tp-1)
            return 0;
        return 1;
    }
    pre[a] = b;
    val[a] = (-val[x] + val[y] + tp-1 + 3) % 3;
    return 0;
}

int main()
{
    scanf("%d%d", &N, &K);
    initt(N);
    int d, x, y, ans = 0;
    for (int i = 1; i <= K; ++i)
    {
        scanf("%d%d%d", &d, &x, &y);
        if (x > N || y > N) ans++;
        else if (d == 2 && x == y) ans++;
        else ans += unionn(d, x, y);
    }
    printf("%d\n", ans);
    return 0;
}