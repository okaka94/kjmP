#include "Quad_tree.h"


bool	Quad_tree::Create(ID3D11Device* pd3dDevice, Camera* Main_cam, DWORD rows_num, DWORD cols_num, std::vector<PNCTVertex>* pVertexList , int iMaxDepth ) {

    m_pCamera = Main_cam;
    //m_pMap = pMap;
    m_MaxDepth = iMaxDepth;
    m_rows_num = rows_num;
    m_cols_num = cols_num;
    
    m_pRootNode = new Node(nullptr, 0, m_cols_num - 1, (m_cols_num * m_rows_num) - 1, m_cols_num * (m_rows_num - 1), m_cols_num, m_rows_num, pd3dDevice, pVertexList);
    Build_tree(m_pRootNode);
    return true;

	return true;
}

void	Quad_tree::Build_tree(Node* node) {

    if(node == nullptr) return;
    if (Is_subdivided(node) == false)
    {
        node->m_bLeaf = true;
        //m_Leaf_list.push_back(node);
        return;
    }
    node->Create_child(node, m_cols_num, m_rows_num);
        

    Build_tree(node->m_Child[0]);
    Build_tree(node->m_Child[1]);
    Build_tree(node->m_Child[2]);
    Build_tree(node->m_Child[3]);
}

bool	Quad_tree::Is_subdivided(Node* node) {
 
        if ((node->m_Corner[1] - node->m_Corner[0]) == 1) return false;
        if (node->m_Depth < m_MaxDepth) return true;
        return false;
 }

bool	Quad_tree::Frame() {

    m_Draw_list.clear();
    VisibleNode(m_pRootNode);

    return true;
}

//bool	Quad_tree::Render();

Node* Quad_tree::VisibleNode(Node* node) {

    P_POSITION Ret = m_pCamera->m_Frustum.Classify_OBB(node->m_OBB);
    if (P_FRONT == Ret)// 완전포함.
    {
        m_Draw_list.push_back(node);
        return node;
    }
    if (P_SPANNING == Ret) // 걸쳐있다.
    {
        if (node->m_bLeaf)
        {
            m_Draw_list.push_back(node);
        }
        else
        {
            for (int iNode = 0; iNode < 4; iNode++)
            {
                VisibleNode(node->m_Child[iNode]);
            }
        }
    }

}

Quad_tree::~Quad_tree() {

    if (m_pRootNode)
    {
        delete m_pRootNode;
        m_pRootNode = nullptr;
    }
}