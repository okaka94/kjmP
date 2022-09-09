#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <conio.h>

struct Student {
    char s_name[4];
    int i_age;
    int i_kor;
    int i_eng;
    int i_math;
    int i_total;
    float i_avg;
    Student* p_next;
    Student* p_prev;
};

Student* S_Head ;
Student* S_Next ;

//Student* S_Tail;
int Students_num;

void Init();
Student* Create_Rand_Node();
void Insert_back(Student* new_node);
void Insert_front(Student* new_node);                                                       // 전위 연결 (사용은 안하고 구현만 해둠)
void Print_All();
void Example(int n);
void FreeMem();
Student* Find(char*);
void Print_Current(Student*);
void Add_Student();
Student* Create_Custom_Node();
void Save();
void Load();
Student* Load_Node(FILE*);
void Delete();
void Clear();
void Sort();

enum STATE {SAMPLE, PRINT_ALL, ADD, FIND, SAVE, LOAD, DELETE, CLEAR, SORT, EXIT = 99};


void Init() {                                                                   // 머리,꼬리,중간 초기화
    S_Head = (Student*)calloc(1, sizeof(Student));                               // 이때 struct* Head = ()malloc() 이런식으로 선언하면 지역변수로 다시 선언하는거라 ----
    //S_Tail = (Student*)calloc(1, sizeof(Student));                               //   ------>  전역변수는 여전히 null값이 되어 nullptr 오류 발생함
    //S_Head->p_next = S_Tail;     
    //S_Tail->p_prev = S_Head;

    S_Next = S_Head;
    Students_num = 0;
    return;
}

 Student* Create_Rand_Node(){                                                    // 랜덤 노드 생성
   
   Student* new_node = (Student*)malloc(sizeof(Student));
   new_node->s_name[0] = 65 + rand() % 26;
   new_node->s_name[1] = 65 + rand() % 26;
   new_node->s_name[2] = 65 + rand() % 26;
   new_node->s_name[3] = 0;
   new_node->i_age = 10+ rand() % 10;
   new_node->i_kor = rand() % 101;
   new_node->i_eng = rand() % 101;
   new_node->i_math = rand() % 101;
   new_node->i_total = new_node->i_kor + new_node->i_eng + new_node->i_math;
   new_node->i_avg = new_node->i_total / 3.0;
   new_node->p_next = NULL;
   new_node->p_prev = NULL;

   return new_node;
}

 Student* Create_Custom_Node() {
     Student* new_node = (Student*)malloc(sizeof(Student));
     printf("이름 : ");
     scanf("%s", new_node->s_name);
     printf("나이 : ");
     scanf("%d",&new_node->i_age);
     printf("국어 점수 : ");
     scanf("%d",&new_node->i_kor);
     printf("영어 점수 : ");
     scanf("%d", &new_node->i_eng);
     printf("수학 점수 : ");
     scanf("%d", &new_node->i_math);
     new_node->i_total = new_node->i_kor + new_node->i_eng + new_node->i_math;
     new_node->i_avg = new_node->i_total / 3.0;
     new_node->p_next = NULL;
     new_node->p_prev = NULL;

     return new_node;
 }  
 
 Student* Load_Node(FILE* fp) {
     char buffer[256] = { 0, };
     Student* new_node = (Student*)malloc(sizeof(Student));
     fgets(buffer, 256, fp);
     sscanf(buffer, "%s\t%d\t%d\t%d\t%d", new_node->s_name,&new_node->i_age, &new_node->i_kor , &new_node->i_eng , &new_node->i_math);
     new_node->i_total = new_node->i_kor + new_node->i_eng + new_node->i_math;
     new_node->i_avg = new_node->i_total / 3.0;
     new_node->p_next = NULL;
     new_node->p_prev = NULL;

     return new_node;

 }

 void Insert_back(Student* new_node) {                                            // 맨 뒤에 추가하기
     S_Next->p_next = new_node;
     //new_node->p_next = S_Tail;                                                 // Tail이 지금 꼭 필요?
     new_node->p_prev = S_Next;
     //S_Tail->p_prev = new_node;


     S_Next = new_node;




     Students_num++;

     return;
 }

 void Insert_front(Student* new_node) {                                            // 맨 앞에 추가하기

     if (S_Head->p_next == nullptr) {                                               // 연결된 노드가 없는 상태라면 뒤에 추가하는 것과 같다
         Insert_back(new_node);
     }
     else {
         Student* old_node = S_Head->p_next;                                        // 기존의 최전방 노드
         S_Head->p_next = new_node;                                                 // 새로운 최전방 노드
         old_node->p_prev = new_node;                                               // 새로운 노드의 양방향 연결
         new_node->p_prev = S_Head;
         new_node->p_next = old_node;
         


         Students_num++;
     }
     




     

     return;
 }


void Example(int n) {
    
    int i;
    for (i = 0; i < n; i++) {                                                   // n개 만들기
        Insert_back(Create_Rand_Node());
    }

    Print_All();                                                                

    return;
}

void Print_All() {                                                              // 노드 전체 출력함수
    
    Student *node = S_Head->p_next;                                                     
    while (node != NULL) {
        Print_Current(node);
        //printf("%s\t%d\t%d\t%d\t%d\t%d\t%.2f\n", node->s_name, node->i_age, node->i_kor, node->i_eng, node->i_math, node->i_total, node->i_avg);
        node = node->p_next;
    }
    printf("\n전체 학생의 수는 %d 명 입니다.\n", Students_num);
    return;
}

void FreeMem() {
    Student* node = S_Head->p_next;
    while (node != NULL) {
        S_Next = node->p_next;
        free(node);
        node = S_Next;
    }                                                                           // 각 메모리 해제 후에는 Head도 해제

    free(S_Head);
    //free(S_Tail);
    

    return;
}

Student* Find (char* name) {
    system("cls");
    
    Student* node = S_Head->p_next;
    while (node != NULL) {
        if (strcmp(node->s_name, name) == 0) {
            printf("====================검색 성공!!!=====================\n");
            printf("이름\t나이\t국어\t영어\t수학\t총점\t평균\n\n");
            Print_Current(node);
            
            return node;
        }
        node = node->p_next;
    }
    printf("일치하는 학생이 없습니다\n");

    return nullptr;
}

void Print_Current(Student* node) {
    printf("%s\t%d\t%d\t%d\t%d\t%d\t%.2f\n", node->s_name, node->i_age, node->i_kor, node->i_eng, node->i_math, node->i_total, node->i_avg);
}

void Add_Student() {                                            
    Insert_back(Create_Custom_Node());                                       // 커스텀 노드 생성

    
    return;
}

void Save() {                                                                // txt 파일로 저장
    Student* node = S_Head->p_next;

    FILE* fp = fopen("students.txt", "w");
    {
        fprintf(fp,"%d\n", Students_num);
        while (node != NULL) {
            fprintf(fp, "%s\t%d\t%d\t%d\t%d\t%d\t%.2f\n", node->s_name, node->i_age, node->i_kor, node->i_eng, node->i_math, node->i_total, node->i_avg);
            node = node->p_next;
        }
        fclose(fp);
    }
    printf("저장 완료.\n");
}

void Load() {
    char ans = NULL;
    do {
        system("cls");
        printf("불러오기시 현재 데이터를 모두 덮어씌웁니다. 계속 하시겠습니까? ... (y/n) ");
        scanf("%c", &ans);
        if (ans == 'n')
            return;
    } while (ans != 'y');
    
    
    FreeMem();           
    Init();
    int i_count;
    FILE* fp = fopen("students.txt", "r");
    {
        fscanf(fp, "%d\n", &i_count);
        for (int i = 0; i < i_count; i++) {
            Insert_back(Load_Node(fp));
        }
        
        fclose(fp);
    }

}

void Delete() {                                                             // 검색 후 해당 노드 삭제 (앞 뒤 재연결 해주기)
    char name[4] = { 0, };
    printf("\n삭제를 원하는 학생의 이름을 입력해주세요 : ");
    scanf("%s", name);

    Student* node = Find(name);
    assert(node);                                                           // assert 한번 써보려고  넣음 ( 일치하는 학생 없으면 다시 검색 or 최초화면으로 분기시키기 )
    
    node->p_prev->p_next = node->p_next;                                            
    node->p_next->p_prev = node->p_prev;

    free(node);

    Students_num--;
    printf("삭제 완료!\n");

    return;
}

void Clear() {
    FreeMem();
    Init();

    system("cls");

    return;
}

void Sort() {
    printf("기존 자료를 백업합니다\n");
    Save();                             // 현재 정보 백업

    ///////////평균 성적 순 정렬이지만 실수기때문에 내부에서는 총점 순서대로 정렬할 것//////////////////

    Student* scanner = S_Head->p_next;
    int num = Students_num - 1;

    for (int i = num; i > 0; i--) {
        scanner = S_Head->p_next; // 스캐너 위치 다시 맨 앞으로
        while (scanner->p_next != NULL ) {
            
            if (scanner->i_total < scanner->p_next->i_total) {
                // 현재 위치와 다음 위치 스왑하기

                Student* swap = scanner;
                Student* temp = swap->p_next;
                Student* temp_next = temp->p_next;


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
    printf("원상태로 되돌리시겠습니까? ... (y/n)\n");

    do {
        scanf("%c", &ans);
        if (ans == 'y') {
            Load();
            printf("되돌리기 완료\n");
            puts("\n< 아무키나 누르세요 >\n"), _getch();
            break;
        }
        else if (ans == 'n') {
            printf("초기화면으로 돌아갑니다\n");
            puts("\n< 아무키나 누르세요 >\n"), _getch();
            break;
        }
        else
            printf("잘못된 입력입니다.\n");
    } while (1);

    return;
}

int main()
{
    srand(time(NULL));
    Init();
    char name[4] = { 0, };
    int select;
    
                                                    
    do {
        //printf("이름\t나이\t국어\t영어\t수학\t총점\t평균\n\n");
        printf("원하는 동작을 입력해주세요 : < 0 : 랜덤 샘플> < 1 : 전체 출력> < 2 :학생 추가> < 3 :이름으로 검색> < 4 :저장> < 5 :불러오기> < 6 : 개별 삭제> < 7 : 초기화> < 8 : 평균 성적 순 정렬> < 99 :종료>\n");
        scanf("%d", &select);
        switch (select) {
            case SAMPLE: {
                int n;
                printf("샘플을 만들 학생 수를 입력해주세요 : ");
                scanf("%d", &n);
                Example(n);                                                  // 초기 예시 n개 보여주기  ----  n개 노드 생성 + 출력
                break;
            }
            case PRINT_ALL: {
                Print_All();
                break;
            }
            case ADD: {
                Add_Student();                                               // 학생 추가하기   --- 정보 입력받아 새 노드 생성 + next노드에 연결
                break;
            }
            case FIND: {
                printf("검색할 학생의 이름을 입력해주세요 : ");
                scanf("%s", name);
                Find(name);                                                  // 이름으로 검색하기 --- 검색 후 출력
                break;
            }
            case SAVE: {
                Save();
                break;
            }
            case LOAD: {
                Load();
                break;
            }
            case DELETE: {
                Delete();
                break;
            }
            case CLEAR: {
                Clear();
                break;
            }
            case SORT: {
                Sort();
                break;
            }
            case EXIT: {
                FreeMem();                                                   // 메모리 할당 해제
                break;
            }
        }
        
        
        //system("cls");
        
        
        


    } while (select != 99);

    
    return 0;
}




// 구현할 내용 : 
//        함수 : 초기값 설정 , 전체 명단 출력, 검색, 개인 출력 , 삽입(후위) , 전체 학생 수 출력, 할당 된 메모리 해제
/* 
    전개 방식  
        구조체 디자인 - 랜덤 데이터 할당(초기값 설정) - 전체 명단 출력 - 검색 - 검색 후 개인 출력 - 삽입(전위) - 삽입(후위) - 전체 학생 수 출력(노드 생성시 카운터) - 메모리 해제(연결체 순회)
///////////////////////////
    void *_recalloc(
        void *memblock
        size_t num,
        size_t size
    );
            매개 변수
            memblock
            이전에 할당된 메모리 블록에 대한 포인터입니다.

            number
            요소의 수입니다.

            size
            각 요소의 길이입니다(바이트).
*/
