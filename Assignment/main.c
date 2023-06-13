/* 16진수를 2진수로 출력하는 프로그램 */

#include<stdio.h> 

void print(int num, int bit) {
    for (int i = bit - 1; i >= 0; --i) {
        printf("%d", (num >> i) & 1);
    }
}

int main(void) {
    int x;
    scanf("%x", &x);
    
    int sub1 = (x >> 12) & ((1 << 4) - 1);
    int sub2 = (x >> 9) & ((1 << 3) - 1);
    int sub3 = x & ((1 << 9) - 1);

    print(sub1, 4);
    printf(" : ");
    print(sub2, 3);
    printf(" : ");
    print(sub3, 9);
    printf("\n");
    
    return 0;
}
