## 常见数值类型范围

```
类型          长度 (bit)           有效数字          绝对值范围
float         32                  6~7              10^(-37) ~ 10^38
double        64                  15~16            10^(-307) ~10^308
long double   128                 18~19            10^(-4931) ~ 10 ^ 4932
```

## C++:
### `upper_bound` && `lower_bound`:
	upper_bound(i) 返回的是键值为i的元素可以插入的最后一个位置（上界） 
	lower_bound(i) 返回的是键值为i的元素可以插入的位置的第一个位置（下界）
	
	举例: 
	在升序的set里面 ,set里没有元素i的时候,两个元素的返回值是一样的 
	1 2 4 5 这个序列,upp（3）和low（3）都返回位置2（下标）
	
	如果只有一个元素i，low返回那个元素的位置，而upp返回那个元素的位置的后一个位置. 
	1 2 4 5 这个序列upp（2）返回下标2而low（2）返回下标1
	
	多个元素i, low返回那个元素的位置, upp返回那多个元素中的最后一个的后一个位置. 
	1 2 2 4 5 这个序列 upp（2）返回下标3的位置，low（2）返回下标1的位置.
	
	特别注意:举例在一个升序的容器里，如果所有元素都大于i则，upp和low都返回begin. 都小于i则返回end(越界了).

## 数论:
### 同余定理:
    (a + b) mod n = ((a mod n) + (b mod n)) mod n;
    (a - b) mod n = ((a mod n) - (b mod n) + n) mod n;
    ab mod n = (a mod n) (b mod n) mod n

### 唯一分解定理的运用:
    x = b ^ P 求P的最大值(-2^31<=x<=2^31)
    x = p1 ^ s1 * p2 ^ s2 * …… * pk ^ sk
    P = gcd(s1, s2, ……, sk)
    if x为质数 than P=1
    if(x<0) P只能为奇数，while(n%2==0) P/=2

### 拓展欧几里得算法应用:
* #### 使用扩展欧几里德算法解决不定方程的办法:

		对于不定整数方程 ax + by = c, 若 c mod gcd(a, b) = 0, 则该方程存在整数解, 否则不存在整数解.
	​	利用扩展欧几里得找到 ax + by = gcd(a, b) 的一组解 x0, y0 后, ax + by = gcd(a, b) 的其他整数解满足:
	​		x = x0 + b / gcd(a, b) * t
	​		y = y0 - a / gcd(a, b) * t 
	​		(其中t为任意整数, x0 y0 是方程一组特解)
	​	至于 ax + by = c 的整数解, 只需将 ax + by = gcd(a, b) 的每个解乘上 c / gcd(a, b) 即可.
	​	
	​	在找到 ax + by = gcd(a, b) 的一组解 x0, y0 后，应该是得到 ax + by = c 的一组解 
	​		x1 = x0 * (c / gcd(a, b)), 
	​		y1 = y0 * (c / gcd(a, b)),
	​	ax + by = c 的其他整数解满足:
	​		x = x1 + b / gcd(a, b) * t
	​		y = y1 - a / gcd(a, b) * t (其中t为任意整数)
	​	x, y 就是 ax + by = c 的所有整数解.
	
* #### 用扩展欧几里德算法求解模线性方程的方法：

	    同余方程 ax ≡ b (mod n) 对于未知数 x 有解, 当且仅当 gcd(a, n) | b 即 b mod gcd(a, n) = 0 . 且方程有解时, 方程有 gcd(a, n) 个解.
        
	    求解方程 ax ≡ b (mod n) 相当于求解方程 
	    	ax + ny = b, (x, y为整数)
        
	    设 d = gcd(a, n), 假如整数 x 和 y, 满足 d = ax + ny (用扩展欧几里德得出). 如果 d | b, 则方程 
	    	a * x0 + n * y0 = d, 
	    方程两边乘以 b / d, (因为 d|b, 所以能够整除), 得到 
	    	a * x0 * b / d + n * y0 * b / d = b.
	    所以 x = x0 * b / d, y = y0 * b / d 为 ax + ny = b 的一个解, 所以 x = x0 * b / d 为 ax = b (mod n) 的解.
        
	    ax ≡ b (mod n) 的一个解为 
	    	x0 = x * (b / d) mod n, 
	    且方程的 d 个解分别为 
	    	xi = (x0 + i * (n / d )) mod n {i= 0... d-1}.
        
	    设 ans = x * (b / d), s = n / d;
	    方程 ax ≡ b (mod n) 的最小整数解为: (ans % s + s) % s;
	
* #### 用欧几里德算法求模的逆元(见模版)


## 图论:
### 差分约束:
	①：对于差分不等式，a - b <= c , 建一条 b 到 a 的权值为 c 的边, 求的是最短路, 得到的是最大值 
	②：对于不等式 a - b >= c , 建一条 b 到 a 的权值为 c 的边, 求的是最长路, 得到的是最小值 
	③：存在负环的话是无解 
	④：求不出最短路（dist[ ]没有得到更新）的话是任意解 

### 有向图 A点恰好走k步(允许重复经过边)到达B点的方案数
	给定一个有向图, 问从A点恰好走k步(允许重复经过边)到达B点的方案数mod p的值
	把给定的图转为邻接矩阵, 即 A(i,j) = 1 当且仅当存在一条边 i->j.
	令 C = A * A, 那么 C(i,j) = ΣA(i,k) * A(k,j), 实际上就等于从点i到点j恰好经过2条边的路径数(枚举k为中转点).
	类似地, C * A(这里的C已经是A * A)的第i行第j列就表示从i到j经过3条边的路径数
	同理, 如果要求经过k步的路径数, 我们只需要二分求出 A^k 即可.

## 数据结构
### 后缀数组(代码见kuangbin模版)

```
概念：
（1）后缀数组（SA）是 “ 排第几的是谁？ ”, 名次数组（RANK）是 “ 你排第几？ ” 在求出名次数组后，可以仅用 O(1) 的时间比较任意两个后缀的大小。
（2）height 数组：定义 height[i] = suffix(SA[i-1]) 和 suffix(SA[i]) 的最长公共前缀，也就是排名相邻的两个后缀的最长公共前缀的长度 。
（3）h[i] = height[rank[i]]，也就是suffix(i)和排序后在它前一名的后缀的最长公共前缀的长度。
（4）函数 lcp(u,v) = max{ i | u = v }，也就是从头开始顺次比较u和v的对应字符，对应字符持续相等的最大位置，称为这两个字符串u,v的最长公共前缀的长度。
（5）LCP(i,j)：对正整数i,j 定义LCP(i,j) = lcp(Suffix(SA[i]),Suffix(SA[j])，其中i,j 均为1至n的整数。LCP(i,j)也就是后缀数组中第i个和第j个后缀的最长公共前缀的长度。

性质：
（1）LCP(i,j) = min{ height[k] | i+1≤k≤j }，也就是说，计算LCP(i,j)等同于询问一维数组height[] 中下标在i+1 到j 范围内的所有元素的最小值。
（2）对于i>1 且Rank[i]>1，一定有 h[i]≥h[i-1]-1。（这条性质要好好理解！）

```

## 字符串
### KMP
	（1）当_next[j]+1 != _next[j+1] 即不符合递推规律时，这时候就是当前子串最长的公共前后缀了，前缀个数就是字符串的长度
	（2）循环节 len - next[len]


## 一些结论
### 划分:
直线划分平面: $n*(n+1)/2+1$ 

折线划分平面: $2n^2-n+1$ 

封闭曲线划分平面: $n^2-n+2$ 

平面划分空间: $(n^3+5n)/6+1$ 

## 计算几何
向量积(叉积): $\vec a * \vec b = |\vec a||\vec b|sin\theta$  模(长度): $|\vec a*\vec b|$ 可以解释为以a和b为邻边的平行四边形的面积, 三角形面积则除2


叉积求多边形面积公式: $$S=[(\sum_{i=1}^{n-1}\begin{vmatrix}Xi&Yi\\Xi+1&Yi+1\end{vmatrix})+\begin{vmatrix}Xn&Yn\\X1&Y1\end{vmatrix}]/2​$$

[叉积求多边形面积]: https://www.cnblogs.com/xiexinxinlove/p/3708147.html

叉积求三角形面积: 

​	顶点A$(X1,Y1)$  B$(X2,Y2)$  C$(X3,Y3)$  $\overrightarrow{AB}=(X2-X1,Y2-Y1)$ $\overrightarrow{AC}=(X3-X1,Y3-Y1)$ 

​	面积$S=(\overrightarrow{AB}*\overrightarrow{AC})/2=[(X2-X1)*(Y3-Y1)-(X3-X1)*(Y2-Y1)]/2$ 

质心: $X=(\sum_{i=1}^nXi)/n$   $Y=(\sum_{i=1}^nYi)/n$ 

凸包:

![](/Users/zdz/Downloads/Code/Template/Graham-Scan.png)

[凸包(Graham扫描法)]: https://blog.csdn.net/u012328159/article/details/50808360
[最远点对(旋转卡壳法)]: https://blog.csdn.net/u012328159/article/details/50809014

平面最近点对: 见kuangbin模版

