#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 1010
int n;

int main()
{
    while (scanf("%d",&n)!=EOF && n)
    {
        int a;
        int sg=0;
        for (int i=0;i<n;i++)
        {
            scanf("%d",&a);
            sg^=a;
        }
        if (sg) printf("Rabbit Win!\n");
        else printf("Grass Win!\n");
    }
    return 0;
}