#include <stdio.h>
#include <string.h>

#define INF 2<<20
#define MAX 1001
char S1[MAX], S2[MAX], S3[MAX], S12[MAX];

int main()
{
    int N, C, i, j, k, l, m;
    while (scanf("%d", &N) != EOF && N != 0)
    {
        for (i = 0; i < N; ++i)
        {
            memset(S1, 0, sizeof(S1));
            memset(S2, 0, sizeof(S2));
            memset(S3, 0, sizeof(S3));
            memset(S12, 0, sizeof(S12));
            scanf("%d", &C);
            getchar();
            for (j = 0; j < C; ++j)
                scanf("%c", &S1[j]);
            getchar();
            for (j = 0; j < C; ++j)
                scanf("%c", &S2[j]);
            getchar();
            for (j = 0; j < 2*C; ++j)
                scanf("%c", &S12[j]);

            m = 0;
            while (strcmp(S3, S12) != 0 && m < INF)
            {
                for (j = 0, k = 0, l = 0; j < 2*C; j+=2)
                {
                    S3[j] = S2[k++];
                    S3[j+1] = S1[l++];
                }
                for (j = 0; j < C; ++j)
                    S1[j] = S3[j];
                for (j = C; j < 2*C; ++j)
                    S2[j-C] = S3[j];

                m++;
            }
            if (m >= INF) m = -1;
            printf("%d %d\n", i+1, m);
        }
    }
    return 0;
}