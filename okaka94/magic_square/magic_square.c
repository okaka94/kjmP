#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int magic_square[20][20]; // 20 x 20 사이즈의 배열
int size;

void fill_square(int num, int row, int col) {      // 마방진 채우기 :: 넣을 숫자 : num , 행 : row , 열 : col
    int temp_row, temp_col;                        // 임시 행,열

    if (num > size*size) {
        return;
    }
    else {
        temp_row = row - 1;
        temp_col = col + 1;
        if (temp_row < 0) temp_row = size - 1;                                     
        if (temp_col > size-1) temp_col = 0;        // 범위 벗어나면 루프

        if (magic_square[temp_row][temp_col] == 0) {  // 빈칸이면 채우기
            magic_square[temp_row][temp_col] = num;

            fill_square(num + 1, temp_row, temp_col);
        }
        else {                // 빈칸이 아니면 기준점에서 아래로 한칸 내려가서 채우기
            if (row + 1 >= size) {
                magic_square[0][col] = num;
                fill_square(num + 1, 0, col);
            }
                
            else {
                magic_square[row + 1][col] = num;
                fill_square(num + 1, row+1, col);
            }
                
        }

        

        

    }

    return;
}


int main()
{
    
    printf("마방진의 크기 입력 ( 3 ~ 19 사이의 홀수 ) : ");
    scanf("%d", &size);  // 크기 입력

    
    magic_square[0][size / 2] = 1;     // 1의 자리는 맨 윗열 가운데로 고정
    fill_square(2, 0, size / 2);

   


    int i, j;
    for (i = 0; i < size; i++) {                            // 마방진 출력
        printf("\n\t");
            for (j = 0; j < size; j++) {
                printf("%d\t", magic_square[i][j]);
        }
    }
    printf("\n");

    return 0;
}

// 마방진 크기 (3~19사이의 홀수) 입력 받음
// 법칙에 따라 마방진 출력 N x N 배열