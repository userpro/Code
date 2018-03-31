#include <cstdio>

int main()
{
    long long n, m, a, n1, m1;
    while (scanf("%lld%lld%lld", &n, &m, &a) != EOF && n)
    {
        if (n % a) n1 = n / a + 1;
        else n1 = n / a;
        if (m % a) m1 = m / a + 1;
        else m1 = m / a;
        printf("%lld\n", n1 * m1);
    }
    return 0;
}