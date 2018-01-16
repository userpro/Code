#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;
#define INF 2<<20
typedef struct _POS
{
    int i, j, k, dis, flag;
    char c;
} pos;

const int MAX = 30;
pos map[MAX][MAX][MAX];

void update(pos* p, pos* cur, queue<pos*> &q)
{
    if (p->c != '#' && p->flag == 0)
    {
        if (p->dis > cur->dis+1)
            p->dis = cur->dis + 1;
        p->flag = 1;
        q.push(p);
    }
}


int main() { 
    int count = 0;
    queue<pos*> q;
    pos *tmp, *up, *down, *north, *south, *east, *west;
    int i, j, k, s_i, s_j, s_k, e_i, e_j, e_k;
    int L, R, C;
    while(scanf("%d %d %d", &L, &R, &C) != EOF && L != 0)
    {
        getchar();
        for (i = 0; i < L; i++)
        {
            for (j = 0; j < R; j++)
            {
                for (k = 0; k < C; k++)
                {
                    scanf("%c", &map[i][j][k].c);
                    map[i][j][k].i = i; map[i][j][k].j = j; map[i][j][k].k = k;
                    map[i][j][k].dis = INF;
                    map[i][j][k].flag = 0;
                    if (map[i][j][k].c == 'S')
                    {
                        s_i = i; s_j = j; s_k = k;
                        map[i][j][k].dis = 0;
                    } else if (map[i][j][k].c == 'E')
                    {
                        e_i = i; e_j = j; e_k = k;
                    }
                }
                getchar();
            }
            getchar();
        }

        q.push(&map[s_i][s_j][s_k]);
        while (!q.empty()) 
        {
            tmp = q.front();
            if (tmp->k-1 >= 0) 
            {
                west = &map[tmp->i][tmp->j][tmp->k-1];
                update(west, tmp, q);
            }
            if (tmp->k+1 < C) 
            {
                east = &map[tmp->i][tmp->j][tmp->k+1];
                update(east, tmp, q);
            }
            if (tmp->j-1 >= 0) 
            {
                north = &map[tmp->i][tmp->j-1][tmp->k];
                update(north, tmp, q);
            }
            if (tmp->j+1 < R) 
            {
                south = &map[tmp->i][tmp->j+1][tmp->k];
                update(south, tmp, q);
            }
            if (tmp->i-1 >= 0) 
            {
                down = &map[tmp->i-1][tmp->j][tmp->k];
                update(down, tmp, q);
            }
            if (tmp->i+1 < L) 
            {
                up = &map[tmp->i+1][tmp->j][tmp->k];
                update(up, tmp, q);
            }
            q.pop();
        }

        if (map[e_i][e_j][e_k].dis != INF)
            printf("Escaped in %d minute(s).\n", map[e_i][e_j][e_k].dis);
        else
            printf("Trapped!\n");
    }
    return 0;
}
