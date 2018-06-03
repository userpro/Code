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

struct PP
{
    int type;
    int row;
    char col;
} White[100],Black[100];
char mp[50][50];
int num[256];

bool _cmp_white(const PP& p1,const PP& p2)
{
    if (p1.type==p2.type)
    {
        if (p1.row==p2.row)
            return p1.col<p2.col;
        return p1.row<p2.row;
    }
    return p1.type<p2.type;
}

bool _cmp_black(const PP& p1,const PP& p2)
{
    if (p1.type==p2.type)
    {
        if (p1.row==p2.row)
            return p1.col<p2.col;
        return p1.row>p2.row;
    }
    return p1.type<p2.type;
}

int main()
{
    char C[100]; char WD[256],BD[256];
    WD[1]='K'; WD[2]='Q'; WD[3]='R'; WD[4]='B'; WD[5]='N'; WD[6]='P';
    BD[1]='K'; BD[2]='Q'; BD[3]='R'; BD[4]='B'; BD[5]='N'; BD[6]='P';
    num['k']=num['K']=1;
    num['q']=num['Q']=2;
    num['r']=num['R']=3;
    num['b']=num['B']=4;
    num['n']=num['N']=5;
    num['p']=num['P']=6;
    C[1]='a'; C[2]='b'; C[3]='c'; C[4]='d';
    C[5]='e'; C[6]='f'; C[7]='g'; C[8]='h';
    for (int i=1;i<=17;i++)
        scanf("%s",mp[i]+1);

    int len=strlen(mp[1]+1);
    int white_cnt=0,black_cnt=0;
    int _row=0;
    for (int i=1;i<=17;i++)
    {
        int _col=0;
        if (mp[i][1]=='+')
            _row++;
        for (int j=1;j<=len;j++)
        {
            if (mp[i][j]=='+'||mp[i][j]=='|')
            {
                _col++;
                continue;
            }
            else if (mp[i][j]=='.'||mp[i][j]==':')
                continue;
            else if (mp[i][j]>='a' && mp[i][j]<='z')
            {
                // Black
                Black[black_cnt].type=num[mp[i][j]];
                Black[black_cnt].col=C[_col];
                Black[black_cnt].row=_row;
                black_cnt++;
            }
            else if (mp[i][j]>='A' && mp[i][j]<='Z')
            {
                // White
                White[white_cnt].type=num[mp[i][j]];
                White[white_cnt].col=C[_col];
                White[white_cnt].row=_row;
                white_cnt++;
            }
        }
    }

    sort(Black,Black+black_cnt,_cmp_white);
    sort(White,White+white_cnt,_cmp_black);
    printf("White: ");
    for (int i=0;i<white_cnt;i++)
    {
        if (White[i].type==num['P'])
            printf("%c%d", White[i].col,9-White[i].row);
        else
            printf("%c%c%d", WD[White[i].type],White[i].col,9-White[i].row);
        if (i!=black_cnt-1)
            printf(",");
    }
    printf("\n");
    printf("Black: ");
    for (int i=0;i<black_cnt;i++)
    {
        if (Black[i].type==num['p'])
            printf("%c%d", Black[i].col,9-Black[i].row);
        else
            printf("%c%c%d", BD[Black[i].type],Black[i].col,9-Black[i].row);
        if (i!=black_cnt-1)
            printf(",");
    }
    printf("\n");
    return 0;
}