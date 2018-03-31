#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10000000 + 2;
int n, used[maxn], p[maxn], s;
int main()
{
	cin >> n;
	for (int i = 2; i <= n; i++)
	{
		if (!used[i]) p[++s] = i;
		for (int j = 1; j <= s && p[j] * i <= n; j++)
		{
			used[p[j] * i] = p[j];
			if (p[j] == used[i]) break;
		}
	}
	cout << p[s] << endl;
	return 0;	
}
