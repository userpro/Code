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

struct Robot
{
    int x,y;
    char direct;
}robot[110];
int D[256][2];
int K,A,B,N,M;
char buf[10];

int judge(int robot_i)
{
    if (robot[robot_i].x<=0 || robot[robot_i].x>=A+1 
        || robot[robot_i].y<=0 || robot[robot_i].y>=B+1)
        return -1;
    for (int i=1;i<=N;i++)
        if (i!=robot_i 
            && robot[robot_i].x==robot[i].x && robot[robot_i].y == robot[i].y)
            return i;

    return 0;
}

void L(int robot_i)
{
    switch (robot[robot_i].direct)
    {
        case 'E': robot[robot_i].direct='N'; break;
        case 'N': robot[robot_i].direct='W'; break;
        case 'W': robot[robot_i].direct='S'; break;
        case 'S': robot[robot_i].direct='E'; break;
        default: break;
    }
}

void R(int robot_i)
{
    switch (robot[robot_i].direct)
    {
        case 'E': robot[robot_i].direct='S'; break;
        case 'S': robot[robot_i].direct='W'; break;
        case 'W': robot[robot_i].direct='N'; break;
        case 'N': robot[robot_i].direct='E'; break;
        default: break;
    }
}

void F(int robot_i)
{
    switch (robot[robot_i].direct)
    {
        case 'E': robot[robot_i].x+=D['E'][0]; robot[robot_i].y+=D['E'][1]; break;
        case 'W': robot[robot_i].x+=D['W'][0]; robot[robot_i].y+=D['W'][1]; break;
        case 'S': robot[robot_i].x+=D['S'][0]; robot[robot_i].y+=D['S'][1]; break;
        case 'N': robot[robot_i].x+=D['N'][0]; robot[robot_i].y+=D['N'][1]; break;
        default: break;
    }
}

int main()
{
    D['E'][0]=1,D['E'][1]=0; D['N'][0]=0,D['N'][1]=1; D['W'][0]=-1,D['W'][1]=0;
    D['S'][0]=0,D['S'][1]=-1;
    while (scanf("%d",&K)!=EOF)
    {
        while (K--)
        {
            scanf("%d%d%d%d",&A,&B,&N,&M);
            for (int i=1;i<=N;i++)
            {
                scanf("%d%d",&robot[i].x,&robot[i].y);
                scanf("%s",buf);
                robot[i].direct=buf[0];
            }
            int robot_i,repeat_i;
            bool flag=true;
            for (int i=1;i<=M;i++)
            {
                scanf("%d%s%d",&robot_i,buf,&repeat_i);
                if (flag)
                {
                    for (int j=0;j<repeat_i;j++)
                    {
                        if (buf[0]=='L')
                            L(robot_i);
                        else if (buf[0]=='R')
                            R(robot_i);
                        else if (buf[0]=='F')
                            F(robot_i);

                        int res=judge(robot_i);
                        if (!res) continue;
                        if (res==-1)
                        {
                            printf("Robot %d crashes into the wall\n", robot_i);
                            flag=false;
                            break;
                        }
                        else
                        {
                            printf("Robot %d crashes into robot %d\n",robot_i,res);
                            flag=false;
                            break;
                        }
                    }
                }
            }
            if (flag)
                printf("OK\n");
        }
    }
    return 0;
}