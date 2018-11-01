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

int getBall(char *c)
{
    if(strcmp(c, "red") == 0) return 0;
    if(strcmp(c, "yellow") == 0) return 1;
    if(strcmp(c, "green") == 0) return 2;
    if(strcmp(c, "brown") == 0) return 3;
    if(strcmp(c, "blue") == 0) return 4;
    if(strcmp(c, "pink") == 0) return 5;
    if(strcmp(c, "black") == 0) return 6;
}

int main()
{
    int balls[7], n, i, sum, max;
    char name[10];
    while(scanf("%d", &n) != EOF)
    {
        CLR(balls, 0);
        sum = 0;
        for(i=0; i<n; i++)
        {
            scanf("%s", name);
            int ball = getBall(name);
            sum += ball + 1;
            balls[ball]++;
        }
        max = -1;
        for(i=1; i<7; i++) if(balls[i] != 0) max = i;
        if(max == -1) sum = 1;
        else sum += balls[0] * (max+1);
        printf("%d\n", sum);
    }
    return 0;
}