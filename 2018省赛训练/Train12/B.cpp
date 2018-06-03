#include <cstdio>
#define LL long long
int main()
{
int n, m, x, y;
LL k;
while(scanf("%d%d%lld", &n, &m, &k) != EOF)
{
if(k<n) {x = k+1; y = 1;}
else
{
x = n - (k-n)/(m-1);
if(x & 1) y = m - (k-n) % (m-1);
else y = (k-n) % (m-1) + 2;
}
printf("%d %d\n", x, y);
}
return 0;
}