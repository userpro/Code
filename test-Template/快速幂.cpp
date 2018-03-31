#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int base = 100007;
inline int power(int a, int b)
{
	int ans = 1;
	for (; b; b >>= 1)
	{
		if (b & 1) ans = ans * a % base;
		a = a * a % base;	
	}
	return ans;
}
int main()
{
	return 0;	
}
