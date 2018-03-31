#include <stdio.h>

int main()
{
    unsigned long long n, i, j, k, m, q;
    while (scanf("%llu %llu", &i, &j) != EOF && i!= 0)
    {
        printf("%llu %llu ", i, j);
        m = 0;
        q = 0;
        if (i > j) 
        {
            n = i;
            i = j;
            j = n;
        }
        for (n = i; n <= j; ++n)
        {
            q = n;
            k = 1;
            while (q != 1)
            {
                if (q % 2 != 0)
                    q = 3 * q + 1;
                else 
                    q = q / 2;
                k++;
            }
            if (m < k) m = k;
        }

        printf("%llu\n", m);
    }
    return 0;
}