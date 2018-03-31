#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 300000 + 2, INF = 0x7fffffff;
inline void gmax(int &a, const int &b) {if (a < b) a = b;}
struct SegT
{
	SegT *ls, *rs;
	int l, r, Max, lazy;
	inline void update() {Max = max(ls -> Max, rs -> Max);}
	inline void add(int x) {Max += x; lazy += x;}
	inline void pushdown() {ls -> add(lazy); rs -> add(lazy); lazy = 0;}
	inline void cover(int left, int right, int x)
	{
		if (left <= l && right >= r) {add(x); return;}
		pushdown();
		int mid = (l + r) >> 1;
		if (left <= mid) ls -> cover(left, right, x);
		if (right > mid) rs -> cover(left, right, x);
		update();
	}
	inline int query(int left, int right)
	{
		if (left <= l && right >= r) return Max;
		pushdown();
		int mid = (l + r) >> 1, ans = -INF;
		if (left <= mid) gmax(ans, ls -> query(left, right));
		if (right > mid) gmax(ans, rs -> query(left, right));
		return ans;
	}
}T[maxn << 1], *p = T, *root;
int n, m, d[maxn];
inline void build(SegT *&node, int left, int right)
{
	node = p++; node -> l = left; node -> r = right;
	if (left == right) {node -> Max = d[left]; return;}
	int mid = (left + right) >> 1;
	build(node -> ls, left, mid);
	build(node -> rs, mid + 1, right);
	node -> update();	
}
int main()
{

	return 0;
}