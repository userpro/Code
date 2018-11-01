/*
kmp循环节
*/

#include <stdio.h>
#include <string.h>

#define MAXN 1000010
char s[MAXN];
int _next[MAXN];
int len,lop;

void kmp_pre(char s[], int m)
{
    int i,j;
    j=_next[0]=-1;
    i=0;
    while (i<m)
    {
        while (j!=-1 && s[i]!=s[j]) j=_next[j];
        _next[++i]=++j;
    }
}

int main()
{
    while (scanf("%s", s))
    {
        if (s[0] == '.') break;
        memset(_next,0,sizeof(_next));
        len=strlen(s);
        kmp_pre(s, len);
        if (_next[len]==0 || len%(len-_next[len])!=0)
            printf("1\n");
        else
            printf("%d\n", len/(len-_next[len]));
    }
    return 0;
}