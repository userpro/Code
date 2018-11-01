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

int main()
{
    bool up, flag;
    int t, n, a, last, i;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        up = true;flag = true;
        last = 0;
        for(i=0; i<n; i++)
        {
            scanf("%d", &a);
            if(up && a < last) {up = false; if(i == 1) flag = false;}
            else if(!up && a >= last) flag = false;
            last = a;
        }
        if(flag && !up) printf("Yes\n");else printf("No\n");
    }
    return 0;
}
