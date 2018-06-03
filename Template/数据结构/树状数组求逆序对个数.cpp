
#include <iostream>  
#include <string>  
using namespace std;  
const int N=1010;  
int bit[N];  
int n;  
int lowbit(int i)  
{  
    return i&(-i);  
}  
int insert(int i,int x)  
{  
    while(i<=n)  
    {  
        bit[i]+=x;  
        i+=lowbit(i);  
    }  
    return 0;  
}  
int query(int i)  
{  
    int sum=0;  
    while(i)  
    {  
        sum+=bit[i];  
        i-=lowbit(i);  
    }  
    return sum;  
}  
int main()  
{  
    while(cin>>n)  
    {  
        int ans=0;  
        memset(bit,0,sizeof(bit));  
        for(int i=1;i<=n;i++)  
        {  
            int a;  
            cin>>a;  
            insert(a,1);  
            ans+=i-query(a);  
        }  
        cout<<ans<<endl;  
    }  
    return 0;  
}  