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

int t,n,m;
int main()
{
    while (scanf("%d",&t)!=EOF)
    {
        while (t--)
        {
            int tmp;
            int maxx=0,minn=0;
            scanf("%d%d",&n,&m);
            for (int i=0;i<m;i++)
            {
                scanf("%d",&tmp);
                int t=max(tmp,n-tmp);
                maxx=max(maxx,t);
                t=min(tmp,n-tmp);
                minn=max(minn,t);
            }
            printf("%d %d\n", minn,maxx);
        }
    }
    return 0;
}