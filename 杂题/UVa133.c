#include <stdio.h>
#include <string.h>
#define N 25

int man[N];
int n, k, m; 
int left;

int go(int p, int d, int t)
{
    while (t--)
    {
        do {
            p = (p + d + n - 1) % n + 1; //  -1 +1是为啥 不懂!?
            /*
                +n 保证p为正数
                -1 +1 是因为之前数组存放是从下标1开始的
                因为 (p + d + n - 1) % n >= 0
                所以 (p + d + n - 1) % n + 1 >= 1
            */
            // printf("debug:p %d \n", p);
        } while(man[p] == 0);
        // printf("ok!!!!!!!!\n");
    }
    return p;
}

int main(int argc, char const *argv[])
{
    int i, p1, p2;
    while ( scanf("%d%d%d", &n, &k, &m) == 3 && n )
    {
        memset(man, 0, sizeof(man));
        for (i = 1; i <= n; i++)  man[i] = i;
        p1 = n;
        p2 = 1;
        left = n;
        while (left)
        {
            p1 = go(p1, 1, k);
            p2 = go(p2, -1, m);
            printf("%3d", p1);
            left--;
            if (p2 != p1) 
            {
                printf("%3d", p2);
                left--;
            }
            man[p1] = man[p2] = 0;
            if (left) printf(",");
        }
        printf("\n");
    }
    return 0;
}