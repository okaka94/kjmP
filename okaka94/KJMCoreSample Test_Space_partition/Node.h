#pragma once
#include "Shape.h"

class Node
{
public:
	bool						m_bLeaf;
	ID3D11Device*				m_pd3dDevice = nullptr;
	std::vector<PNCTVertex>*	m_pVertexList;
	std::vector<DWORD>			m_Index_list;
	DWORD						m_Corner[4];
	int							m_Depth;
	OBB							m_OBB;
	ID3D11Buffer*				m_Index_buffer = nullptr;
	std::vector<Node*>			m_Child;
public:
	void		Create_child(Node* parent, DWORD col_num, DWORD row_num);
	void		CreateIndexList(std::vector<PNCTVertex>* m_pVertexList,DWORD col_num, DWORD row_num);
	HRESULT		CreateIndexBuffer(DWORD col_num, DWORD row_num);
public:
	Node(Node* parent, DWORD LT, DWORD RT, DWORD RB, DWORD LB, DWORD col_num, DWORD row_num, ID3D11Device* pd3dDevice, std::vector<PNCTVertex>* m_pVertexList);
	virtual ~Node();
};

