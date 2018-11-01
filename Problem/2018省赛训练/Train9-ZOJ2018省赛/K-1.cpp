#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int maxn = 1e5 + 10;
int main()
{
    int t;
    scanf("%d", &t);
    while(t--) {
        int num[maxn];
        char suit[maxn];
        int n, m;
        scanf("%d%d", &n, &m);
        int sign = 0;
        int index = 0;
        for(int i = 1; i <= n; i++) {
            getchar();
            scanf("%c", &suit[i]);
            if(suit[i] != 'W') {
                scanf("%d", &num[i]);
            } else {
                sign = 1;
                index = i;
            }
        }
        int ans = 0;
        if(n == 1 && suit[1] == 'W') {
            printf("%d\n", 3 * m);
            continue;
        }
        if(n == 1) {
            printf("%d\n", 3 * m);
            continue;
        }
        if(sign == 0) {

            if(suit[1] == 'B' && suit[2] == 'C') {
                printf("1\n");
                continue;
            }
            if(suit[1] == 'D' && (suit[2] == 'C' || suit[2] == 'B')) {
                printf("1\n");
                continue;
            }
            if(suit[1] == suit[2]) {
                if(num[1] > num[2]) {
                    printf("1\n");
                    continue;
                }
            }
            ans = 3 * m - n + 1;
            printf("%d\n", ans);
            continue;
        }

        if(index == n) {
            int sumh = 0;
            if(suit[index - 1] == 'C') {
                sumh = num[index - 1];
            }
            if(suit[index - 1] == 'B') {
                sumh = m + num[index - 1];
            }
            if(suit[index - 1] == 'D') {
                sumh = 2 * m + num[index - 1];
            }

            int sum1 = 0;
            int sum2 = 0;
            if(suit[1] == 'C') {
                sum1 = num[1];
            }
            if(suit[1] == 'B') {
                sum1 = m + num[1];
            }
            if(suit[1] == 'D') {
                sum1 = 2 * m + num[1];
            }

            if(suit[2] == 'C') {
                sum2 = num[2];
            }
            if(suit[2] == 'B') {
                sum2 = m + num[2];
            }
            if(suit[2] == 'D') {
                sum2 = 2 * m + num[2];
            }


            if(n == 2) {
                printf("%d\n", 3 * m - sumh + 1);
                continue;
            }
            if(n > 2 && sum1 > sum2) {
                printf("%d\n", 1);
                continue;
            }
            if(n > 2) {
                printf("%d\n", 3 * m - sumh);
                continue;
            }
        }
        if(index == 1) {
            int sumh = 0;
            if(suit[2] == 'C') {
                sumh = num[2];
            }
            if(suit[2] == 'B') {
                sumh = m + num[2];
            }
            if(suit[2] == 'D') {
                sumh = 2 * m + num[2];
            }
            printf("%d\n", sumh - 1);
        }
        if(suit[2] != 'W') {
            if(suit[1] == 'B' && suit[2] == 'C') {
                printf("1\n");
                continue;
            }
            if(suit[1] == 'D' && (suit[2] == 'C' || suit[2] == 'B')) {
                printf("1\n");
                continue;
            }
            if(suit[1] == suit[2]) {
                if(num[1] > num[2]) {
                    printf("1\n");
                    continue;
                }
            }
        }
        if(index == 2) {
            int sum1 = 0;
            int sum2 = 0;
            if(suit[index - 1] == 'C') {
                sum1 = num[index - 1];
            }
            if(suit[index - 1] == 'B') {
                sum1 = m + num[index - 1];
            }
            if(suit[index - 1] == 'D') {
                sum1 = 2 * m + num[index - 1];
            }
            if(suit[index + 1] == 'C') {
                sum2 = num[index + 1];
            }
            if(suit[index + 1] == 'B') {
                sum2 = m + num[index + 1];
            }
            if(suit[index + 1] == 'D') {
                sum2 = 2 * m + num[index + 1];
            }
            printf("%d\n", sum2 - sum1);
            continue;
        }
        if(index > 2) {
            int sum1 = 0;
            int sum2 = 0;
            if(suit[index - 1] == 'C') {
                sum1 = num[index - 1];
            }
            if(suit[index - 1] == 'B') {
                sum1 = m + num[index - 1];
            }
            if(suit[index - 1] == 'D') {
                sum1 = 2 * m + num[index - 1];
            }


            if(suit[index + 1] == 'C') {
                sum2 = num[index + 1];
            }
            if(suit[index + 1] == 'B') {
                sum2 = m + num[index + 1];
            }
            if(suit[index + 1] == 'D') {
                sum2 = 2 * m + num[index + 1];
            }
            printf("%d\n", sum2 - sum1 - 1);
        }
    }
    return 0;
}
