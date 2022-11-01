#include "Node.h"


void	Node::Create_child(Node* parent, DWORD col_num, DWORD row_num) {
	DWORD LT = parent->m_Corner[0];
	DWORD RT = parent->m_Corner[1];
	DWORD RB = parent->m_Corner[2];
	DWORD LB = parent->m_Corner[3];
	DWORD CT = (LT + RT) / 2;
	DWORD CR = (RT + RB) / 2;
	DWORD CB = (LB + RB) / 2;
	DWORD CL = (LT + LB) / 2;
	DWORD C = (LT + RB) / 2;
	//시계방향 - 다시확인
	m_Child[0] = new Node(parent, LT, CT, C, CL, col_num, row_num);
	m_Child[1] = new Node(parent, CT, RT, CR, C, col_num, row_num);
	m_Child[2] = new Node(parent, LT, C, CB, LB, col_num, row_num);
	m_Child[3] = new Node(parent, C, CR, RB, CB, col_num, row_num);


}

void	Node::CreateIndexList(DWORD col_num, DWORD row_num) {


}

HRESULT	Node::CreateIndexBuffer(DWORD col_num, DWORD row_num) {


}

Node::Node(Node* parent, DWORD LT, DWORD RT, DWORD RB, DWORD LB, DWORD col_num, DWORD row_num) {


}

Node::~Node() {


}