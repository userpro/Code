//POJ 2135
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1000 + 2, maxm = 20000 + 2, INF = 0x7fffffff;
inline void gmin(int &a, const int &b) {if (a > b) a = b;}
queue<int> que;
int dist[maxn], source, sink, flow, mcost, pre[maxn];
bool vis[maxn];
struct arc
{
	int e, v, c;
	arc *next;
	arc(){}
	arc(int e, int v, int c, arc *next) : e(e), v(v), c(c), next(next){}
	void *operator new(unsigned, void *p) {return p;}	
}*head[maxn], mem[maxm << 1], *sp = mem, *last[maxn];
inline void addarc(int x, int y, int v, int c)
{
	head[x] = new(sp++) arc(y, v, c, head[x]);
	head[y] = new(sp++) arc(x, 0, -c, head[y]);
}
inline arc* rev(arc *p)
{
	return mem + ((p - mem) ^ 1);
}
inline bool SPFA()
{
	memset(dist, 0x7f, sizeof(dist));
	que.push(source);
	dist[source] = 0;
	vis[source] = true;
	while (!que.empty())
	{
		int F = que.front();
		que.pop();
		vis[F] = false;
		for (arc *p = head[F]; p; p = p -> next)
			if (p -> v > 0 && dist[p -> e] > dist[F] + p -> c)
			{	
				dist[p -> e] = dist[F] + p -> c;
				last[p -> e] = p; pre[p -> e] = F;
				if (!vis[p -> e]) que.push(p -> e), vis[p -> e] = true;	
			}
	}
	return dist[sink] < dist[0];
}
inline void SSPA()
{
	while (SPFA())
	{
		int aug = INF;
		for (int i = sink; last[i]; i = pre[i])
			gmin(aug, last[i] -> v);
		flow += aug; mcost += dist[sink] * aug;
		for (int i = sink; last[i]; i = pre[i])
			last[i] -> v -= aug, rev(last[i]) -> v += aug;
	}
}
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	source = n + 1; sink = n + 2;
	int a, b, c;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		addarc(a, b, 1, c);
		addarc(b, a, 1, c);
	}
	addarc(source, 1, 2, 0);
	addarc(n, sink, 2, 0);
	SSPA();
	printf("%d\n", mcost);
	return 0;
}