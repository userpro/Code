#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200000 + 2, l = 0, r = 1;
struct Snode
{
	Snode *p, *ch[2];
	int size, v, num, lazy;
	inline bool dir() {return p -> ch[r] == this;}
	inline void add(const int &x) {v += x; lazy += x;}
	inline void pushdown() {ch[l] -> add(lazy); ch[r] -> add(lazy); lazy = 0;}
	inline void update() {size = num + ch[l] -> size + ch[r] -> size;}
	inline void set_l(Snode *x) {ch[l] = x; x -> p = this;}
	inline void set_r(Snode *x) {ch[r] = x; x -> p = this;}
	inline void set_s(Snode *x) {if (x -> v < v) set_l(x); else set_r(x);}
	inline void rotate()
	{
		bool d = dir();
		Snode *x = p, *y = x -> p;
		x -> ch[d] = ch[!d]; ch[!d] -> p = x;
		ch[!d] = x; x -> p = this;
		y -> set_s(this);
		x -> update();
	}
	inline Snode *rank(const int &k)
	{
		pushdown();
		if (ch[r] -> size < k && ch[r] -> size + num >= k) return this;
		if (ch[r] -> size + num < k) return ch[l] -> rank(k - ch[r] -> size - num);
		else return ch[r] -> rank(k);
	}
}T[maxn], *sp = T, *root = T, *nil = T;
inline void splay(Snode *&node, Snode *x, Snode *y)
{
	while (x -> p != y)
	{
		if (x -> p -> p != y) x -> p -> p -> pushdown();
		x -> p -> pushdown(); x -> pushdown();
		if (x -> p -> p == y)
			x -> rotate();
		else
			if (x -> dir() == x -> p -> dir())
				x -> p -> rotate(), x -> rotate();
			else
				x -> rotate(), x -> rotate();
	}
	if (y == nil) node = x;
	x -> update();
}
inline void newnode(Snode *&node, const int &x)
{
	node = ++sp; node -> v = x; node -> size = node -> num = 1;
	node -> p = node -> ch[l] = node -> ch[r] = nil;
}
inline void insert(Snode *&node, const int &a)
{
	Snode *last = nil, *now = node, *x;
	newnode(x, a);
	if (node == nil) {node = x; return;}
	while (now != nil)
	{
		now -> pushdown();
		if (now -> v == a)
			{now -> num++; now -> size++; splay(root, now, nil); sp--; return;}
		last = now;
		if (a < now -> v) now = now -> ch[l]; else now = now -> ch[r];
	}
	last -> set_s(x);
	splay(node, x, nil);
}
inline int del(Snode *node)
{
	if (node == nil) return 0;
	node -> p -> ch[node -> dir()] = nil;
	node -> p -> update();
	return node -> size;
}
inline Snode *succ(Snode *node, const int &x)
{
	Snode *now = node, *last = nil;
	while (now != nil)
	{
		now -> pushdown();
		if (now -> v >= x)
			last = now, now = now -> ch[l];
		else
			now = now -> ch[r];
	}
	return last;
}
int n, MIN, k, ans;
int main()
{
	scanf("%d%d", &n, &MIN);
	char t;
	for (int i = 1; i <= n; i++)
	{
		scanf(" %c %d", &t, &k);
		if (t == 'I')
			{if (k < MIN) continue; else insert(root, k);}
		if (t == 'A') root -> add(k);
		if (t == 'S')
		{
			root -> add(-k);
			Snode *tmp = succ(root, MIN);
			if (tmp == nil) {ans += root -> size; root = nil; continue;}
			splay(root, tmp, nil);
			ans += del(root -> ch[l]);
		}
		if (t == 'F')
			printf("%d\n", root -> size < k ? -1 : root -> rank(k) -> v);
	}
	printf("%d\n", ans);
	return 0;
}