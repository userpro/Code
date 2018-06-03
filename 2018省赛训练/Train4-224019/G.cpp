#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAXN 200010
int n,a,b;
char buf[MAXN];
int main()
{
    while (scanf("%d%d%d",&n,&a,&b)!=EOF)
    {
        int aa=a,bb=b;
        scanf("%s",buf);
        int len=strlen(buf);
        for (int i=0;i<len;i++)
        {
            if (buf[i]=='.')
            {
                if (i==0)
                {
                    if (a>b)
                    {
                        buf[i]='A';
                        a--;
                    }
                    else
                    {
                        b--;
                        buf[i]='B';
                    }
                }
                else if (buf[i-1]=='A')
                {
                    buf[i]='B';
                    b--;
                }
                else if (buf[i-1]=='B')
                {
                    buf[i]='A';
                    a--;
                }
                else if (buf[i-1]=='*')
                {
                    if (a>b)
                    {
                        buf[i]='A';
                        a--;
                    }
                    else
                    {
                        buf[i]='B';
                        b--;
                    }
                }
            }
        }
        int sa=0,sb=0;
        for (int i=0;i<len;i++)
        {
            if (buf[i]=='A')
                sa++;
            else if (buf[i]=='B')
                sb++;
        }
        int res=sa+sb;
        if (a<0)
            res+=a;
        if (b<0)
            res+=b;
        printf("%d\n", res);
    }
    return 0;
}