#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10001;
struct Heap
{
	int size, v[maxn], tmp;
	inline void swap(int &a, int &b) {tmp = a, a = b, b = tmp;}
	int operator [] (int k) {return v[k];}
	inline bool empty() {return !size;}
	inline int top() {return v[1];}
	inline void up(int a)
	{
		while (a != 1)
		{
			if (v[a] < v[a >> 1]) swap(v[a], v[a >> 1]); else break;
			a >>= 1;
		}
	}
	inline void down(int a)
	{
		a <<= 1;
		while (a <= size)
		{
			if (a < size && v[a + 1] < v[a]) a++;
			if (v[a] < v[a >> 1]) swap(v[a], v[a >> 1]); else break;
			a <<= 1;	
		}
	}
	inline void push(const int &x)
	{
		v[++size] = x;
		up(size);
	}
	inline void pop()
	{
		v[1] = v[size--];
		down(1);	
	}
	inline void del(int a)
	{
		v[a] = v[size--];
		down(a);
		up(a);	
	}	
}heap;
int main()
{

	return 0;
}
