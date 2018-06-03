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

#define MAX 310
int n;
int num[MAX];
int main()
{
    while (scanf("%d",&n)!=EOF)
    {
        for (int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        int vecs=num[n]+1;
        int ready=0,l=1,r=n,ans=0;
        for (int v=1;v<vecs;v++)
        {
            if (num[l]<=ready)
                l++,r--;
            else if (ready+vecs-v==num[r])
                ready++,ans+=vecs-v;
        }
        printf("%d\n", ans);

        l=1,r=n,ready=0;
        for (int v=1;v<vecs;v++)
        {
            if (num[l]<=ready)
                l++,r--;
            else if (ready+vecs-v==num[r])
            {
                for (int j=v+1;j<=vecs;j++)
                    printf("%d %d\n", v, j);
                ready++;
            }
        }
    }
    return 0;
}