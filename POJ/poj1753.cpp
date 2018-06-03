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

char mp[5][5];
bool mp1[5][5],mp2[5][5];

void update(int i,int j)
{
    mp2[i][j]=!mp2[i][j];
    if (i-1>=0) mp2[i-1][j]=!mp2[i-1][j];
    if (i+1<4)  mp2[i+1][j]=!mp2[i+1][j];
    if (j-1>=0) mp2[i][j-1]=!mp2[i][j-1];
    if (j+1<4)  mp2[i][j+1]=!mp2[i][j+1];
}

int main()
{
    CLR(mp,0);
    CLR(mp1,0);
    CLR(mp2,0);
    for (int i=0;i<4;i++)
        scanf("%s",mp[i]);
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            if (mp[i][j]=='w')
                mp1[i][j]=1;
            else
                mp1[i][j]=0;

    int ans=INF;
    for (int i=0;i<1<<4;i++)
    {
        int tmp=0;
        memcpy(mp2,mp1,sizeof(mp1));
        for (int j=0;j<4;j++)
            if (i&(1<<j))
            {
                update(0,j);
                tmp++;
            }

        for (int j=1;j<4;j++)
            for (int k=0;k<4;k++)
                if (!mp2[j-1][k])
                {
                    update(j,k);
                    tmp++;
                }

        bool flag=true;
        for (int j=0;j<4;j++)
            if (!mp2[3][j])
                flag=false;

        if (flag) ans=min(ans,tmp);
    }

    for (int i=0;i<1<<4;i++)
    {
        int tmp=0;
        memcpy(mp2,mp1,sizeof(mp1));
        for (int j=0;j<4;j++)
            if (i&(1<<j))
            {
                update(0,j);
                tmp++;
            }

        for (int j=1;j<4;j++)
            for (int k=0;k<4;k++)
                if (mp2[j-1][k])
                {
                    update(j,k);
                    tmp++;
                }

        bool flag=true;
        for (int j=0;j<4;j++)
            if (mp2[3][j])
                flag=false;

        if (flag) ans=min(ans,tmp);
    }

    if (ans==INF) printf("Impossible\n");
    else printf("%d\n", ans);
    return 0;
}