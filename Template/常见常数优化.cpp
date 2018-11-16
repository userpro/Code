#pragma GCC optimize(2)

inline int read() {
    int ret=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
        ret=(ret<<1)+(ret<<3)+ch-'0',ch=getchar();
    return ret;
}