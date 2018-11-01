#include <stdio.h>

#define llu unsigned long long

bool ok;
void dfs(llu a, int n, int depth)
{
    if (ok) return;
    if (a % n == 0)
    {
        printf("%llu\n", a);
        ok = true;
        return;
    }
    if (depth >= 19) return;
    dfs(a*10, n, depth+1);
    dfs(a*10+1, n, depth+1);
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF && n != 0)
    {
        ok = false;
        dfs(1, n, 0);
    }
    return 0;
}