#define _CRT_SECURE_NO_WARNINGS
#include "Manage_List.h"-		



enum STATE { SAMPLE, PRINT_ALL, ADD, FIND, SAVE, LOAD, DELETE, CLEAR, SORT, EXIT = 99 };

int main() {
    srand(time(NULL));


    Manage_List<Student> Manage_student;        // student �ڷ��� �Ѱ���


    int select;
    std::cout << "===============================================================================================================\n";
    std::cout << "===============================================Student  Manager================================================\n";
    std::cout << "===============================================================================================================\n";

    do {

        printf("\n���ϴ� ������ �Է����ּ��� : < 0 : ���� ����> < 1 : ��ü ���> < 2 :�л� �߰�> < 3 :�̸����� �˻�> < 4 :����>\n\t\t\t     < 5 :�ҷ�����> < 6 : ���� ����> < 7 : �ʱ�ȭ> < 8 : ��� ������ ����> < 99 :����>\n");
        scanf("%d", &select);
        switch (select) {
        case SAMPLE: {
            int n;
            printf("������ ���� �л� ���� �Է����ּ��� : ");
            scanf("%d", &n);
            Manage_student.Example(n);                                                  // �ʱ� ���� n�� �����ֱ�  ----  n�� ��� ���� + ���
            break;
        }
        case PRINT_ALL: {

            Manage_student.Print_All();
            break;
        }
        case ADD: {
            Manage_student.Add_Student();                                               // �л� �߰��ϱ�   --- ���� �Է¹޾� �� ��� ���� + next��忡 ����
            break;
        }
        case FIND: {
            printf("�˻��� �л��� �̸��� �Է����ּ��� : ");
            char name[4];
            scanf("%s", name);
            Manage_student.Find(name);                                                  // �̸����� �˻��ϱ� --- �˻� �� ���
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
            Manage_student.FreeMem();                                                   // �޸� �Ҵ� ����
            break;
        }
        }




    } while (select != 99);


    return 0;

}

