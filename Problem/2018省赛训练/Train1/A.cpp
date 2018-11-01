#include <stdio.h>
#include <string.h>

int T,n;

char tmp[1000];
int main()
{
    int ans=0;
    int a,b;
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            ans=0;
            scanf("%d%s",&n,tmp);
            int mon=0;
            if (tmp[0]=='I')
                mon=200;
            else
                mon=400;
            for (int i=0;i<n;i++)
            {
                scanf("%s",tmp);
                if (tmp[0]=='T')
                    ans+=300;
                else if (tmp[0]=='B')
                {
                    scanf("%d",&a);
                    ans+=a;
                }
                else if (!strcmp(tmp, "CONTEST_WON"))
                {
                    scanf("%d",&a);
                    ans+=300;
                    b=20-a>0?20-a:0;
                    ans+=b;
                }
                else if (!strcmp(tmp, "CONTEST_HOSTED"))
                    ans+=50;
            }
            printf("%d\n", ans/mon);
        }
    }
    return 0; 
}