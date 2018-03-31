//
//  1003MaxSum.c
//  ACM
//
//  Created by 郑东哲 on 15/11/13.
//  Copyright © 2015年 郑东哲. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    int count = 0;
    scanf("%d",&count);
    for (int i = 1; i <= count; i ++) {
        int arrsize = 0;
        scanf("%d",&arrsize);
        int * arr = (int *)malloc(sizeof(int) * arrsize);
        for (int j = 0; j < arrsize; j ++) {
            scanf("%d",arr + j);
        }
        
        int sum = *arr,between = 0,temp = 0,start = 1,end = 1;
        for (int j = 0; j < arrsize; j ++) {
            if (temp < 0) {
                temp = *(arr + j);
                between = 0;
            } else {
                temp += *(arr + j);
            }
            
            if (temp > sum) {
                sum = temp;
                end = j + 1;
                start = end - between;
            }
            
            between ++;
        }
        
        if (i == count) {
            printf("Case %d:\n",i);
            printf("%d %d %d\n",sum,start,end);
        } else {
            printf("Case %d:\n",i);
            printf("%d %d %d\n\n",sum,start,end);
        }
        
        free(arr);
    }
     
    return 0;
}