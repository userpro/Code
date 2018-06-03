#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
#include <stack>
using namespace std;
#define INF (1<<29)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

stack< pair<int, int> > stk;
char s[1005];

void quickSort(char *arr, int left, int right){
    int i = left, j = right;
    char mid = arr[(i+j)/2];
    while(i <= j){
        while(arr[i] < mid) i ++;
        while(arr[j] > mid) j --;
        if(i <= j){
            int tmp;
            tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            if (arr[i]!=arr[j]) stk.push(make_pair(j+1, i+1));
            i ++; j --;
        }
    }
    if(i < right) quickSort(arr,i, right);
    if(left < j) quickSort(arr,left, j);
}

int main()
{
    int len;
    while(scanf("%s", s) != EOF)
    {
        while(!stk.empty()) stk.pop();
        len = strlen(s);
        quickSort(s, 0, len-1);
        while(!stk.empty())
        {
            auto t = stk.top();
            stk.pop();
            printf("%d %d\n", t.first, t.second);
        }
    }
    return 0;
}