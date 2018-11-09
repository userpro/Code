const int maxn=110;
int N,M;
double a[maxn][maxn],ans[maxn];

inline int sgn(double x) { return (x>eps)-(x<-eps); }

int gauss() {
    int equ,var; // equ个方程 var个变量
    equ=N*M, var=N*M;
    
    bool free_x[maxn];
    int i,j,k;  
    int max_r; // 当前这列绝对值最大的行.  
    int col; // 当前处理的列.  
    double temp;  
    // 转换为阶梯阵.  
    col=0; // 当前处理的列.  
    memset(free_x,true,sizeof(free_x));  
    for(k=0;k<equ&&col<var;k++,col++) {  
        max_r=k;  
        for(i=k+1;i<equ;i++) //找出当前这列绝对值最大的行
        {  
            if(sgn(fabs(a[i][col])-fabs(a[max_r][col]))>0)  
                max_r=i;  
        }  
        if(max_r!=k) { // 与第k行交换.  
            for(j=k;j<var+1;j++)  
                swap(a[k][j],a[max_r][j]);  
        }  
        if(sgn(a[k][col])==0) { // 说明该col列第k行以下全是0了，则处理当前行的下一列.  
            k--; continue;  
        }  
        for(i=k+1;i<equ;i++)  
        { // 枚举要删去的行，即将第k行以下的第col个变量的系数都变为0  
            if (sgn(a[i][col])!=0) {  
                temp=a[i][col]/a[k][col];  
                for(j=col;j<var+1;j++) {  
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
        for(i=k-1;i>=0;i--) {  
            int free_x_num=0;  //自由变元的个数
            int free_index;  //自由变元的序号  

            for(j=0;j<var;j++) {  
                if (sgn(a[i][j])!=0&&free_x[j])  
                    free_x_num++,free_index=j;  
            }  
            if(free_x_num>1) continue;  //该行中的不确定的变元的个数超过1个,无法求解,它们仍然为不确定的变元  
            //只有一个不确定的变元free_index,可以求解出该变元,且该变元是确定的
            temp=a[i][var];  
            for(j=0;j<var;j++) {
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
        for(j=i+1;j<var;j++) {
            if(sgn(a[i][j])!=0)
                temp-=a[i][j]*ans[j];
        }
        ans[i]=temp/a[i][i];  
    }  
    return 1;  
}