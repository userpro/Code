#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

char s[20], t[20];

int main()
{
	int n = 10;
	for (int i = 1; i <= n; i++)
	{
		sprintf(s, "test%d.out", i);
		sprintf(t, "test%d.ans", i);
		rename(s, t);
	}
	return 0;
}
