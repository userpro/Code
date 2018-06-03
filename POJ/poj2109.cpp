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
#define EPS 0.000000000001

double n,p;
int main()
{
    while (scanf("%lf%lf",&n,&p)!=EOF)
    {
        cout<<pow(p,1/n)<<endl;
    }
    return 0;
}

// #define MAXK 1000000010
// double n,p;
// int main()
// {
//     while (scanf("%lf%lf",&n,&p)!=EOF)
//     {
//         LL l,r,mid;
//         double tmp;
//         l=0, r=MAXK;
//         while (r-l>EPS)
//         {
//             mid=(l+r)>>1;
//             tmp=pow(mid,n);
//             if (tmp-p>0)
//                 r=mid;
//             else if (tmp-p<0)
//                 l=mid;
//             else
//             {
//                 cout<<mid<<endl;
//                 break;
//             }
//         }
//     }
//     return 0;
// }