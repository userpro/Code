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

#define MAX 100010
int num[MAX],d[MAX];
int N;
int main()
{
    while (scanf("%d",&N)!=EOF)
    {
        CLR(num, 0);
        CLR(d, 0);
        for (int i=1;i<=N;i++)  // num 1~n
            scanf("%d",&num[i]);
        for (int i=2;i<=N;i++)  // delta 2~n
            d[i]=num[i]-num[i-1];
        int _max = 0, last = d[2], len = 1, cache=-1;
        for (int i=3; i<=N; i++)
        {
            if (d[i] == 0) {len++; if(cache == -1) cache = i;}
            else if(d[i] != 0 && last == d[i])
            {
                last = d[i];
                if(len > _max) _max = len;
                len = 1;
                if(cache != -1) {i = cache; last = 0;}
                cache = -1;
            }
            else if(d[i] != 0 && last != d[i])
            {last = d[i]; len++; cache = -1;}
        }
        if(len > _max) _max = len;
        printf("%d\n", _max+1);
    }
    return 0;
}