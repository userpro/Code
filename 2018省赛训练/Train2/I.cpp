#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
int T,H,W;
char buf[110][110];

int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            int ans=0;
            scanf("%d%d",&H,&W);
            for (int i=0;i<H;i++)
                scanf("%s",buf[i]);

            for (int i=0;i<H;i++)
            {
                for (int j=0;j<W;j++)
                {
                    if (buf[i][j]!='.')
                    {
                        if (buf[i][j]=='O')
                        {
                            if (i+1<H)
                            {
                                if (buf[i+1][j]=='|')
                                    buf[i+1][j]='.';
                                if (j-1>=0&&buf[i+1][j-1]=='/')
                                    buf[i+1][j-1]='.';
                                if (j+1<W&&buf[i+1][j+1]=='\\')
                                    buf[i+1][j+1]='.';
                            }
                            if (i+2<H)
                            {
                                if (j-1>=0&&buf[i+2][j-1]=='(')
                                    buf[i+2][j-1]='.';
                                if (j+1<W&&buf[i+2][j+1]==')')
                                    buf[i+2][j+1]='.';
                            }
                        }
                        else
                        if (buf[i][j]=='|')
                        {
                            if (j-1>=0&&buf[i][j-1]=='/')
                                buf[i][j-1]='.';
                            if (j+1<W&&buf[i][j+1]=='\\')
                                buf[i][j+1]='.';
                            if (i-1>=0)
                            {
                                if (buf[i-1][j]=='O')
                                    buf[i-1][j]='.';
                            }
                            if (i+1<H)
                            {
                                if (j-1>=0&&buf[i+1][j-1]=='(')
                                    buf[i+1][j-1]='.';
                                if (j+1<W&&buf[i+1][j+1]==')')
                                    buf[i+1][j+1]='.';
                            }
                        }
                        else
                        if (buf[i][j]=='/')
                        {
                            if (j+1<W&&buf[i][j+1]=='|')
                                buf[i][j+1]='.';
                            if (j+2<W&&buf[i][j+2]=='\\')
                                buf[i][j+2]='.';
                            if (i-1>=0)
                            {
                                if (j+1<W&&buf[i-1][j+1]=='O')
                                    buf[i-1][j+1]='.';
                            }
                            if (i+1<H)
                            {
                                if (buf[i+1][j]=='(')
                                    buf[i+1][j]='.';
                                if (j+2<W&&buf[i+1][j+2]==')')
                                    buf[i+1][j+2]='.';
                            }
                        }
                        else
                        if (buf[i][j]=='\\')
                        {
                            if (j-1>=0&&buf[i][j-1]=='|')
                                buf[i][j-1]='.';
                            if (j-2>=0&&buf[i][j-2]=='/')
                                buf[i][j-2]='.';
                            if (i-1>=0)
                            {
                                if (j-1>=0&&buf[i-1][j-1]=='O')
                                    buf[i-1][j-1]='.';
                            }
                            if (i+1<H)
                            {
                                if (buf[i+1][j]==')')
                                    buf[i+1][j]='.';
                                if (j-2>=0&&buf[i+1][j-2]=='(')
                                    buf[i+1][j-2]='.';
                            }
                        }
                        else
                        if (buf[i][j]=='(')
                        {
                            if (j+2<W&&buf[i][j+2]==')')
                                buf[i][j+2]='.';
                            if (i-1>=0)
                            {
                                if (buf[i-1][j]=='/')
                                    buf[i-1][j]='.';
                                if (j+1<W&&buf[i-1][j+1]=='|')
                                    buf[i-1][j+1]='.';
                                if (j+2<W&&buf[i-1][j+2]=='\\')
                                    buf[i-1][j+2]='.';
                            }
                            if (i-2>=0)
                            {
                                if (j+1<W&&buf[i-2][j+1]=='O')
                                    buf[i-2][j+1]='.';
                            }
                        }
                        else
                        if (buf[i][j]==')')
                        {
                            if (j-2>=0&&buf[i][j-2]=='(')
                                buf[i][j-2]='.';
                            if (i-1>=0)
                            {
                                if (buf[i-1][j]=='\\')
                                    buf[i-1][j]='.';
                                if (j-1>=0&&buf[i-1][j-1]=='|')
                                    buf[i-1][j-1]='.';
                                if (j-2>=0&&buf[i-1][j-2]=='/')
                                    buf[i-1][j-2]='.';
                            }
                            if (i-2>=0)
                            {
                                if (j-1>=0&&buf[i-2][j-1]=='O')
                                    buf[i-2][j-1]='.';
                            }
                        }
                        buf[i][j]='.';
                        ans++;
                    }
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0; 
}