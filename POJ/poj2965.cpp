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

char mp[6][6];
int mmp[6][6];
void update(int x,int y)
{
    for (int i=1;i<=4;i++)
        mmp[x][i]=(mmp[x][i]+1)%2;
    for (int i=1;i<=4;i++)
        mmp[i][y]=(mmp[i][y]+1)%2;
    mmp[x][y]=(mmp[x][y]+1)%2;
}

int main()
{
    for (int i=1;i<=4;i++)
        scanf("%s",mp[i]+1);
    CLR(mmp,0);
    for (int i=1;i<=4;i++)
        for (int j=1;j<=4;j++)
            if (mp[i][j]=='+')
                update(i,j);

    int ans=0;
    for (int i=1;i<=4;i++)
        for (int j=1;j<=4;j++)
            ans+=mmp[i][j];

    printf("%d\n", ans);
    for (int i=1;i<=4;i++)
        for (int j=1;j<=4;j++)
            if (mmp[i][j])
                printf("%d %d\n", i,j);
    return 0;
}