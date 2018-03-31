#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
const int maxn = 10000 + 2, maxm = 100000 + 2;
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
	head[y] = new(sp++) arc(x, v, head[y]);
}
int dist[maxn], s, t, n, m;
bool vis[maxn];
priority_queue<pii, vector<pii >, greater<pii > > heap;
int Dij(int x)
{
	memset(dist, 0x7f, sizeof(dist));
	dist[x] = 0;
	for (int i = 1; i < n; i++)
	{
		vis[x] = true;
		for (arc *p = head[x]; p; p = p -> next)
			if (dist[x] + p -> v < dist[p -> e])
				dist[p -> e] = dist[x] + p -> v, heap.push(MP(dist[p -> e], p -> e));
		if (x == t) return dist[x];
		while (!heap.empty() && vis[heap.top().se]) heap.pop();
		x = heap.top().se;
	}
	return dist[t];
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	int a, b, c;
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &a, &b, &c), addarc(a, b, c);
	printf("%d\n", Dij(s));
	return 0;	
}
