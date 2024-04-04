/*************************************************************************
	> File Name: 02.attribute.c
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Apr 2024 07:50:22 PM CST
 ************************************************************************/

#include<stdio.h>

int num[10];

__attribute__((constructor))void test1() {
    num[0] = 1;
    return ;
} 
__attribute__((constructor))void test2() {
    num[1] = 10086;
    return ;
} 
__attribute__((constructor))void test3() {
    num[2] = 10087;
    return ;
} 

int main() {
    for (int i = 0; i < 10; i++) {
        printf(" %3d", num[i]);
    }
    printf("\n");
    
    return 0;
}
