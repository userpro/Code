#include <stdio.h>
#include <vector>
using namespace std;
#define MAX 10001
char N[MAX];

int main()
{
    int c, i, j;
    vector<int> v;
    memset(N, 0, sizeof(N));
    while (scanf("%s", N) != EOF && N[0] != '0')
    {
        c = 0;
        for (i = 0; i < strlen(N); ++i)
            c += N[i] - '0';
        while (c >= 10)
        {
            v.clear();
            while (c)
            {
                j = c % 10;
                c = c / 10;
                v.push_back(j);
            }
            for (i = 0; i < v.size(); ++i)
                c += v[i];
        }
        memset(N, 0, sizeof(N));
        printf("%d\n", c);
    }
    return 0;
}