#define _CRT_SECURE_NO_WARNINGS
#include "Manage_List.h"


enum STATE { SAMPLE, PRINT_ALL, ADD, FIND, SAVE, LOAD, DELETE, CLEAR, SORT, EXIT = 99 };

int main(){
    srand(time(NULL));
    
    
    Manage_List<Student> Manage_student;        // student 자료형 넘겨줌

    
    int select;

    std::cout << "============================================학생 성적 관리 프로그램=============================================";

    do {
        
        printf("\n원하는 동작을 입력해주세요 : < 0 : 랜덤 샘플> < 1 : 전체 출력> < 2 :학생 추가> < 3 :이름으로 검색> < 4 :저장>\n\t\t\t     < 5 :불러오기> < 6 : 개별 삭제> < 7 : 초기화> < 8 : 평균 성적 순 정렬> < 99 :종료>\n");
        scanf("%d", &select);
        switch (select) {
        case SAMPLE: {
            int n;
            printf("샘플을 만들 학생 수를 입력해주세요 : ");
            scanf("%d", &n);
            Manage_student.Example(n);                                                  // 초기 예시 n개 보여주기  ----  n개 노드 생성 + 출력
            break;
        }
        case PRINT_ALL: {
            
            Manage_student.Print_All();
            break;
        }
        case ADD: {
            Manage_student.Add_Student();                                               // 학생 추가하기   --- 정보 입력받아 새 노드 생성 + next노드에 연결
            break;
        }
        case FIND: {
            printf("검색할 학생의 이름을 입력해주세요 : ");
            char name[4];
            scanf("%s", name);
            Manage_student.Find(name);                                                  // 이름으로 검색하기 --- 검색 후 출력
            break;
        }
        case SAVE: {
            
            Manage_student.Save();
            break;
        }
        
        case LOAD: {
            
            Manage_student.Load();
            break;
        }
        case DELETE: {
            
            Manage_student.Delete();
            break;
        }
        case CLEAR: {
            
            Manage_student.Clear();
            break;
        }
        case SORT: {
            
            Manage_student.Sort();
            break;
        }
        case EXIT: {
            Manage_student.FreeMem();                                                   // 메모리 할당 해제
            break;
        }
        }


        

    } while (select != 99);


    return 0;

}

