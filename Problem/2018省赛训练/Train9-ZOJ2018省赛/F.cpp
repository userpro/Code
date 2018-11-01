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

#define MAX 500010
int T,N,M;
int a[MAX],p[MAX],z[MAX];
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            scanf("%d%d",&N,&M);
            for (int i=1;i<=N;i++)
                scanf("%d",&a[i]);
            for (int i=1;i<=M;i++)
                scanf("%d",&p[i]);
        }
    }
    return 0;
}