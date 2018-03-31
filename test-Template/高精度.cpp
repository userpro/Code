#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;
using namespace rel_ops;
const int Len = 255 + 2, base = 10000;
struct bint
{
	int len;
	int v[Len];
	bint(int r = 0) {for (len = 0; r > 0; r /= base) v[len++] = r % base;}
	bint &operator = (const bint &a)
	{
		memcpy(this, &a, sizeof(int) * (a.len + 1));
		return *this;
	}
	bool operator < (const bint &a) const
	{
		if (len != a.len) return len < a.len;
		for (int i = len - 1; i >= 0; i--)
			if (v[i] != a.v[i]) return v[i] < a.v[i];
		return false;
	}
	bool operator == (const bint &r)
	{
		if (len != r.len) return false;
		for (int i = len-1; i >= 0; i--)
			if (v[i] != r.v[i]) return false;
		return true;
	}
};
istream &operator >> (istream &in, bint &a)
{
	static char s[Len];
	scanf("%s", s);
	int len = strlen(s), u = 0, v = 1;
	for (int i = len - 1; i >= 0; i--)
	{
		u += (s[i] - '0') * v;
		v *= 10;
		if (v == base)
			a.v[a.len++] = u, u = 0, v = 1;	
	}
	if (v != 1) a.v[a.len++] = u;
	if (a.len == 1 && a.v[0] == 0) a.len = 0;
	return in;
}
ostream &operator << (ostream &out, const bint &a)
{
	printf("%d", a.len == 0 ? 0 : a.v[a.len - 1]);
	for (int i = a.len - 2; i >= 0; i--) printf("%04d", a.v[i]);
	return out;
}
bint operator + (const bint &a, const bint &b)
{
	bint ans = 0;
	int i, carry = 0;
	for (i = 0; i < a.len || i < b.len || carry > 0; i++)
	{
		if (i < a.len) carry += a.v[i];
		if (i < b.len) carry += b.v[i];
		ans.v[i] = carry % base;
		carry /= base;	
	}
	ans.len = i;
	return ans;
}
bint operator - (const bint &a, const bint &b)
{
	bint ans = 0;
	int carry = 0;
	for (int i = 0; i < a.len; i++)
	{
		if (i < b.len) carry += b.v[i];
		ans.v[i] = a.v[i] - carry;
		if (ans.v[i] < 0)
			ans.v[i] += base, carry = 1;	
		else
			carry = 0;
	}
	ans.len = a.len;
	while (!ans.v[ans.len - 1] && ans.len > 0) ans.len--;
	return ans;
}
bint operator * (const bint &a, const int &b)
{
	bint ans = 0;
	if (!a.len || !b) return ans;
	int carry = 0, i;
	for (i = 0; i < a.len || carry; i++)
	{
		if (i < a.len) carry += a.v[i] * b;
		ans.v[i] = carry % base;
		carry /= base;
	}
	ans.len = i;
	return ans;
}
bint operator * (const bint &a, const bint &b)
{
	bint ans = 0;
	if (a.len == 0 || b.len == 0) return ans;
	int carry, i, j;
	for (i = 0; i < a.len; i++)	
		for (j = carry = 0; j < b.len || carry > 0; j++)
		{
			if (j < b.len) carry += a.v[i] * b.v[j];
			if (i + j < ans.len)
				carry += ans.v[i + j], ans.v[i + j] = carry % base;
			else
				ans.v[ans.len++] = carry % base;
			carry /= base;
		}
	return ans;
}
bint operator / (const bint &a, const int &b)
{
	bint ans = a;
	int carry = 0;
	for (int i = ans.len - 1; i >= 0; i--)
	{
		ans.v[i] += carry * base;
		carry = ans.v[i] % b;
		ans.v[i] /= b;
	}
	while (!ans.v[ans.len - 1] && ans.len) ans.len--;
	return ans;
}
bint a, b;
int main()
{
	return 0;	
}
