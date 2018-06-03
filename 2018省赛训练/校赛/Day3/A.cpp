#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;
int m;

int main()
{
    int cnt=1;
    while (scanf("%d",&m)!=EOF)
    {
        printf("Case #%d: %d\n", cnt++, (int)(m*log10(2)));
    }
    return 0; 
}