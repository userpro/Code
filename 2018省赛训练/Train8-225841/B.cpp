#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define MOD 1000000007

int n, a[500010], b[250005];
int aii[500010], amax[500010];

int main()
{
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
            aii[i] = a[i] - i;
        }
        for (int i = 1; i <= n; i++)
            scanf("%d", &b[i]);
        sort(b + 1, b + n + 1);

        int maxx = -1;
        for (int i = n; i >= 1; i--)
        {
            if (maxx < aii[i])
                maxx = aii[i];
            amax[i] = maxx;
        }

        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            int indexb = b[i];
            a[n + i] = amax[indexb];
            aii[n + i] = a[n + i] - n - i;
            amax[n + i] = aii[n + i];
            ans = (ans + a[n + i]) % MOD;

            int maxxx = amax[n + i];
            for (int j = n + i; j >= 1; j--)
            {
                if (maxxx < amax[j])
                {
                    break;
                }
                else
                {
                    amax[j] = maxxx;
                }
            }
        }

        printf("%d\n", ans%MOD);
    }
    
    return 0;
}