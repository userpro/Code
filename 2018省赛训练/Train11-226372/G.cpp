#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define MAX 200010

struct node
{
    LL x, y;
    bool operator < (const node &tmp) const {
        return x - y > tmp.x - tmp.y;
    }
};

int main()
{
    int n, a, b;
    LL sum;
    node m[MAX];
    while(scanf("%d%d%d", &n, &a, &b) != EOF)
    {
        CLR(m,0);
        sum = 0;
        for(int i = 1; i <= n; i++) scanf("%lld%lld", &m[i].x, &m[i].y);
        
        sort(m + 1, m + n + 1);
        for(int i = 1; i <= b; i++) sum += max(m[i].x, m[i].y);
        for(int i = b + 1; i <= n; i++) sum += m[i].y;

        LL ans = sum;
        for(int i = 1; i <= b; i++) ans = max(ans, sum - max(m[i].x, m[i].y) + (m[i].x << a));
        sum = sum - max(m[b].x, m[b].y) + m[b].y;
        for(int i = b + 1; i <= n && b; i++) ans = max(ans, sum - m[i].y + (m[i].x << a));

        printf("%lld\n", ans);
    }
    return 0;
}