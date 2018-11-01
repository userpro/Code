#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int t;
int nx[15000];
char x[15000],y[1000005];

void prekmp(int n)
{
    int i,j;
    j=nx[0]=-1;
    i=0;
    while (i<n)
    {
        if (j==-1 || x[i]==x[j])
            nx[++i]=++j;
        else
            j=nx[j];
    }
}

int kmp_count(int n, int m)
{
    prekmp(n);
    int i,j,ans;
    i=j=ans=0;
    while (i<m)
    {
        if (j==-1 || x[j]==y[i])
        {
            i++; j++;
        } else {
            j=nx[j];
        }
        if (j>=n)
        {
            ans++;
            j=nx[j];
        }
    }
    return ans;
}

int main()
{
    scanf("%d",&t);
    while (t--)
    {
        scanf("%s %s",x,y);
        printf("%d\n", kmp_count(strlen(x),strlen(y)));
    }
    return 0;
}