// 每新增一条直线，都将原来所有的区域分成两半，因此第n条直线会在原来的基础
// 上再添加n个平面
// 结论:
//     直线:
//         最多可分为(1/2)*n*(n+1)+1块区域
//     折线:
//         最多可以分成（2×n^2-n+1）块区域

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int c,a;

int main()
{
    while (scanf("%d",&c)!=EOF)
    {
        for (int i=0;i<c;i++)
        {
            scanf("%d",&a);
            printf("%d\n", 2*a*a-a+1);
        }
    }
    return 0;
}