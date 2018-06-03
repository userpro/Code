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

#define MAX 100005

int main()
{
    char sex[MAX], room[MAX];
    bool used[MAX];
    int t, n, i, h, s, next;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        scanf("%s", sex+1);
        CLR(used, 0);
        if(n%4 && (n+1)%4) {printf("-1\n");continue;}
        // h = (1 + n) * n / 4;
        s = 0;
        int start, end;
        if(n & 1)
        {
            room[n] = (sex[n]=='0') ? '1' : '3';
            room[1] = (sex[1]=='0') ? '2' : '4';
            room[n-1] = (sex[n-1]=='0') ? '2' : '4';
            start = 2; end = n-2;
        }
        else {start = 1; end = n;}
        bool G = true;
        while(start < end)
        {
            if(G) 
            {
                room[start] = (sex[start]=='0') ? '2' : '4';
                room[end] = (sex[end]=='0') ? '2' : '4';
            }
            else
            {
                room[start] = (sex[start]=='0') ? '1' : '3';
                room[end] = (sex[end]=='0') ? '1' : '3';
            }
            start++;end--;G = !G;
        }
        for(i=1; i<=n; i++) putchar(room[i]);
        putchar('\n');
    }
    return 0;
}