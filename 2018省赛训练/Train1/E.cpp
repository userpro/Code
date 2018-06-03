// CodeChef-CHEFMATH
// DFS
#include <iostream>
using namespace std;
typedef long long LL;
LL Q,X,K,ans,f[100];

void dfs(int n,LL sum,int i)
{
    if (n==K)
    {
        if (sum==X)
            ans++;
    }
    else 
    {
        for (int j=i;j<39 && f[j]<=X;j++)
        {
            if (sum+f[j]<=X)
                dfs(n+1,sum+f[j],j);
            else
                break;
        }        
    }
}

int main()
{
    f[0]=1;
    f[1]=2;
    for (int i=2;i<39;i++) f[i]=f[i-1]+f[i-2];
    cin >> Q;
    while (Q--)
    {
        cin >> X >> K;
        ans=0;
        dfs(0,0,0);
        cout << ans << endl;
    }
    return 0; 
}