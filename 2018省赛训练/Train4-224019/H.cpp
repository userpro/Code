#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

int x;
LL e[11];

LL getNum(LL raw, int operate)
{
    LL res = 0;
    for(int i=x-1; i>=0; i--) if((1<<i) & operate) res = res * 10 + raw % e[i+1] / e[i];
    return res;
}

int operateCount(int operate)
{
    int c = 0;
    for(int i=0; i<x; i++) if((1<<i) & operate) c++;
    return x - c;
}

int main()
{
    LL n;
    int i, m, _min;
    e[0] = 1;
    for(int i=1; i<=10; i++) e[i] = e[i-1] * 10;
    while(cin >> n)
    {
        x = ((int)log10(n)) + 1;
        _min = INF;
        m = 1 << x;
        for(int i=1; i<m; i++)
        {
            LL res = getNum(n, i);
            if(res == 0) continue;
            // cout << res << endl;
            LL s = (LL) sqrt(res);
            if(res == s * s) {int oc = operateCount(i);if(res / e[x-oc-1])_min = min(_min, oc);}
        }
        if(_min == INF) cout << -1 << endl; else cout << _min << endl;

    }
    return 0;
}