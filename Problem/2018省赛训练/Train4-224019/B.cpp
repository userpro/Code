#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 1100
int n,A,B,C,T;
int num[MAXN];

int main(int argc, char const *argv[])
{
    while (scanf("%d%d%d%d%d",&n,&A,&B,&C,&T)!=EOF)
    {
        CLR(num,0);
        int a;
        for (int i=0;i<n;i++)
        {
            scanf("%d",&a);
            num[a]++;
        }

        if (B>=C)
        {
            printf("%d\n", n*A);
        }
        else
        {
            int ans=n*A;
            for (int i=0;i<=T;i++)
            {
                if (num[i])
                    ans+=((C-B)*(T-i)*num[i]);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}