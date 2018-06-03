// ZOJ 3939
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
#define LL long long
map<LL,LL> mp;
struct Node
{
    int y,m,d;
};
vector<Node> ans;

bool isMonday(int year,int month,int day)
{
    if(month < 3) { year -= 1;  month += 12; }
    int c = int (year / 100), y = year - 100 * c;
    int w = int ( c / 4) - 2 * c + y + int ( y / 4 ) +(26 * ( month + 1 ) / 10) + day - 1;
    w = (w % 7 + 7) % 7;

    if (w == 1) return 1;
    else return 0;
}

void solve()
{
    for (int i=1600;i<=1999;i++)
        for (int j=1;j<=12;j++)
        {
            Node tmp;
            LL num=0;
            if (isMonday(i,j,1))
            {
                tmp.y=i; tmp.m=j; tmp.d=1;
                ans.push_back(tmp);
                num=i*10000+j*100+tmp.d;
                mp[num]=ans.size()-1;
            }
            if (isMonday(i,j,11))
            {
                tmp.y=i; tmp.m=j; tmp.d=11;
                ans.push_back(tmp);
                num=i*10000+j*100+tmp.d;
                mp[num]=ans.size()-1;
            }
            if (isMonday(i,j,21))
            {
                tmp.y=i; tmp.m=j; tmp.d=21;
                ans.push_back(tmp);
                num=i*10000+j*100+tmp.d;
                mp[num]=ans.size()-1;
            }
        }
}

int t,y,m,d,n;
int main()
{
    solve();
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d%d%d",&y,&m,&d,&n);
        int a=400;
        int b=ans.size();

        int yy= (y-1600) % a + 1600;

        LL num= yy*10000 + m*100 + d;
        int pos= mp[num];

        int e_pos= (pos+n-1) % b;
        int ns= (pos+n-1) / b;

        printf("%d %d %d\n", y + ans[e_pos].y - ans[pos].y + ns*a, ans[e_pos].m, ans[e_pos
            ].d);
    }
    return 0;
}