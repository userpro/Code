#include <iostream>  
using namespace std;  
// Author: bjr  
//   
const int max = 1000;   
// sup是保存多项式的数组，sup[n]中的值代表xn的系数
// temp是临时多项式，保存相乘的临时中间情况  
int sup[max], temp[max];   
/*
程序始终只计算两个多项式之间的乘积，多个多项式的情况
先计算前两个的乘积，将结果作为第一个多项式，再与第三个相乘
依次类推，sup始终存放当前运算后的结果然后作为被乘多项式，
*/  
int main()  
{   
    int target;   //  目标重量， 比如上面的例子里就是10，要<max的值
    int i, j, k;  
   
    while(cin >> target)  
    {  
        for(i=0; i<=target; ++i)     
        {  
            sup[i] = 1;   
//初始化第一个多项式，也就是用1g砝码的多项式,
//注意如果题目没给1g的砝码那么就不能++i，而要加上砝码的质量
            temp[i] = 0;  
//将临时区清空，无论第一个多项式质量是几都要全部置零
        }  
        for(i=2; i<=target; ++i)   
// 生成后续的第i个多项式，此题中是2g，i从2开始。
//如果砝码的值不是规律增长，i可能需要取决于输入
        {  
   
            for(j=0; j<=target; ++j)   
// 遍历当前结果多项式的每一项（当前结果的第j项）与第i个多项式相乘，
                for(k=0; k+j<=target; k+=i) 
// 遍历第i个多项式的每一项，此处构造用小砝码组成大砝码的多项式
                {  
                    temp[j+k] += sup[j];  
//幂运算，注意理解
                }  
            for(j=0; j<=target; ++j)    
// 将临时的结果覆盖当前结果，同时把临时结果置零，为下次做准备
            {  
                sup[j] = temp[j];  
                temp[j] = 0;  
            }  
        }  
        cout << sup[target] << endl;  //输出结果
    }  
    return 0;  
}  