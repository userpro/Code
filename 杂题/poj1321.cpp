#include <iostream>
#include <cstring>
using namespace std;
#define N 10

bool mp[N][N];
bool col[N];
int n, k, mcount;

void DFS(int x, int rest)
{
    if (rest == 0) 
    {
        mcount++;
        return;
    }
    if (x > n) return;
    for (int i = 0; i < n; ++i)
        if (!col[i] && mp[x][i])
        {
            col[i] = true;
            DFS(x + 1, rest - 1);
            col[i] = false;
        }

    if (rest + x < n)
        DFS(x + 1, rest);
}

int main()
{
    freopen("poj1321-data", "r", stdin);
    char c[N + 1];
    while (cin>>n>>k && n != -1 && k != -1)
    {
        memset(mp, false, sizeof(mp));
        memset(col, false, sizeof(col));
        for (int i = 0; i < n; ++i)
        {
            cin>>c;
            for (int j = 0; j < n; ++j)
                if (c[j] == '#') mp[i][j] = true;
        }
        mcount = 0;
        DFS(0, k);
        cout<<mcount<<endl;
    }
    return 0;
}