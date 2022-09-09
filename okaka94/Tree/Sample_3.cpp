#include "Sample.h"
#include <iostream>
#include <queue>


class Tree {
public:

	int		m_data;
	int		m_depth;
	Tree*	m_child[2];
	Tree*	m_parent;



public:
	Tree() {
		m_data = 0;
		m_depth = 0;
		m_child[0] = nullptr;
		m_child[1] = nullptr;
		m_parent   = nullptr;
	};
	virtual ~Tree() {
		delete m_child[0];
		delete m_child[1];
		m_child[0] = nullptr;
		m_child[1] = nullptr;				
	};

};
///////////////////////////////////////////////////////////////////
int node_counter = 0;
//int max_depth = 2;
int idx = 0;
int arr[7] = { 5,9,1,4,15,6,22 };
Tree* Root = nullptr;

Tree* Create_node(Tree* parent,int data) {
	Tree* child = new Tree;

	child->m_data = data;
	if (parent != nullptr)
		child->m_depth = parent->m_depth + 1;

	child->m_child[0] = nullptr;
	child->m_child[1] = nullptr;
	child->m_parent = parent;

	return child;
}

void Build_BST(Tree* node,int data) {


	//if (node->m_depth >= max_depth) return;
	if (idx >= 7) return;

	
	if (node->m_data > data) {
		if (node->m_child[0] == nullptr) {
			node->m_child[0] = Create_node(node, data);
			return;
		}
		

		Build_BST(node->m_child[0], data);
	}
	
	else {
		if (node->m_child[1] == nullptr) {
			node->m_child[1] = Create_node(node, data);
			return;
		}
		
		Build_BST(node->m_child[1], data);
	}
	

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

void Search(int n, Tree* node = Root) {

	if (node == nullptr) return;

	if (node->m_data > n) {


		Search(n, node->m_child[0]);
	}

	else if (node->m_data < n) {


		Search(n, node->m_child[1]);
	}
	else
		std::cout << node->m_depth << "층에 있습니다" << std::endl;
		


	return;
}





int main() {

	

	Root = Create_node(nullptr,arr[0]);

	for (int i = 1; i < 7; i++) {
		Build_BST(Root, arr[i]);
	}

	

	Print(Root);
	std::cout << std::endl;

	Print_level(Root);

	std::cout << std::endl;


	Search(15);




	delete Root;

	return 0;
}


