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

struct Node
{
    int col,row;
}p[6*6];
char mp[6][6];
bool mp1[6][6];

void update(int x,int y)
{
    for (int i=1;i<=4;i++)
        mp1[x][i]=!mp1[x][i];
    for (int i=1;i<=4;i++)
        mp1[i][y]=!mp1[i][y];
    mp1[x][y]=!mp1[x][y];
}

bool isok()
{
    for (int i=1;i<=4;i++)
        for (int j=1;j<=4;j++)
            if (!mp1[i][j])
                return false;
    return true;
}

bool flag;
int step;
int dfs(int row,int col,int deep)
{
    if (deep==step)
        return flag=isok();
    if (flag || row>4)
        return 0;
    update(row,col);
    p[deep].row=row;
    p[deep].col=col;
    if (col<4)
        dfs(row,col+1,deep+1);
    else
        dfs(row+1,1,deep+1);
    update(row,col);
    if (col<4)
        dfs(row,col+1,deep);
    else
        dfs(row+1,1,deep);
    return 0;
}

int main()
{
    for (int i=1;i<=4;i++)
        scanf("%s",mp[i]+1);
    CLR(mp1,0);
    for (int i=1;i<=4;i++)
        for (int j=1;j<=4;j++)
            if (mp[i][j]=='-')
                mp1[i][j]=1;
            else
                mp1[i][j]=0;

    flag=false;
    for (step=0;step<=16;step++)
    {
        dfs(1,1,0);
        if (flag)
        {
            printf("%d\n", step);
            break;
        }
    }

    for (int i=0;i<step;i++)
        printf("%d %d\n", p[i].row,p[i].col);
    return 0;
}