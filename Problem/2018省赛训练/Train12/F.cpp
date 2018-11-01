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

#define MAX 200010

struct number
{
    LL num;
    int index;
};

bool _cmp(const number &a, const number &b) {return a.num < b.num;}

number num[MAX];
LL _num[MAX];

int main()
{
    int i, n, k;
    LL x;
    while(scanf("%d%d%lld", &n, &k, &x) != EOF)
    {
        CLR(num, 0);CLR(_num, 0);
        for(i=0; i<n; i++) scanf("%lld", &_num[i]);
        for( i=0; i<n; i++) {num[i].index = i+1; num[i].num = _num[i];}
        sort(num, num+n, _cmp);
        if(num[0].num - k * x <= 0)
        {
            int oper = num[0].num / x;
            if(num[0].num - oper * x >= 0 && oper < k) oper++;
            k -= oper;
            num[0].num -= oper * x;
            _num[num[0].index-1] -= oper*x;
        }
        else
        {
            num[0].num -= k * x;
            _num[num[0].index-1] -= k*x;
            k = 0;
        }
        while(k > 0)
        {
            for(i=1; num[i].num >= num[i+1].num; i++);
            if(i == n) i = n-1;
            int oper = (max(num[i-1].num, num[i+1].num) - num[i].num) / x + 1;
            k -= oper;
            num[i].num += oper * x;
            _num[num[i].index-1] += oper*x;
        }
        printf("%lld", _num[0]);
        for(i=1; i<n; i++) printf(" %lld", _num[i]);
        putchar('\n');
    }
    return 0;
}