#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000 + 2;
int n, k;
template <int A, int B>
struct matrix
{
	int v[A][B];
	matrix(int r = 0)
	{
		memset(v, 0, sizeof(v));
		for (int i = 0; i < A && i < B; i++)
			v[i][i] = r;
	}
	matrix(int a[A][B])
	{
		memcpy(v, a, sizeof(a));
	}
};
template <int A, int B, int C>
matrix<A, C> operator * (const matrix<A, B> &a, const matrix<B, C> &b)
{
	matrix<A, C> c;
	for (int i = 0; i < A; i++)
		for (int j = 0; j < C; j++)
		{
			long long v = 0;
			for (int w = 0; w < B; w++)
				v += a.v[i][w] * b.v[w][j];
				c.v[i][j] = (v % k + k) % k;
		}
	return c;
}
template <int A>
matrix<A, A> power(matrix<A, A> a, int b)
{
	matrix<A, A> ans = 1;
	for (; b; b >>= 1)
	{
		if (b & 1) ans = ans * a;
		a = a * a;
	}
	return ans;
}
matrix<2, 2> a = 1;
matrix<1, 2> b;
int main()
{
	return 0;
}
