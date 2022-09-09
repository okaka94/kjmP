#pragma once
#include "Linked_List.h"
#include "Student.h"
#include <iomanip>

using namespace std;

template <class T>
class Manage_List
{
public:

    Linked_List<T> List;

public:
    void Example(int n);
    void Print_All();
    void Print_Current(Box<T>* node);
    void FreeMem();
    Box<T>* Find(char* name);
    void Delete();
    void Clear();
    void Sort();
    void Save();
    void Load();
    void Add_Student();

};

// =======================================.cpp ===================================


template <class T>
void Manage_List<T>::Example(int n) {

    int i;
    for (i = 0; i < n; i++) {

        List.Insert_back(List.Create_Rand_Node());
    }

    Print_All();

    return;
}

template <class T>
void Manage_List<T>::Print_All() {                                                              // 노드 전체 출력함수
    system("cls");
    std::cout << "\n 이름\t나이\t국어\t영어\t수학\t총점\t 평균\n\n";
    Box<T>* box = List.Begin();
    while (box != NULL) {
        Print_Current(box);

        box = box->p_next;
    }
    std::cout << "\n 전체 학생의 수는 " << List.Get_counter() << "명 입니다.\n";

    return;
}

template <class T>
void Manage_List<T>::Print_Current(Box<T>* box) {

    T* node_data = box->m_data;

    std::cout << " " << node_data->s_name << "\t" << setw(4) << node_data->i_age << "\t" << setw(4) << node_data->i_kor
        << "\t" << setw(4) << node_data->i_eng << "\t" << setw(4) << node_data->i_math << "\t" << setw(4) << node_data->i_total
        << "\t" << setw(4);
    cout << fixed;
    cout.precision(2);
    cout << node_data->i_avg << "\n";

    return;
}


template <class T>
void Manage_List<T>::FreeMem() {
    Box<T>* node = List.Begin();
    while (node != NULL) {

        delete node->m_data;
        List.Set_next(node->p_next);
        delete node;
        node = List.Get_next();
    }




    return;
}

template <class T>
void Manage_List<T>::Delete() {                                                             // 검색 후 해당 노드 삭제 (앞 뒤 재연결 해주기)
    char name[4] = { 0, };
    printf("\n 삭제를 원하는 학생의 이름을 입력해주세요 : ");
    scanf("%s", name);

    Box<T>* node = Find(name);
    assert(node);                                                           // assert 한번 써보려고  넣음 ( 일치하는 학생 없으면 다시 검색 or 최초화면으로 분기시키기 )

    node->p_prev->p_next = node->p_next;
    if (node->p_next != nullptr) {
        node->p_next->p_prev = node->p_prev;
        
    }
    else {
        
        List.Set_next(node->p_prev);
    }

    delete node->m_data;
    node->m_data = nullptr;
    delete node;

    List.Lesser_counter();

    printf("삭제 완료!\n");

    return;
}

template <class T>
void Manage_List<T>::Clear() {
    FreeMem();
    
    List.Init();
    

    system("cls");

    return;
}

template <class T>
void Manage_List<T>::Sort() {


    printf(" 기존 자료를 백업합니다\n");
    Save();                             // 현재 정보 백업

    ///////////평균 성적 순 정렬이지만 실수기때문에 내부에서는 총점 순서대로 정렬할 것//////////////////

    Box<T>* scanner = List.Begin();
    int num = List.Get_counter() - 1;

    for (int i = num; i > 0; i--) {
        scanner = List.Begin(); // 스캐너 위치 다시 맨 앞으로
        //while (scanner->p_next != NULL) {
        for(int j=i;j>0;j--){
            if (scanner->m_data->i_total < scanner->p_next->m_data->i_total) {              /// 총점은 student에만 잇음
                // 현재 위치와 다음 위치 스왑하기

                Box<T>* swap = scanner;
                Box<T>* temp = swap->p_next;
                Box<T>* temp_next = temp->p_next;



                if (temp_next == nullptr) {
                    swap->p_prev->p_next = temp;      // 1 -> 2 (scanner) -> 3 -> 4 를
                    temp->p_prev = swap->p_prev;      // 1 -> 3 -> 2 (scanner) -> 4 로 바꾸는 과정
                    temp->p_next = swap;
                    swap->p_prev = temp;
                    swap->p_next = NULL;
                }
                else {
                    swap->p_prev->p_next = temp;      // 1 -> 2 (scanner) -> 3 -> 4 를
                    temp->p_prev = swap->p_prev;      // 1 -> 3 -> 2 (scanner) -> 4 로 바꾸는 과정
                    temp->p_next = swap;
                    swap->p_prev = temp;
                    swap->p_next = temp_next;
                    temp_next->p_prev = swap;
                }



            }
            else
                scanner = scanner->p_next;                      // next 노드로 넘어감
        }
    }

    //////////////////////////////////////////////////////////////// 정렬 후 //////////////////////////////////////////////
    char ans = NULL;
    getchar();
    printf(" 원상태로 되돌리시겠습니까? ... (y/n)\n");

    do {
        scanf("%c", &ans);
        if (ans == 'y') {
            Load();
            printf(" 되돌리기 완료\n");
            puts("\n< 아무키나 누르세요 >\n"), _getch();
            break;
        }
        else if (ans == 'n') {
            printf(" 초기화면으로 돌아갑니다\n");
            puts("\n< 아무키나 누르세요 >\n"), _getch();
            break;
        }
        else
            printf(" 잘못된 입력입니다.\n");
    } while (1);

    return;

}

template <class T>
void Manage_List<T>::Save() {                                                                // txt 파일로 저장
    Box<T>* node = List.Begin();

    T* node_data = node->m_data;

    FILE* fp = fopen("save_file.txt", "w");
    {
        fprintf(fp, "%d\n", List.Get_counter());
        while (node != NULL) {
            node_data = node->m_data;
            fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%d\t%.2f\n", node_data->s_name, node_data->i_age, node_data->i_kor, node_data->i_eng, node_data->i_math, node_data->i_total, node_data->i_avg);
            node = node->p_next;

        }
        fclose(fp);
    }
    printf(" 저장 완료.\n");
}

template <class T>
void Manage_List<T>::Load() {
    char ans = NULL;
    do {
        system("cls");
        printf(" 불러오기시 현재 데이터를 모두 덮어씌웁니다. 계속 하시겠습니까? ... (y/n) ");
        scanf("%c", &ans);
        if (ans == 'n')
            return;
    } while (ans != 'y');


    FreeMem();
    List.Init();
    int i_count;
    FILE* fp = fopen("save_file.txt", "r");
    {
        fscanf(fp, "%d\n", &i_count);
        for (int i = 0; i < i_count; i++) {
            List.Insert_back(List.Load_Node(fp));
        }

        fclose(fp);
    }
    
}

template <class T>
void Manage_List<T>::Add_Student() {
    List.Insert_back(List.Create_Custom_Node());                                       // 커스텀 노드 생성


    return;
}

template <class T>
Box<T>* Manage_List<T>::Find(char* name) {
    system("cls");

    Box<T>* node = List.Begin();

    while (node != NULL) {
        if (strcmp(node->m_data->s_name, name) == 0) {
            printf("=====================검색 성공!!!======================\n");
            printf(" 이름\t나이\t국어\t영어\t수학\t총점\t 평균\n\n");
            Print_Current(node);

            return node;
        }
        node = node->p_next;
    }
    printf("일치하는 학생이 없습니다\n");

    return nullptr;
}