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

#define MAX 510
int N;
int num[MAX];

int main()
{
    int a,b,ans,index;
    while (scanf("%d",&N)!=EOF)
    {
        ans=INF;
        index=0;
        for (int i=0;i<N;i++)
            scanf("%d",&num[i]);
        scanf("%d",&b);
        for (int i=0;i<N;i++)
        {
            int tmp=b%num[i];
            if (ans>tmp)
            {
                ans=tmp;
                index=i;
            }
        }
        printf("%d\n", num[index]);
    }
    return 0;
}