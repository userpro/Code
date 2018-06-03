#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    int a;
    while (scanf("%d",&a)!=EOF)
    {
        if (a%2==0)
            printf("Mahmoud\n");
        else
            printf("Ehab\n");
    }
    return 0;
}