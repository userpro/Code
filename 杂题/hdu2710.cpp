#include <iostream>
#include <string.h>
using namespace std;

const int N = 20005;

int main()
{
    int n, flag, s[N], a[N];
    int i,j;
    memset(s, 1, sizeof(s));
    for ( i = 2; i < N; ++i)
    {
        if (s[i])
            for ( j = i + i; j < N; j += i)
                s[j] = 0;
    }

    for ( i = 2, j = 2; i < N; ++i)
    {
        if(s[i])
            a[j++] = i;
    }
    a[1] = 1;
    memset(s, 0, sizeof(s));

    while (cin >> n)
    {
        int max = 0;
        for ( i = 1; i <= n; ++i)
            cin >> s[i];

        for ( i = 1; i <= n; ++i)
        {
            for ( j = 1; a[j] <= s[i]; ++j)
            {
                if (s[i] % a[j] == 0)
                {
                    if (max < a[j])
                    {
                        max = a[j];
                        flag = i;
                    }
                }
            }
        }
        cout << s[flag] << endl;
    }
    return 0;
}