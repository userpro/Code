#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

int l[100010], r[100010], sum, x, y, p, t, L, n;

int main()
{
    while (scanf("%d%d%d%d", &L, &n, &p, &t)!=EOF)
    {
        sum = 0;
        x = 0;
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &l[i], &r[i]);

        for (int i = 1; i <= n; ++i)
        {
            y = (r[i]-l[i])/p;
            if (y > 0)
                sum+= y;
            else if (i+1<=n)
                i++;
            //printf("sum=%d r[i]=%d\n", sum, r[i]);
            if (r[i]-l[i]>=p)
                x = r[i]-(r[i]-l[i])%p+t;
            else
                x = r[i] + t;
            while (i+1<=n && r[i+1]<x)
                i++;
            if (i+1<=n && x >= l[i+1] && x <= r[i+1])
            {
                l[i+1] = x;
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}