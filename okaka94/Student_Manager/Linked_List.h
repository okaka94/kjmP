#pragma once
#include <iostream>


template <class T>							// Box를 만들어서 next, prev 포인터 달아주기  // Head와 Next가 필요한 것이 아니라 자료형 무관하게 연결이 가능하도록 포장하는 것
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


template <class T>										// Box(클래스 템플릿) 객체를 생성할 때 <> 안에 자료형 넣어주는 것 
class Linked_List
{
	

private:
	Box<T>* S_Head = NULL;										// 연결리스트에 필요한 멤버
	Box<T>* S_Next = NULL;
	static int counter;

public:
	Linked_List();												// 연결리스트 클래스는 노드의 연결 기능만 수행하도록
	~Linked_List();
	void Init();												

	void Insert_back(T* new_node);
	//void Insert_front(T* new_node);          // 구현했으나 사용되지 않음
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


//============================================================== cpp 파일==========================================
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
void Linked_List<T>::Init() {        //  초기화
	
	S_Head->p_prev = nullptr;
	S_Head->p_next = nullptr;
	S_Next = S_Head;
	counter = 0;                        

	return;
}



template <class T>								//  student로 특화된 템플릿임 (나중에 특화 템플릿으로 수정하기)
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

	printf("이름 : ");
	scanf("%s", new_node->s_name);
	printf("나이 : ");
	scanf("%d", &new_node->i_age);
	printf("국어 점수 : ");
	scanf("%d", &new_node->i_kor);
	printf("영어 점수 : ");
	scanf("%d", &new_node->i_eng);
	printf("수학 점수 : ");
	scanf("%d", &new_node->i_math);
	new_node->i_total = new_node->i_kor + new_node->i_eng + new_node->i_math;
	new_node->i_avg = new_node->i_total / 3.0;


	return new_node;

}

template <class T>
void Linked_List<T>::Insert_back(T* new_data) {                                            // 맨 뒤에 추가하기

	Box<T>* new_node = new Box<T>;
	new_node->m_data = new_data;
	S_Next->p_next = new_node;

	new_node->p_prev = S_Next;



	S_Next = new_node;
	counter++;

	return;
}
//template <class T>
//void Linked_List<T>::Insert_front(T* new_node) {                                            // 맨 앞에 추가하기
//
//	if (S_Head->p_next == nullptr) {                                               // 연결된 노드가 없는 상태라면 뒤에 추가하는 것과 같다
//		Insert_back(new_node);
//	}
//	else {
//		Box* old_node = S_Head->p_next;                                        // 기존의 최전방 노드
//		S_Head->p_next = new_node;                                                 // 새로운 최전방 노드
//		old_node->p_prev = new_node;                                               // 새로운 노드의 양방향 연결
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
// ------------------------------------> 노드 생성은 어떤 형식이 될지 모르기때문에 다른 곳으로 이동시켜야 함