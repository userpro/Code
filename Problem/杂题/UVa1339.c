#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *s1, const void *s2)
{
    return *(int *)s1 - *(int *)s2;
}

int main()
{
    char a[101], b[101];
    int cnt1[26], cnt2[26];
    int i, len, YN;

    while (scanf("%s%s",a, b) != EOF)
    {
        YN = 1;
        len = strlen(a);
        memset(cnt1, 0, sizeof(cnt1));
        memset(cnt2, 0, sizeof(cnt2));

        for (i = 0; i < len; ++i)
        {
            cnt1[a[i] - 'A']++;
            cnt2[b[i] - 'A']++;
        }

        qsort(cnt1, sizeof(cnt1)/sizeof(int), sizeof(int), cmp);
        qsort(cnt2, sizeof(cnt2)/sizeof(int), sizeof(int), cmp);

        for (i = 0; i < 26; i++)
        {
            if (cnt1[i] != cnt2[i])
            {
                YN = 0;
                break;
            }
        }

        if (YN)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}