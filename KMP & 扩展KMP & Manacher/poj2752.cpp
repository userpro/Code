/*
利用next数组 不断回溯 j=next[j]

    --  --
    ------  ------
    --------------

*/
#include <stdio.h>
#include <string.h>

#define MAXN 400010
char s[MAXN];
int _next[MAXN], ans[MAXN];
int slen, cnt;

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
    while (scanf("%s", s) != EOF)
    {
        memset(_next,0,sizeof(_next));
        memset(ans,0,sizeof(ans));
        slen=strlen(s);
        kmp_pre(s,slen);
        cnt=0;
        int t=_next[slen-1];
        while (t!=-1)
        {
            if (s[t]==s[slen-1]) ans[cnt++]=t+1;
            t=_next[t];
        }
        for (int i = cnt-1; i >= 0; --i)
            printf("%d ", ans[i]);
        printf("%d\n",slen);
    }
    return 0;
}