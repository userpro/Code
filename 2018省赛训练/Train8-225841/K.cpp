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

#define MAXN 80010
char s1[MAXN],s2[MAXN];
int T,N,X,Y;
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            scanf("%d%d%d",&N,&X,&Y);
            scanf("%s%s",s1,s2);
            int diff=0;
            for (int i=0;i<N;i++)
                if (s1[i]!=s2[i])
                    diff++;

            int equ=N-diff;
            if (abs(X-Y)<=diff && X+Y<=equ*2+diff)
                printf("Not lying\n");
            else
                printf("Lying\n");

        }
    }
    return 0;
}