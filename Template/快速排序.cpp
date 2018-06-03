void quickSort(char *arr, int left, int right){
    int i = left, j = right;
    char mid = arr[(i+j)/2];
    while(i <= j)
    {
        while(arr[i] < mid) i++;
        while(arr[j] > mid) j--;
        if(i <= j)
        {
            int tmp;
            tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            i ++; j --;
        }
    }
    if(i < right) quickSort(arr,i, right);
    if(left < j) quickSort(arr,left, j);
}