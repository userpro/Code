#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define MAXN 100020
char a[MAXN],b[MAXN];
int _next[MAXN];

void prekmp(int n)
{
    int i,j;
    j=_next[0]=-1;
    i=0;
    while (i<n)
    {
        while (j!=-1&&b[i]!=b[j]) j=_next[j];
        _next[++i]=++j;
    }
}

bool kmp(int x,int y)
{
    int i,j;
    i=j=0;
    while (i<x)
    {
        if (j==-1 || a[i]==b[j])
        {
            i++; j++;
        }
        else
        {
            j=_next[j];
        }

        if (j>=y)
            return true;
    }
    return false;
}

int T;
int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            scanf("%s%s",a,b);
            int x=strlen(a);
            int y=strlen(b);
            if (x<y)
                printf("Bob\n");
            else if (b[0]=='0')
                printf("Alice\n");
            else
            {
                prekmp(y);
                if (kmp(x,y))
                    printf("Alice\n");
                else
                {
                    reverse(b,b+y);
                    prekmp(y);
                    if (kmp(x,y))
                        printf("Alice\n");
                    else
                        printf("Bob\n");
                }
            }
        }
    }
    return 0;
}