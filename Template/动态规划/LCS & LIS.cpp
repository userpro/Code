// 最长公共子序列
const int maxn = 10000;
int dp[maxn];
int a[maxn],b[maxn];
int LCS(int n, int m) {
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; i++) {
        int tmp = 0; // 存 i 确定, 且 a[i] > b[j] 时最大的 dp[j]
        for(int j = 1; j <= m; j++) {
            if(a[i] > b[j] && dp[j] > tmp)
                tmp = dp[j];
            else if(a[i] == b[j])
                dp[j] = tmp+1;
        }
    }

    int ans = 0;
    for(int i = 1; i <= m; i++)
        ans = max(ans, dp[i]);
    return ans;
}

// 最长上升子序列
const int maxn = 10000;
int dp[maxn];
int a[maxn];
int LIS(int sign) {
    fill(dp,dp+maxn,inf);
    int ans = 0;
    for(int i=0;i<n;i++){
        int index = upper_bound(dp,dp+ans,a[i]*sign) - dp;//这个是求不严格的序列，如果要求严格的就用lower_bound
        dp[index] = a[i]*sign;
        ans = max(ans,index+1);
    }
    return ans;
}
int lins() { return LIS(1); } // 求上升的
int lnds() { return LIS(-1); } //求下降的