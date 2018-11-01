#include <stdio.h>
#include <string.h>

#define INF 1<<20
#define MAX 20
int filp[MAX][MAX], tmp_f[MAX][MAX];
unsigned int op1[MAX], op2[MAX];


int M, N;
void update(int m[MAX][MAX], int r, int c)
{
    m[r][c] = !m[r][c];
    if (c-1 >= 0) m[r][c-1] = !m[r][c-1];
    if (c+1 < N) m[r][c+1] = !m[r][c+1];
    if (r-1 >= 0) m[r-1][c] = !m[r-1][c];
    if (r+1 < M) m[r+1][c] = !m[r+1][c];
}

int main()
{
    int i, j, k, c1 = INF, c2, a; 
    while (scanf("%d %d", &M, &N) != EOF && M != 0)
    {
        getchar();
        memset(filp, 0, sizeof(filp));
        for (i = 0; i < M; i++)
        {
            for (j = 0; j < N; j++)
                scanf("%d", &filp[i][j]);
            getchar();
        }

        for (i = 0; i < (1 << N); ++i)
        {
            c2 = 0;
            memcpy(tmp_f, filp, sizeof(filp));
            memset(op2, 0, sizeof(op2));
            op2[0] = i;
            for (k = 0; k < N; ++k)
            {
                if (op2[0] & (1<<k))
                {
                    update(tmp_f, 0, k);
                    c2++;
                }
            }
            for (j = 1; j < M; ++j)
            {
                for (k = 0; k < N; ++k)
                {
                    if (tmp_f[j-1][k] == 1)
                    {
                        update(tmp_f, j, k);
                        op2[j] = op2[j] | (1<<k);
                        c2++;
                    }
                }
            }

            for (k = 0, a = 0; k < N; ++k)
                a += tmp_f[M-1][k];

            if (a == 0 && c2 < c1)
            {
                c1 = c2;
                memcpy(op1, op2, sizeof(op2));
            }
        }

        if (c1 > 0 && c1 != INF)
        {
            for (i = 0; i < M; ++i)
            {
                for (j = 0; j < N; ++j)
                {
                    if (op1[i] & (1<<j))
                        printf("1 ");
                    else
                        printf("0 ");
                }
                printf("\n");
            }
        } else {
            printf("IMPOSSIBLE\n");
        }
    }
    return 0;
}