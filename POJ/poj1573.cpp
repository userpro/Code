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

char mp[20][20];
int vis[20][20];
int D[256][2];
int row,col,enter;

void walk(int x,int y)
{
    int steps=1;
    vis[x][y]=steps;
    while (1)
    {
        switch (mp[x][y])
        {
            case 'W': x+=D['W'][0]; y+=D['W'][1]; break;
            case 'E': x+=D['E'][0]; y+=D['E'][1]; break;
            case 'N': x+=D['N'][0]; y+=D['N'][1]; break;
            case 'S': x+=D['S'][0]; y+=D['S'][1]; break;
            default: break;
        }
        ++steps;
        if (x<=0 || x>row || y<=0 || y>col)
        {
            printf("%d step(s) to exit\n",steps-1);
            break;
        }
        if (!vis[x][y]) vis[x][y]=steps;
        else
        {
            printf("%d step(s) before a loop of %d step(s)\n", vis[x][y]-1,steps-vis[x][y]);
            break;
        }
    }
}

int main()
{
    D['N'][0]=-1,D['N'][1]=0;
    D['S'][0]=1,D['S'][1]=0;
    D['W'][0]=0,D['W'][1]=-1;
    D['E'][0]=0,D['E'][1]=1;
    while (scanf("%d%d%d",&row,&col,&enter)!=EOF && (row || col || enter))
    {
        for (int i=1;i<=row;i++)
            scanf("%s",mp[i]+1);
        CLR(vis,0);
        walk(1,enter);
    }
    return 0;
}