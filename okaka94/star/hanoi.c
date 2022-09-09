#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int move_count; // 이동 횟수 카운트

void hanoi(int n, char start, char temp, char end) {    // 원반의 수 = n , 시작점 = start , 임시 temp,  목표점 end
    if (n == 1) {
        printf("(%d)번원반 (%c) -> (%c) \n", n, start, end);
        move_count++;
        return;
    }
    else {
        hanoi(n - 1, start,end, temp);
        printf("(%d)번원반 (%c) -> (%c) \n", n, start, end);
        move_count++;
        hanoi(n - 1, temp,start, end);
    }
    return;
}

int main()
{
    int n; // 원반의 갯수
    printf("원반의 갯수를 입력해주세요 : ");
    scanf("%d", &n); // 원반의 갯수 입력 받음

    hanoi(n,'A','B','C'); // 이동 경로 출력하는 함수 호출

    printf("원반 (%d) 개의 최소 이동 횟수는 %d번 입니다.\n", n, move_count);

    return 0;
}


// 시작 위치는 A ,목표 위치는 C
// 원반갯수 입력
// "n번원반" "시작 위치 (A,B,C) -> 옮긴 위치" 출력 (각 줄에)
// 원반갯수("""n개""") = 최소 이동 횟수("""n번""")
