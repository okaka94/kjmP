#pragma once
#include "Node.h"
#include "Camera_debug.h"

class Quad_tree
{
public:
	Node*				m_pRootNode;
	int					m_MaxDepth;
	//TMap* m_pMap = nullptr;
	Camera*				m_pCamera = nullptr;
	//std::vector<Node*>	m_Leaf_list;
	std::vector<Node*>	m_Draw_list;
	DWORD				m_rows_num; 
	DWORD				m_cols_num;
public:
	bool	Create(ID3D11Device* pd3dDevice , Camera* Main_cam, DWORD rows_num, DWORD cols_num, std::vector<SimpleVertex>* pVertexList ,int iMaxDepth = 3);
	//bool	AddObject(TObject3D* pObj);
	void	Build_tree(Node* node);
	bool	Is_subdivided(Node* node);
	//TNode* FindNode(TNode* pNode, TObject3D* pObj);
	//void	Reset(Node* node);
	bool	Frame();
	//bool	Render();
	Node*	VisibleNode(Node* node);
	virtual ~Quad_tree();
};
