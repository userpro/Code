// ZOJ 3936
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int T,A,B,C,D;

int main()
{
    while (scanf("%d",&T)!=EOF)
    {
        while (T--)
        {
            scanf("%d%d%d%d",&A,&B,&C,&D);
            printf("%d %d\n", C,B+D);
            printf("%d %d\n", A,B+D);
        }
    }
    return 0;
}