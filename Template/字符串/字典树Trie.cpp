const int maxn=400010;
char buf[maxn];
int sum[maxn];
int tree[maxn][26];
int tot;

void insert(int n) {
    int root=0;
    for (int i=0;i<n;i++) {
        int id=buf[i]-'a';
        if (!tree[root][id])
            tree[root][id]=++tot;
        sum[tree[root][id]]++;
        root=tree[root][id];
    }
}

int find(int n) {
    int root=0;
    for (int i=0;i<n;i++) {
        int id=buf[i]-'a';
        if (!tree[root][id])
            return 0;
        root=tree[root][id];
    }
    return sum[root];
}