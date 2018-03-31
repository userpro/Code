#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

class ZigZag
{
public:
    int longestZigZag(vector<int> a)
    {
        int dp[100100][2];
        int ans=1;
        memset(dp,0,sizeof(dp));
        for (int i = 0; i < a.size(); ++i)
        {
            dp[i][0]=dp[i][1]=1;
            for (int k = 0; k < 2; ++k)
            {
                for (int j = 0; j < i; ++j)
                {
                    if (a[i]==a[j]) continue;
                    if (k==0)
                    {
                        if (a[i]>a[j])
                            dp[i][k]=max(dp[i][k],dp[j][!k]+1);
                    } else {
                        if (a[i]<a[j])
                            dp[i][k]=max(dp[i][k],dp[j][!k]+1);
                    }
                }
                ans=max(ans,max(dp[i][0],dp[i][1]));
            }
        }
        return ans;
    }
    
};

// int main()
// {
//     ZigZag t;
//     int vv[]={1 };
//     int sz=sizeof(vv)/sizeof(int);
//     vector<int> v(vv,vv+sz);
//     printf("%d\n", t.longestZigZag(v));
//     return 0;
// }

/*
Examples

0)  
        
{ 1, 7, 4, 9, 2, 5 }
Returns: 6
The entire sequence is a zig-zag sequence.
1)  
        
{ 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 }
Returns: 7
There are several subsequences that achieve this length. One is 1,17,10,13,10,16,8.
2)  
        
{ 44 }
Returns: 1
3)  
        
{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }
Returns: 2
4)  
        
{ 70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32 }
Returns: 8
5)  
        
{ 374, 40, 854, 203, 203, 156, 362, 279, 812, 955, 
600, 947, 978, 46, 100, 953, 670, 862, 568, 188, 
67, 669, 810, 704, 52, 861, 49, 640, 370, 908, 
477, 245, 413, 109, 659, 401, 483, 308, 609, 120, 
249, 22, 176, 279, 23, 22, 617, 462, 459, 244 }
Returns: 36
*/