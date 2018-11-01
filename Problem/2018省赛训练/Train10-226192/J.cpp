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

#define MAX 2010
int N;
int num[MAX];
int main()
{
    int a;
    CLR(num,0);
    num[0]=32;
    num[1]=16; num[2]=8; num[4]=4; num[8]=2; num[16]=1;
    while (scanf("%d",&N)!=EOF)
    {
        int ans=0;
        for (int i=0;i<N;i++)
        {
            scanf("%d",&a);
            ans+=num[a];
        }
        int end = ans % 16;
        printf("%d", ans/16);
        switch(end)
        {
            case 0: printf("\n");break;
            case 1: printf(".0625\n");break;
            case 2: printf(".125\n");break;
            case 3: printf(".1875\n");break;
            case 4: printf(".25\n");break;
            case 5: printf(".3125\n");break;
            case 6: printf(".375\n");break;
            case 7: printf(".4375\n");break;
            case 8: printf(".5\n");break;
            case 9: printf(".5625\n");break;
            case 10: printf(".625\n");break;
            case 11: printf(".6875\n");break;
            case 12: printf(".75\n");break;
            case 13: printf(".8125\n");break;
            case 14: printf(".875\n");break;
            case 15: printf(".9375\n");break;
        }
    }
    return 0;
}