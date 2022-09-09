#include <stdio.h>
#define SIZE 10


int storage[SIZE];
void Enqueue(int new_num);
void Dequeue();
void Show_first();
void Print_all();
int Head;
int Tail;

int main()
{
	int new_num = 0;										// 숫자 입력받을 변수

	Dequeue();

	for (int i = 1; i < 11; i++) {
		Enqueue(i);
		Print_all();
	}
	
	Show_first();

	for (int i = 1; i < 12; i++) {
		Dequeue();
		Print_all();
	}
	Show_first();

	for (int i = 11; i < 15; i++) {
		Enqueue(i);
		Print_all();
	}

	Show_first();
	
	return 0;
}


void Enqueue(int new_num) {

	if ((Tail+1) %SIZE== Head% SIZE) {
		printf("Not enough Storage! \n");
	}
	else {
		storage[Tail % SIZE] = new_num;
		Tail++;
	}
	
	return;
}

void Dequeue() {

	if (Head == Tail) {
		printf("Nothing to Dequeue! \n");
	}
	else {
		printf("Dequeue : %d \n", storage[Head%SIZE]);
		storage[Head % SIZE] = 0;
		Head++;
	}
	
	return;
}

void Show_first() {

	if (Head == Tail) {
		printf("Nothing to Show! \n");
	}
	else {
		printf("First Num is : %d\n", storage[Head % SIZE]);
	}
	

	return;
}

void Print_all() {										// 순서대로 보이게 수정하기

	for (int i = 0; i < SIZE; i++) {
		printf("%d\t", storage[i]);
	}
	printf("\n");
	return;
}