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

int T,N,B;
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        int a;
        bool flag=false;
        while (T--)
        {
            flag=false;
            scanf("%d%d",&N,&B);
            for (int i=0;i<N;i++)
            {
                scanf("%d",&a);
                if ((a+B)%7==0)
                    flag=true;
            }
        
            if (flag)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}