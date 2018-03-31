#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10000 + 2, maxm = 100000 + 2;
int n, m;
struct arc
{
	int b, e, v;
	arc(){}
	arc(int b, int e, int v) : b(b), e(e), v(v){}
}e[maxm], *sp = e;
inline void addarc(int b, int e, int v)
{
	*(sp++) = arc(b, e, v);	
}

inline bool comp(arc a, arc b)
{
	return a.v < b.v;
}

struct UFset
{
	int root[maxn];
	inline void init()
	{
		for (int i = 1; i <= n; i++)
			root[i] = i;	
	}
	inline int find(int x)
	{
		return root[x] == x ? x : root[x] = find(root[x]);
	}
	inline bool merge(int x, int y)
	{
		if (find(x) == find(y)) return false;
		root[find(x)] = find(y);
		return true;
	}
}U;

inline int Kruskal()
{
	int ans = 0;
	sort(e + 1, e + m + 1, comp);
	U.init();
	for (int i = 0, j = 1; j < n; i++)
		if (U.merge(e[i].b, e[i].e)) ans += e[i].v, j++;
	return ans;
}
int main()
{
	freopen("Kruskal.in", "r", stdin);
	freopen("Kruskal.out", "w", stdout);
	scanf("%d%d", &n, &m);
	int a, b, c;
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &a, &b, &c), addarc(a, b, c);
	printf("%d\n", Kruskal());
	fclose(stdin);
	fclose(stdout);
	return 0;	
}
