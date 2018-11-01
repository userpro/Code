// 将问题数值化, 第 i 个问题回答 yes 所代表的数值为 1<<i 
// 则 c 个 Friends 都有唯一确定的一个数值与之对应
// 相应的, 若一个数值能够唯一确定一个 Friends , 则对于下列 n 个待确定名字的 Friends
// 同样将回答的 yes 数值化, 则可确定该 Friends 的名字；否则输出 Let's go to the library!!
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;
string name;
map<string, int> mp;
map<int, string> rev;
int t,n,q,c,m;

int main()
{
    scanf("%d",&t);
    while (t--)
    {
        mp.clear();
        rev.clear();
        scanf("%d%d%d",&n,&q,&c);
        for (int i=0;i<c;i++)
        {
            cin>>name;
            mp[name]=0;
        }
        for (int i=0;i<q;i++)
        {
            scanf("%d",&m);
            for (int j=0;j<m;j++)
            {
                cin>>name;
                mp[name]+=(1<<i);
            }
        }

        for (map<string, int>::iterator it = mp.begin(); it!=mp.end(); it++)
        {
            if (rev.find(it->second) == rev.end())
                rev[it->second]=it->first;
            else
                rev[it->second]="Let's go to the library!!";
        }

        for (int i=0;i<n;i++)
        {
            int val=0,tmp;
            for (int j=0;j<q;j++)
            {
                scanf("%d",&tmp);
                if (tmp) val+=(1<<j);
            }
            if (rev.find(val)==rev.end())
                printf("Let's go to the library!!\n");
            else
                printf("%s\n", rev[val].c_str());
        }
    }
    return 0;
}