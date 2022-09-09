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
void Manage_List<T>::Print_All() {                                                              // ��� ��ü ����Լ�
    system("cls");
    std::cout << "\n �̸�\t����\t����\t����\t����\t����\t ���\n\n";
    Box<T>* box = List.Begin();
    while (box != NULL) {
        Print_Current(box);

        box = box->p_next;
    }
    std::cout << "\n ��ü �л��� ���� " << List.Get_counter() << "�� �Դϴ�.\n";

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
void Manage_List<T>::Delete() {                                                             // �˻� �� �ش� ��� ���� (�� �� �翬�� ���ֱ�)
    char name[4] = { 0, };
    printf("\n ������ ���ϴ� �л��� �̸��� �Է����ּ��� : ");
    scanf("%s", name);

    Box<T>* node = Find(name);
    assert(node);                                                           // assert �ѹ� �Ẹ����  ���� ( ��ġ�ϴ� �л� ������ �ٽ� �˻� or ����ȭ������ �б��Ű�� )

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

    printf("���� �Ϸ�!\n");

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


    printf(" ���� �ڷḦ ����մϴ�\n");
    Save();                             // ���� ���� ���

    ///////////��� ���� �� ���������� �Ǽ��⶧���� ���ο����� ���� ������� ������ ��//////////////////

    Box<T>* scanner = List.Begin();
    int num = List.Get_counter() - 1;

    for (int i = num; i > 0; i--) {
        scanner = List.Begin(); // ��ĳ�� ��ġ �ٽ� �� ������
        //while (scanner->p_next != NULL) {
        for(int j=i;j>0;j--){
            if (scanner->m_data->i_total < scanner->p_next->m_data->i_total) {              /// ������ student���� ����
                // ���� ��ġ�� ���� ��ġ �����ϱ�

                Box<T>* swap = scanner;
                Box<T>* temp = swap->p_next;
                Box<T>* temp_next = temp->p_next;



                if (temp_next == nullptr) {
                    swap->p_prev->p_next = temp;      // 1 -> 2 (scanner) -> 3 -> 4 ��
                    temp->p_prev = swap->p_prev;      // 1 -> 3 -> 2 (scanner) -> 4 �� �ٲٴ� ����
                    temp->p_next = swap;
                    swap->p_prev = temp;
                    swap->p_next = NULL;
                }
                else {
                    swap->p_prev->p_next = temp;      // 1 -> 2 (scanner) -> 3 -> 4 ��
                    temp->p_prev = swap->p_prev;      // 1 -> 3 -> 2 (scanner) -> 4 �� �ٲٴ� ����
                    temp->p_next = swap;
                    swap->p_prev = temp;
                    swap->p_next = temp_next;
                    temp_next->p_prev = swap;
                }



            }
            else
                scanner = scanner->p_next;                      // next ���� �Ѿ
        }
    }

    //////////////////////////////////////////////////////////////// ���� �� //////////////////////////////////////////////
    char ans = NULL;
    getchar();
    printf(" �����·� �ǵ����ðڽ��ϱ�? ... (y/n)\n");

    do {
        scanf("%c", &ans);
        if (ans == 'y') {
            Load();
            printf(" �ǵ����� �Ϸ�\n");
            puts("\n< �ƹ�Ű�� �������� >\n"), _getch();
            break;
        }
        else if (ans == 'n') {
            printf(" �ʱ�ȭ������ ���ư��ϴ�\n");
            puts("\n< �ƹ�Ű�� �������� >\n"), _getch();
            break;
        }
        else
            printf(" �߸��� �Է��Դϴ�.\n");
    } while (1);

    return;

}

template <class T>
void Manage_List<T>::Save() {                                                                // txt ���Ϸ� ����
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
    printf(" ���� �Ϸ�.\n");
}

template <class T>
void Manage_List<T>::Load() {
    char ans = NULL;
    do {
        system("cls");
        printf(" �ҷ������ ���� �����͸� ��� �����ϴ�. ��� �Ͻðڽ��ϱ�? ... (y/n) ");
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
    List.Insert_back(List.Create_Custom_Node());                                       // Ŀ���� ��� ����


    return;
}

template <class T>
Box<T>* Manage_List<T>::Find(char* name) {
    system("cls");

    Box<T>* node = List.Begin();

    while (node != NULL) {
        if (strcmp(node->m_data->s_name, name) == 0) {
            printf("=====================�˻� ����!!!======================\n");
            printf(" �̸�\t����\t����\t����\t����\t����\t ���\n\n");
            Print_Current(node);

            return node;
        }
        node = node->p_next;
    }
    printf("��ġ�ϴ� �л��� �����ϴ�\n");

    return nullptr;
}