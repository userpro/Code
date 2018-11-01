#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAX 300005
#define MUL 100000000

int main()
{
    int t, n, m, w, res;
    int mj[MAX];
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        w = -1;
        for(int i=0; i<n; i++)
        {
            char sc[2], c;int tmp;
            scanf("%s", sc);c = sc[0];
            if(c == 'W') {mj[i] = 0; w = i;}
            else
            {
                scanf("%d", &tmp);
                if(c == 'C') tmp += 1 * MUL;
                else if(c == 'B') tmp += 2 * MUL;
                else tmp += 3 * MUL;
                mj[i] = tmp;
            }
        }
        int mj_max = 3 * MUL + m + 1;
        res = 1;
        if(n == 3*m+1)
            res = 1;
        else if(mj[0] > mj[1] && w != 1)
            res = 1;
        else if(w == 0)
        {
            if(n == 1)
            {
                res = 3 * m;}
            else
            {
                res = (mj[1] / MUL - 1) * m + (mj[1] % MUL - 1);
            }
        }
        else if(w == n-1)
        {
            res = ((mj_max / MUL) - (mj[w-1] / MUL)) * m + mj_max % MUL - mj[w-1] % MUL - 1;
            if(w == 1)
            {res ++;}
        }
        else if(w == -1)
        {res = 3 * m - n + 1;}
        else
        {
            res = ((mj[w+1] / MUL) - (mj[w-1] / MUL)) * m + mj[w+1] % MUL - mj[w-1] % MUL - 1;
            if(w == 1)
            {res ++;}
        }
        if(res < 1) res = 1;
        printf("%d\n", res);

    }
    return 0;
}