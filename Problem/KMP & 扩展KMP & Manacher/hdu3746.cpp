/*
kmp循环节 len-next[len]
*/
#include <cstdio>
#include <cstring>

#define MAXN 100010
int T,len;
char s[MAXN];
int _next[MAXN];

void kmp_pre(char x[], int m)
{
    int i,j;
    j=_next[0]=-1;
    i=0;
    while (i<m)
    {
        while (j!=-1 && x[j]!=x[i]) j=_next[j];
        _next[++i]=++j;
    }
}

int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%s",s);
        memset(_next,0,sizeof(_next));
        len=strlen(s);
        kmp_pre(s,len);
        if (_next[len]==0)
            printf("%d\n", len);
        else if (len%(len-_next[len])==0)
            printf("0\n");
        else
        {
            int tmp = len-_next[len];
            printf("%d\n", tmp-len%tmp);
        }
    }
    return 0;
}