const int maxn = 100000;
int num[maxn];
void merge_sort(int l, int r) 
{
    int mid, p, q, i, j, len;

    if(l >= r)    return ;
    mid = (l + r) >> 1;
    len = r - l + 1;

    p = l; q = mid + 1;
    j = l;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    for(i = 0; i < len; ++i) {
        if((q > r) || (num[p] < num[q] && p <= mid)) {
            t[j++] = num[p++];
        } else {
            t[j++] = num[q++];
        }
    }
    for(i = l; i <= r; ++i)
        num[i] = t[i];
}