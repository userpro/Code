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

#define LEN 100005
#define MAX 400005
#define ADD 200000

int main()
{
    int t, n;
    int d[LEN], s[LEN], cnt[MAX];
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        CLR(cnt, 0);
        for(int i=0; i<n; i++) scanf("%d", &d[i]);
        for(int i=0; i<n; i++)
        {
            scanf("%d", &s[i]);
            int delta = d[i] - s[i];
            cnt[delta + ADD] += 1;
        }
        int c = 0;
        for(int i=0; i<MAX; i++) if(cnt[i] > c) c = cnt[i];
        printf("%d\n", c);
    }
    return 0;
}