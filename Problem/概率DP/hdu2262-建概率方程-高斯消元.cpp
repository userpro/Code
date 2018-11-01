// 地图n*m看成一个个格子，编号0,1,2,3…n*m-1， 那么坐标i,j的格子编号为 i*m+j 
// EK表示编号为K的格子到一个出口的期望步数 
// 那么EK=0, K这里为出口的编号 
// 我们要求的则是EK, K这里为起点的编号 
// 由一个状态可以走向其他状态，假设当前K可以向三个方向走， 
// 那么 EK= (EK(a) + EK(b) +EK(c)) /3 +1 
// 一般的 EK=(Enext1+Enext2+Enext3+……Ecnt)/ cnt+1 
// 整理得 Enext1+Enext2+Enext3+…Ecnt - EK*cnt= - cnt 
// 对每个EK(K=0,1,2,3…n*m-1)，都建立这样的一个等式，那么可以列出 n*m个方程，然后采用高斯消元，求出E（起点） 
// 其中有 n*m个方程，n*m个变量 
// a[i][j]代表第i个式子（从0开始）,第j个未知数的系数（从0开始）,其中EK为未知数 
// a[0][0] *E0+a[0][1]*E1+………a[0][n*m-1]*E(n*m-1)= a[0][n*m] 
// a[1][0]* E0+a[1][1]*E1+……………………………………… = a[1][n*m] 
// ….. 
// ….. 
// a[n*m-1][0]*E0+a[n*m-1][1]*E1+……………………… =a[n*m-1][n*m] 
// 所以关键要求a[i][j]，如果a数组全部求出来了，然后直接带入高斯消元模板就可以了。 
// 预处理：从每个出口进行bfs，把能到达的位置用flag[i][j]=1标记。 
// 遍历每个格子，对每个格子建立一个方程，求出每个方程每个未知数的系数 
// 用高斯消元求解。 
// 如果起点可以访问到(flag[i][j]==1且高斯消元有解），那么输出唯一解，即E（sx*m+sy）其中，sx,sy为起点的坐标 
// 否则输出-1.
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 
#define ULL unsigned long long 
const int maxn=250;
const double eps=1e-12;  
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
char mp[20][20];
int vis[20][20];
double a[maxn][maxn];//每个方程中的未知数的系数
double ans[maxn];//解集
int n,m;
int sx,sy;
struct node
{
    int x,y;
};
queue<node>que;

void bfs()
{
    while(!que.empty())
    {
        node u=que.front();
        node v;
        que.pop();
        for(int i=0;i<4;i++)
        {
            int x=dx[i]+u.x;
            int y=dy[i]+u.y;
            if(x>=0&&x<n&&y>=0&&y<m&&mp[x][y]!='#'&&!vis[x][y])
            {
                vis[x][y]=1;
                v.x=x;
                v.y=y;
                que.push(v);    
            }
        }
    }
}
int equ,var;//equ个方程,var个变量 
bool free_x[maxn]; 
int sgn(double x)  
{  
    return (x>eps)-(x<-eps);  
}  

int gauss()
{
    equ=n*m,var=n*m;  
    int i,j,k;  
    int max_r; // 当前这列绝对值最大的行.  
    int col; // 当前处理的列.  
    double temp;  
    // 转换为阶梯阵.  
    col=0; // 当前处理的列.  
    memset(free_x,true,sizeof(free_x));  
    for(k=0;k<equ&&col<var;k++,col++)  
    {  
        max_r=k;  
        for(i=k+1;i<equ;i++) //找出当前这列绝对值最大的行
        {  
            if(sgn(fabs(a[i][col])-fabs(a[max_r][col]))>0)  
                max_r=i;  
        }  
        if(max_r!=k)  
        { // 与第k行交换.  
            for(j=k;j<var+1;j++)  
                swap(a[k][j],a[max_r][j]);  
        }  
        if(sgn(a[k][col])==0)  
        { // 说明该col列第k行以下全是0了，则处理当前行的下一列.  
            k--; continue;  
        }  
        for(i=k+1;i<equ;i++)  
        { // 枚举要删去的行，即将第k行以下的第col个变量的系数都变为0  
            if (sgn(a[i][col])!=0)  
            {  
                temp=a[i][col]/a[k][col];  
                for(j=col;j<var+1;j++)  
                {  
                    a[i][j]=a[i][j]-a[k][j]*temp;  
                }  
            }  
        }  
    }  

    for(i=k;i<equ;i++)//此时开始的行的所有变量前面的系数都为0，方程结果应该也为0  
    {   
        if (sgn(a[i][col])!=0)  //如果不为0则说明无解 
            return 0;  
    }  

    if(k<var)//如果存在自由元，自由元个数为var-k   
    {  
        for(i=k-1;i>=0;i--)  
        {  
            int free_x_num=0;  //自由变元的个数
            int free_index;  //自由变元的序号  

            for(j=0;j<var;j++)  
            {  
                if (sgn(a[i][j])!=0&&free_x[j])  
                    free_x_num++,free_index=j;  
            }  
            if(free_x_num>1) continue;  //该行中的不确定的变元的个数超过1个,无法求解,它们仍然为不确定的变元  
            //只有一个不确定的变元free_index,可以求解出该变元,且该变元是确定的
            temp=a[i][var];  
            for(j=0;j<var;j++)  
            {  
                if(sgn(a[i][j])!=0&&j!=free_index)  
                    temp-=a[i][j]*ans[j];  
            }  
            ans[free_index]=temp/a[i][free_index];  
            free_x[free_index]=0;  
        }  
        return var-k;  //返回自由元个数 
    }  

    for (i=var-1;i>=0;i--) //不存在自由元的话 
    {  
        temp=a[i][var];  
        for(j=i+1;j<var;j++)  
        {  
            if(sgn(a[i][j])!=0)  
                temp-=a[i][j]*ans[j];  
        }  
        ans[i]=temp/a[i][i];  
    }  
    return 1;  
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        while(!que.empty())
        {
            que.pop();
        }

        memset(vis,0,sizeof(vis));
        memset(a,0,sizeof(a));
        for(int i=0;i<n;i++)
        {
            scanf("%s",mp[i]);
            for(int j=0;j<m;j++)
            {

                if(mp[i][j]=='@')
                {
                    sx=i;
                    sy=j;
                }
                if(mp[i][j]=='$')
                {
                    node n;
                    n.x=i;
                    n.y=j;
                    que.push(n);
                    vis[i][j]=1;
                }
            }
        }
        bfs();
        for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            int cnt=0;
            if(mp[i][j]=='#') continue;
            if(mp[i][j]=='$')
            {
                a[i*m+j][n*m]=0;
                a[i*m+j][i*m+j]=1;
                continue;
            }
            for(int f=0;f<4;f++)
            {
                int x=i+dx[f];
                int y=j+dy[f];
                if(x>=0&&x<n&&y>=0&&y<m&&mp[x][y]!='#'&&vis[x][y])
                {
                    cnt++;
                    a[i*m+j][x*m+y]=1;
                }
            }
            a[i*m+j][n*m]=-1*cnt;
            a[i*m+j][i*m+j]=-1*cnt;
        }
        if(vis[sx][sy]&&gauss())
        {
            printf("%.6lf\n",ans[sx*m+sy]);
        }
        else 
        printf("-1\n");
    }
    return 0;
}