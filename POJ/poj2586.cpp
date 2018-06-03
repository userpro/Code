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

int s,d;
int main()
{
    while (scanf("%d%d",&s,&d)!=EOF)
    {
        int i=0;
        for (i=1;i<=5;i++)
            if (s*i-d*(5-i)>0)
            {
                i--;
                break;
            }

        int res=s*i*2-d*(5-i)*2;
        if (i>=2)
            res+=s*2;
        else if (i>0)
            res+=s*i-d*(2-i);
        if (res>=0)
            printf("%d\n", res);
        else
            printf("Deficit\n");
    }
    return 0;
}