#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 10000 + 2, maxm = 100000 + 2;
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
priority_queue<pii, vector<pii >, greater<pii > > heap;
int n, m, dist[maxn], s, t;
bool vis[maxn];
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
int Prim(int x)
{
	memset(dist, 0x7f, sizeof(dist));
	dist[x] = 0;
	int ans = 0;
	for (int i = 1; i < n; i++)
	{
		vis[x] = true;
		for (arc *p = head[x]; p; p = p -> next)
			if (dist[p -> e] > p -> v)
				dist[p -> e] = p -> v, heap.push(MP(dist[p -> e], p -> e));
		while (!heap.empty() && vis[heap.top().se]) heap.pop();
		x = heap.top().se;
		ans += dist[x];
	}
	return ans;
}
int main()
{
	freopen("Prim.in", "r", stdin);
	freopen("Prim.out", "w", stdout);
	scanf("%d%d", &n, &m);
	int a, b, c;
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &a, &b, &c), addarc(a, b, c);
	printf("%d\n", Prim(1));
	fclose(stdin);
	fclose(stdout);
	return 0;	
}
