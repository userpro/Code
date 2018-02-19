// 子集生成 生成[0, n)的所有子集.
// 用法：
// dfs(n,0);
void dfs(int n,int cur) {
    for(int i=0;i<cur;++i)
        printf("%d ",a[i]);
    printf("\n");
    int MIN=(cur?a[cur-1]+1:0);
    for (int i=MIN; i<n; i++) {
        a[cur]=i;
        dfs(n,cur+1);
    }
}