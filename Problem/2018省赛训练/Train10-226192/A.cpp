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

int gcd(int a, int b){if (b == 0) return a;return gcd(b, a%b);}
int lcm(int a, int b){return a*b/gcd(a,b);}


int main()
{
    int n, all, i, j, _min;
    int p[25][3];
    bool night[200000];
    while(scanf("%d", &n) != EOF)
    {
        for(i=0; i<n; i++) scanf("%d%d%d", &p[i][0], &p[i][1], &p[i][2]);
        all = 1825 * 100;
        CLR(night, 1);
        for(j=0; j<n; j++)   // i: day
        {
            bool nht = p[j][1] < p[j][2];
            for(i=0; i<=all; i++)  // j: planet
            {
                if(i % p[j][0] == p[j][2]) nht = true;
                else if(i % p[j][0] == p[j][1]+1) nht = false;
                // night[i] = night[i] && nht;
                if(!nht) night[i] = false;
            }
        }
        bool flag = false;
        for(i=0; i<=all; i++) if(night[i]) {flag = true; break;}
        if(flag) printf("%d\n", i);
        else printf("impossible\n");
    }
    return 0;
}
