typedef struct _pos
{
    int from, to;
    double rate;
}pos;
pos E[MAX_E]; // 边
double D[MAX_N]; // 到每个顶点的值

// // n个顶点 1~n  m条边
bool Bellman_Ford(int start,int n,int m)
{
    memset(D, 0, sizeof(D));
    D[start] = 1;
    for (i = 1; i < n; ++i)
        for (j = 1; j <= m; ++j)
        {
            if (D[E[j].to] < D[E[j].from] * E[j].rate)
                D[E[j].to] = D[E[j].from] * E[j].rate;
            if (D[start] > 1) return true;
        }

    // 判断环 存在返回true
    for (i = 1; i <= m; ++i)
        if (D[E[i].to] < D[E[i].from] * E[i].rate)
            return true;
    return false;
}