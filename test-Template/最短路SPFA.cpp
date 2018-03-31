/*********************************************
可以求带有负权的无环图中的最短路
若是没有负权，不保证无环的话，vis改为int类型记录进出队列的次数，vis[i] > 2 * n 说明有环
可以求最长路 
*********************************************/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 10000 + 2, maxm = 100000 + 2;
queue<int> que;
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
inline int SPFA(int x)
{
	memset(dist, 0x7f, sizeof(dist));
	que.push(x);
	dist[x] = 0;
	vis[x] = true;
	while (!que.empty())
	{
		int F = que.front();
		que.pop();
		vis[F] = false;
		for (arc *p = head[F]; p; p = p -> next)
			if (dist[p -> e] > dist[F] + p -> v)
			{	
				dist[p -> e] = dist[F] + p -> v;
				if (!vis[p -> e]) que.push(p -> e), vis[p -> e] = true;	
			}
	}
	return dist[t];
}

int main()
{
	scanf("%d%d", &n, &m);
	int a, b, c;
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &a, &b, &c), addarc(a, b, c);
	scanf("%d%d", &s, &t);
	printf("%d\n", SPFA(s));
	fclose(stdin);
	fclose(stdout);
	return 0;	
}
