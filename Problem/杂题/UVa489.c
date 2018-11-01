#include <stdio.h>
#include <string.h>
#define MAXN 100

int main(int argc, char const *argv[])
{
    int rnd;
    int left, chance, find;
    int i, j;
    char Q[MAXN],A[MAXN];
    while ( scanf("%d%s%s", &rnd, Q, A) == 3 && rnd != -1)
    {
        chance = 6;
        left = strlen(Q);
        for (i = 0; i < strlen(A); ++i)
        {
            find = 0;
            for (j = 0; j < strlen(Q); ++j)
            {
                if (A[i] == Q[j])
                {
                    Q[j] = ' ';
                    find = 1;
                    left--;
                }
            }
            if (!left) break;
            if (!find) chance--;
        }

        printf("Round %d\n", rnd);
        if (left <= 0 && chance >= 0) printf("You win.\n");
        else if (chance >= 0 && left >= 0) printf("You chickened out.\n");
        else printf("You lose.\n");
    }
    return 0;
}