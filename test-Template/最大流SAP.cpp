//POJ P1273
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200 + 2, maxm = 200 + 2, INF = 1 << 30;
#define clr(a) memset(a, 0, sizeof(a))
inline int MIN(const int &a, const int &b) {if (a > b) return b; return a;}
inline void gmin(int &a, const int &b) {if (a > b) a = b;}
struct arc
{
	int e, v;
	arc *next;
	arc(){}
	arc(int e, int v, arc *next) : e(e), v(v), next(next){}	
	void *operator new(unsigned, void *p) {return p;}
}*head[maxn], mem[maxm * 2], *sp = mem;
inline void addarc(int x, int y, int v)
{
	head[x] = new(sp++) arc(y, v, head[x]);
	head[y] = new(sp++) arc(x, 0, head[y]);
}
inline arc* rev(arc *p)
{
	return mem + ((p - mem) ^ 1);
}
int n, m, source, sink, dis[maxn], gap[maxn];
int DFS(int x, int aug)
{
	if (x == sink) return aug;
	int flow = 0, md = n - 1;
	for (arc *p = head[x]; p; p = p -> next) if (p -> v)
	{
		if (dis[x] == dis[p -> e] + 1)
		{
			int t = DFS(p -> e, MIN(aug - flow, p -> v));
			p -> v -= t;
			rev(p) -> v += t;
			flow += t;
			if (dis[source] >= n || flow == aug) return flow;
		}
		gmin(md, dis[p -> e]);
	}
	if (!flow)
	{
		if (!(--gap[dis[x]])) dis[source] = n;
		gap[dis[x] = md + 1]++;
	}
	return flow;
}
int SAP()
{
	int ans = 0;
	clr(gap); clr(dis);
	gap[0] = n;
	while (dis[source] < n)
		ans += DFS(source, INF);
	return ans;
}
int main()
{
	while(scanf("%d%d", &m, &n) != -1 && (n || m))
	{
		source = 1, sink = n;
		int a, b, c;
		sp = mem; clr(head);
		for (int i = 1; i <= m; i++)
			scanf("%d%d%d", &a, &b, &c), addarc(a, b, c);
		printf("%d\n", SAP());
	}
	return 0;
}
