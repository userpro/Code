#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
char mp[4][4];
bool vis[3][3];
char buf[5];
int T;
char a;
int to[4][2]={{-1,0},{0,1},{0,-1},{1,0}};

bool check1(int i,int j,char c)
{
    if (i-1>=0&&j-1>=0&&i+1<3&&j+1<3&&mp[i-1][j-1]==c&&mp[i+1][j+1]==c)
        return true;
    else if (i+1<3&&j-1>=0&&j+1<3&&mp[i+1][j-1]==c&&mp[i-1][j+1]==c)
        return true;
    else if (i-1>=0&&i+1<3&&mp[i-1][j]==c&&mp[i+1][j]==c)
        return true;
    else if (j+1<3&&j-1>=0&&mp[i][j+1]==c&&mp[i][j-1]==c)
        return true;
    return false;
}

bool check(char c)
{
    for (int i=0;i<3;i++)
        if (mp[1][i]==c&&check1(1,i,c))
            return true;
    return false;
}

bool solve(char c,int step)
{
    if (step>2)
        return false;
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            if (mp[i][j]=='.')
            {
                char t=mp[i][j];
                mp[i][j]=c;
                if (check(c))
                                return true;
                for (int k=0;k<3;k++)
                    for (int kk=0;kk<3;kk++)
                        if (mp[k][kk]=='.')
                        {
                            char tt=mp[k][kk];
                            if (c=='o')
                                mp[k][kk]='x';
                            else
                                mp[k][kk]='o';
                            
                            solve(c,step+1);
                            mp[k][kk]=tt;
                        }
                mp[i][j]=t;
            }
    return false;
}

int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        char c;
        getchar();
        while (T--)
        {
            for (int i=0;i<3;i++)
            {
                for (int j=0;j<3;j++)
                    scanf("%c%c",&mp[i][j],&c);
            }
            scanf("%c%c",&a,&c);
            if (solve(a,1))
                printf("Kim win!\n");
            else
                printf("Cannot win!\n");
        }
    }
    return 0;
}