#include <stdio.h>
#include <map>
using namespace std;

int main()
{
    map<int, int> m;
    map<int, int>::iterator it;
    int N, i, j, q1, q2;
    while (scanf("%d", &N) != EOF && N)
    {
        q1 = 0; q2 = 0;
        m.clear();
        for (i = 0; i < N; ++i)
        {
            scanf("%d", &j);
            m[j]++;
        }
        for (it = m.begin(); it != m.end(); ++it)
            if (it->second > q2)
            {
                q2 = it->second;
                q1 = it->first;
            }
        printf("%d\n", q1);
    }
    return 0;
}