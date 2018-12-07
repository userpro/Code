#include <cstdio>
#include <cstring>
int f[1010],res[1010],sav[1010];

// 乘
/*
    f res数字数组
    f[1]=2;
    res[1]=1;
*/
void cheng() {
    memset(sav,0,sizeof(sav));
    for (int i=1;i<=500;i++)
        for (int j=1;j<=500;j++)
            sav[i+j-1]+=res[i]*f[j];

    for (int i=1;i<=500;i++) {
        sav[i+1]+=sav[i]/10;
        sav[i]%=10;
    }
    memcpy(res,sav,sizeof(res));
}
