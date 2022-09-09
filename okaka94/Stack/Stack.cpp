#include <stdio.h>
#define SIZE 10					// 배열의 크기는 10으로 함


int storage[SIZE];
int order;

void Put(int new_num);
void Pop();
void Show_last_num();
void Print_All();


int main() {
	
	int new_num = 0;								// 숫자 입력받을 변수

	Pop();

	for (int i = 1; i < 8; i++) {
		Put(i);
	}

	Print_All();

	Show_last_num();

	Pop();
	Pop();

	Show_last_num();

	Print_All();

	for (int i = 8; i < 15; i++) {
		Put(i);
	}

	Print_All();

	Show_last_num();

	return 0;
}





void Put(int new_num) {
	if (order >= SIZE) {
		printf(" Not enough of Storage! \n");
		return;
	}
	else {
		printf("Put %d\n", new_num);
		storage[order] = new_num;
		order++;
		
	}

	return;

}

void Pop() {
	if (order-1 <= 0) {
		printf(" Nothing to delete!\n ");
		return;
	}
	else {
		printf("Delete %d\n", storage[order-1]);
		storage[order-1] = 0;
		order--;
	}

	return;
}


void Show_last_num() {
	printf("Last number is : %d \n", storage[order-1]);

	return;
}

void Print_All() {
	for (int i = 0; i < SIZE; i++) {
		printf("%d\t", storage[i]);
	}
	printf("\n");
	return;
}