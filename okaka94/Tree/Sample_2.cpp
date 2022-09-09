#include "Sample.h"
#include <iostream>
#include <queue>
#include <math.h>
													// 배열을 통한 메모리할당 해보기

class Tree {
public:

	int		m_data;
	int		m_depth;
	Tree* m_child[2];



public:
	Tree() {
		m_data = 0;
		m_depth = 1;
		m_child[0] = nullptr;
		m_child[1] = nullptr;

	};
	virtual ~Tree() {

		//delete[] m_child;				// 이거 안됨
		/*delete m_child[0];
		delete m_child[1];
		m_child[0] = nullptr;
		m_child[1] = nullptr;

		std::cout << "소멸자 호출" << std::endl;*/

	};

};

int node_counter = 0;
int max_depth = 3;

Tree* Root = nullptr;
Tree* tree_array = nullptr;

Tree* Create_node(const Tree* parent) {
	Tree* child = &tree_array[node_counter];

	child->m_data = node_counter++;
	if (parent != nullptr)
		child->m_depth = parent->m_depth + 1;

	child->m_child[0] = nullptr;
	child->m_child[1] = nullptr;

	return child;
}

void Build_PBT(Tree* node) {


	if (node->m_depth >= max_depth) return;

	node->m_child[0] = Create_node(node);
	node->m_child[1] = Create_node(node);


	Build_PBT(node->m_child[0]);
	Build_PBT(node->m_child[1]);



	return;
}

void Print(Tree* node) {
	if (node == nullptr) return;

	Print(node->m_child[0]);
	Print(node->m_child[1]);

	std::cout << node->m_data << std::endl;



	return;
}

std::queue <Tree*> T_queue;

void Print_level(Tree* node) {

	if (node == nullptr) return;

	std::cout << node->m_data << std::endl;

	for (int i = 0; i < 2; i++) {
		if (node->m_child[i] != nullptr) {
			T_queue.push(node->m_child[i]);
		}
	}



	if (!T_queue.empty()) {
		Tree* temp = T_queue.front();
		T_queue.pop();
		Print_level(temp);
	}

}







int main() {

	
	int max_size = pow(2, max_depth) - 1;
	tree_array = new Tree[max_size];						// 메모리가 미리 할당되어있음 


	Root = Create_node(nullptr);								
	

	Build_PBT(Root);

	Print(Root);
	std::cout << std::endl;

	Print_level(Root);

	std::cout << std::endl;


	for (int i = 0; i < max_size; i++) {
		std::cout << tree_array[i].m_data << "\t";
	}



	delete[] tree_array;
	//delete Root;


	/*Tree Root;
	Tree* child_L =  Root.m_child[0] = new Tree;
	Tree* child_R = Root.m_child[1] = new Tree;

	delete child_L;
	delete child_R;*/

	return 0;
}


