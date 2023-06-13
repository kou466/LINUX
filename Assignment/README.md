# 과제

---

## 16진수를 2진수로 출력하는 프로그램

입력형식
16진수로 입력

출력형식
4비트 : 3비트 : 9비트
1010 : 011 : 110100100

---

### 코드 설명 및 결과

```c
#include<stdio.h> 

// print 함수를 정의함. 이 함수는 'num'과 'bit' 두 개의 인수를 받아서, 주어진 수 'num'의 이진수 표현을 'bit' 길이만큼 출력함.
void print(int num, int bit) {
    for (int i = bit - 1; i >= 0; --i) {
        printf("%d", (num >> i) & 1);
    }
}

int main(void) {
    int x; 
    scanf("%x", &x);
    // 변수를 선언하여 사용자로부터 16진수 정수를 입력받음.
	
    int sub1 = (x >> 12) & ((1 << 4) - 1);
    int sub2 = (x >> 9) & ((1 << 3) - 1);
    int sub3 = x & ((1 << 9) - 1);
	
    print(sub1, 4);
    printf(" : ");
    print(sub2, 3);
    printf(" : ");
    print(sub3, 9);
    printf("\n");
    // 'sub1', 'sub2', 'sub3'를 print 함수를 사용하여 2진수로 변환하고 출력함.
    
    return 0;
}
```

![image](https://github.com/kou466/LINUX/assets/32214586/3c0dee1c-2dbb-44a0-b886-0888079f294b)
