#include <cstdio>
#include <cstring>

#define MAXN 1010
char s1[MAXN], s2[MAXN];
int _next[MAXN];

void kmp_pre(char x[], int m)
{
    int i,j;
    j=_next[0]=-1;
    i=0;
    while (i<m)
    {
        while (j!=-1 && x[i]!=x[j]) j=_next[j];
        _next[++i]=++j;
    }
}

int kmp_count(char x[], int m, char y[], int n)
{
    int i,j;
    int ans=0;
    kmp_pre(x,m);
    i=j=0;
    while (i<n)
    {
        while (j!=-1 && x[j]!=y[i]) j=_next[j];
        i++;j++;
        if (j>=m)
        {
            ans++;
            i+=m-1;
            j=_next[j];
        }
    }
    return ans;
}

int main()
{
    while (scanf("%s%s",s1,s2) && s1[0] != '#')
    {
        memset(_next,0,sizeof(_next));
        printf("%d\n", kmp_count(s2,strlen(s2),s1,strlen(s1)));
    }
    return 0;
}