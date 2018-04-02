// SG计算方法
// 1.可选步数为1~m的连续整数，直接取模即可，SG(x) = x % (m+1);
// 2.可选步数为任意步，SG(x) = x;
// 3.可选步数为一系列不连续的数，用getSG()计算

//f[]需要从小到大排序
//f[N]:可改变当前状态的方式，N为方式的种类，f[N]要在getSG之前先预处理
//SG[]:0~n的SG函数值
//S[]:为x后继状态的集合
int f[N],SG[MAXN],S[MAXN];
void getSG(int n)
{
    memset(SG,0,sizeof(SG));
    //因为SG[0]始终等于0，所以i从1开始
    for(int i = 1; i <= n; i++)
    {
        //每一次都要将上一状态 的 后继集合 重置
        memset(S,0,sizeof(S));
        for(int j = 0; f[j] <= i && j <= N; j++)
            S[SG[i-f[j]]] = 1;  //将后继状态的SG函数值进行标记
        for(int j = 0;; j++) 
            if(!S[j]) //查询当前后继状态SG值中最小的非零值
            {
                SG[i] = j;
                break;
            }
    }
}


// -------
// 注意 S数组要按从小到大排序 SG函数要初始化为-1 对于每个集合只需初始化1遍  
// n是集合s的大小 S[i]是定义的特殊取法规则的数组 
int s[MAXN];
bool vis[MAXN];
void dfsSG(int x)
{
    if (sg[x]!=-1)
        return sg[x];
    memset(vis,0,sizeof(vis));
    for (int i=1;i<=n;i++)
        if (x>=s[i])
        {
            dfsSG(x-s[i]);
            vis[sg[x-s[i]]]=1;
        }

    for (int i=1;;++i)
        if (!vis[i])
        {
            e=i;
            return sg[x]=i;
        }
}