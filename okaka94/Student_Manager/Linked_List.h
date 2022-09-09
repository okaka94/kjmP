#pragma once
#include <iostream>


template <class T>							// Box�� ���� next, prev ������ �޾��ֱ�  // Head�� Next�� �ʿ��� ���� �ƴ϶� �ڷ��� �����ϰ� ������ �����ϵ��� �����ϴ� ��
class Box {

public:
	T* m_data;
	Box* p_next;
	Box* p_prev;
	Box() {
		p_next = p_prev = nullptr;
	}
	~Box() {

	}

};


template <class T>										// Box(Ŭ���� ���ø�) ��ü�� ������ �� <> �ȿ� �ڷ��� �־��ִ� �� 
class Linked_List
{
	

private:
	Box<T>* S_Head = NULL;										// ���Ḯ��Ʈ�� �ʿ��� ���
	Box<T>* S_Next = NULL;
	static int counter;

public:
	Linked_List();												// ���Ḯ��Ʈ Ŭ������ ����� ���� ��ɸ� �����ϵ���
	~Linked_List();
	void Init();												

	void Insert_back(T* new_node);
	//void Insert_front(T* new_node);          // ���������� ������ ����
	Box<T>* Get_head();
	Box<T>* Get_next();
	void Set_next(Box<T>* node);
	Box<T>* Begin();
	int Get_counter();
	void Lesser_counter();

	T* Create_Rand_Node();
	T* Create_Custom_Node();
	T* Load_Node(FILE* fp);

};


//============================================================== cpp ����==========================================
template <class T>
int Linked_List<T>::counter = 0;


template <class T>
Linked_List<T>::Linked_List() {
	S_Head = new Box<T>;
	S_Head->p_prev = nullptr;
	S_Head->p_next = nullptr;
	S_Next = S_Head;
}


template <class T>
Linked_List<T>::~Linked_List() {

	delete S_Head;
}


template <class T>
void Linked_List<T>::Init() {        //  �ʱ�ȭ
	
	S_Head->p_prev = nullptr;
	S_Head->p_next = nullptr;
	S_Next = S_Head;
	counter = 0;                        

	return;
}



template <class T>								//  student�� Ưȭ�� ���ø��� (���߿� Ưȭ ���ø����� �����ϱ�)
T* Linked_List<T>::Create_Rand_Node() {

	T* new_data = new T;
	new_data->s_name[0] = 65 + rand() % 26;
	new_data->s_name[1] = 65 + rand() % 26;
	new_data->s_name[2] = 65 + rand() % 26;
	new_data->s_name[3] = 0;
	new_data->i_age = 10 + rand() % 10;
	new_data->i_kor = rand() % 101;
	new_data->i_eng = rand() % 101;
	new_data->i_math = rand() % 101;
	new_data->i_total = new_data->i_kor + new_data->i_eng + new_data->i_math;
	new_data->i_avg = new_data->i_total / 3.0;
	


	return new_data;


}

template <class T>
T* Linked_List<T>::Create_Custom_Node() {
	T* new_node = new T;

	printf("�̸� : ");
	scanf("%s", new_node->s_name);
	printf("���� : ");
	scanf("%d", &new_node->i_age);
	printf("���� ���� : ");
	scanf("%d", &new_node->i_kor);
	printf("���� ���� : ");
	scanf("%d", &new_node->i_eng);
	printf("���� ���� : ");
	scanf("%d", &new_node->i_math);
	new_node->i_total = new_node->i_kor + new_node->i_eng + new_node->i_math;
	new_node->i_avg = new_node->i_total / 3.0;


	return new_node;

}

template <class T>
void Linked_List<T>::Insert_back(T* new_data) {                                            // �� �ڿ� �߰��ϱ�

	Box<T>* new_node = new Box<T>;
	new_node->m_data = new_data;
	S_Next->p_next = new_node;

	new_node->p_prev = S_Next;



	S_Next = new_node;
	counter++;

	return;
}
//template <class T>
//void Linked_List<T>::Insert_front(T* new_node) {                                            // �� �տ� �߰��ϱ�
//
//	if (S_Head->p_next == nullptr) {                                               // ����� ��尡 ���� ���¶�� �ڿ� �߰��ϴ� �Ͱ� ����
//		Insert_back(new_node);
//	}
//	else {
//		Box* old_node = S_Head->p_next;                                        // ������ ������ ���
//		S_Head->p_next = new_node;                                                 // ���ο� ������ ���
//		old_node->p_prev = new_node;                                               // ���ο� ����� ����� ����
//		new_node->p_prev = S_Head;
//		new_node->p_next = old_node;
//
//	}
//	counter++;
//
//	return;
//}

template <class T>
Box<T>* Linked_List<T>::Get_head() {

	return S_Head;
}

template <class T>
Box<T>* Linked_List<T>::Get_next() {

	return S_Next;
}

template <class T>
void Linked_List<T>::Set_next(Box<T>* node) {

	S_Next = node;
	return;
}

template <class T>
Box<T>* Linked_List<T>::Begin() {

	return S_Head->p_next;
}

template <class T>
int Linked_List<T>::Get_counter() {

	return counter;
}

template <class T>
void Linked_List<T>::Lesser_counter() {

	counter--;
	return;
}


template <class T>
T* Linked_List<T>::Load_Node(FILE* fp) {
	char buffer[256] = { 0, };
	T* new_node = new T;
	fgets(buffer, 256, fp);
	sscanf(buffer, "%s\t%d\t%d\t%d\t%d", new_node->s_name, &new_node->i_age, &new_node->i_kor, &new_node->i_eng, &new_node->i_math);
	new_node->i_total = new_node->i_kor + new_node->i_eng + new_node->i_math;
	new_node->i_avg = new_node->i_total / 3.0;
	

	return new_node;

}
// ------------------------------------> ��� ������ � ������ ���� �𸣱⶧���� �ٸ� ������ �̵����Ѿ� ��