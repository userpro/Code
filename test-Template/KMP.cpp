#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100000;
int p[maxn], ans, pos[maxn], sp;
char s[maxn], t[maxn], *a = s + 1, *b = t + 1;
int main()
{
	scanf("%s%s", a, b);
	int lens = strlen(a), lent = strlen(b), j = 0;
	for (int i = 2; i <= lent; i++)
	{
		while (j > 0 && t[j + 1] != t[i]) j = p[j];
		if (t[j + 1] == t[i]) j++;
		p[i] = j;
	}
	j = 0;
	for (int i = 1; i <= lens; i++)
	{
		while (j > 0 && t[j + 1] != s[i]) j = p[j];
		if (t[j + 1] == s[i]) j++;
		if (j == lent)
			ans++, pos[sp++] = i - lent + 1, j = p[j];
	}
	return 0;
}