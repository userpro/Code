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

#define MAX 110
char mp[MAX][MAX];
int to[8][2]={{-1,0},{1,0},{1,1},{1,-1},{-1,-1},{-1,1},{0,1},{0,-1}};
int n,m;

void bfs(int i,int j)
{
    queue<pair<int,int> > que;
    que.push(make_pair(i,j));
    mp[i][j]='.';
    while (!que.empty())
    {
        pair<int,int> t=que.front(); que.pop();
        for (int k=0;k<8;k++)
        {
            int ni=t.first+to[k][0];
            int nj=t.second+to[k][1];
            if (ni>=0 && ni<n && nj>=0 && nj<m && mp[ni][nj]=='W')
            {
                mp[ni][nj]='.';
                que.push(make_pair(ni,nj));
            }
        }
    }
}

int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (int i=0;i<n;i++)
            scanf("%s",mp[i]);

        int ans=0;
        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                if (mp[i][j]=='W')
                {
                    ans++;
                    bfs(i,j);
                }


        printf("%d\n", ans);
    }
    return 0;
}