#include <stdio.h>
#include <string.h>

int dp[121][121];

int split(int n, int m)
{
    if (dp[n][m] != 0) return dp[n][m];
    if (n == 1 || m == 1) return dp[n][m] = 1;
    else if (m > n) return dp[n][n] = split(n, n);
    else if (m == n) return dp[n][m] = split(n, m-1) + 1;
    else return dp[n][m] = split(n, m-1) + split(n-m, m);
}

int main()
{
    int N;
    while (scanf("%d", &N) != EOF && N != 0)
    {
        memset(dp, 0, sizeof(dp));
        printf("%d\n", split(N, N));
    }
    return 0;
}