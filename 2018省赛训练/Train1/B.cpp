#include <stdio.h>  
#include <assert.h>  
#include <string.h>  
  
int main()  
{  
    printf("1\n");fflush(stdout);  
    printf("3 1 2 2\n");fflush(stdout);  
    printf("3 3 4 4\n");fflush(stdout);  
    int ret = 0;scanf("%d",&ret);  
    if(0 == ret) { printf("2\n5\n");fflush(stdout); }  
    else if(1 == ret) { printf("2\n1\n");fflush(stdout); }  
    else if(2 == ret) { printf("2\n2\n");fflush(stdout); }  
    else if(-1 == ret) { printf("2\n3\n");fflush(stdout); }  
    else if(-2 == ret) { printf("2\n4\n");fflush(stdout); }  
    else { assert(0); }  
    return 0;  
}  