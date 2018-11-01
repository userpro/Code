#include <cstdio>
int main()
{
int n, zero=0, one=0;
char bin[105];
scanf("%d%s", &n, bin);
for(int i=0; i<n; i++) if(bin[i] == '0') zero++;else if(bin[i] == '1') one++;
if(one) putchar('1');for(int i=0; i<zero; i++) putchar('0');
return 0;
}