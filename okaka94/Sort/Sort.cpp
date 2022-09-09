#include <iostream>                
#define SWAP(a,b,temp) (temp)=(a); (a)=(b); (b)=(temp);

void Insert_sort(int* arr, int size, int start = 0, int gap = 1);
void Q_sort(int* arr, int left, int right);

int main() {
    int size = 0;
    int min = 1001;
    int select = 0;
    int temp = 0;

    std::cout << "size : ";                                 
    std::cin >> size;

    int* arr = new int [size];
    int* init = new int[size];

    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    memcpy(init, arr, sizeof(int)*size);                                // backup


       /////////////////////////////////////////////////////////// 선택 정렬///////////////////////////////////////////////////
    std::cout << "=======================" << std::endl;

    for (int i = 0; i < size - 1; i++) {                               
        min = 1001;
        for (int j = i; j < size; j++) {
            if (min > arr[j]) {
                min = arr[j];
                select = j;
            }
            
        }
        temp = arr[i];
        arr[i] = arr[select];
        arr[select] = temp;
    }
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << "\t";

    std::cout << std::endl << "선택 정렬" << std::endl;
    std::cout << "=======================" << std::endl;

    
    /// //////////////////////////////////////////////////////초기화//////////////////////////////////////////////
    
    memcpy(arr, init, sizeof(int) * size);

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << "\t";
    std::cout << std::endl << "초기화 완료" << std::endl;
    std::cout << "=======================" << std::endl;



    ///////////////////////////////////////////////////////////// 삽입 정렬 ///////////////////////////////////////////////////

    Insert_sort(arr, size);

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << "\t";
    std::cout << std::endl << "삽입 정렬" << std::endl;
    std::cout << "=======================" << std::endl;

    /// //////////////////////////////////////////////////////초기화//////////////////////////////////////////////

    memcpy(arr, init, sizeof(int) * size);

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << "\t";
    std::cout << std::endl << "초기화 완료" << std::endl;
    std::cout << "=======================" << std::endl;



    ///////////////////////////////////////////////////////////// 쉘 정렬 ///////////////////////////////////////////////////

    int gap = size/2;
    while (gap != 0) {

        for(int start=0;start<gap;start++){
            Insert_sort(arr, size, start, gap);
        }

        gap /= 2;
    }


    for (int i = 0; i < size; i++)
        std::cout << arr[i] << "\t";

    std::cout << std::endl << "쉘 정렬" << std::endl;
    std::cout << "=======================" << std::endl;

    /// //////////////////////////////////////////////////////초기화//////////////////////////////////////////////

    memcpy(arr, init, sizeof(int) * size);

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << "\t";
    std::cout << std::endl << "초기화 완료" << std::endl;;
    std::cout << "=======================" << std::endl;

    ///////////////////////////////////////////////////////////// 퀵 정렬 ///////////////////////////////////////////////////

    Q_sort(arr, 0, size-1);

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << "\t";    

    std::cout << std::endl << "퀵 정렬" << std::endl;
    std::cout << "=======================" << std::endl;

    /// //////////////////////////////////////////////////////초기화//////////////////////////////////////////////

    memcpy(arr, init, sizeof(int) * size);

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << "\t";
    std::cout << std::endl << "초기화 완료" << std::endl;;
    std::cout << "=======================" << std::endl;

    delete[] arr;
    delete[] init;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Insert_sort(int* arr, int size, int start , int gap ) {
    for (int i = start; i < size - 1; i+=gap) {

        int temp = arr[i + gap];
        for (int j = i; j >= 0; j-=gap) {            //  temp보다 앞에 있는 값([j]) 확인해서 밀어내기
            if (temp < arr[j]&&(i+gap)<=size-1) {
                arr[j + gap] = arr[j];
                arr[j] = temp;
            }

        }

    }
}

void Q_sort(int* arr, int left, int right) {

    int pivot = left;
    int end = right;
    int temp = 0;

    if (left >= right)
        return;

    while (left <= right) {
        while (left<=end && arr[pivot] >= arr[left]) {
            left++;
        }
            
        while (right>=pivot && arr[pivot] <= arr[right]) {
            right--;
        }
            

        if (left <= right) {
            temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
        else {
            temp = arr[pivot];
            arr[pivot] = arr[right];
            arr[right] = temp;
            break;
        }
        
    }

    
    
    
    Q_sort(arr, pivot, right - 1);
    Q_sort(arr, right+1, end);
    

    return;
}