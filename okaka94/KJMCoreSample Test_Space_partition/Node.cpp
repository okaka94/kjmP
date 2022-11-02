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
	//시계방향 
	m_Child[0] = new Node(parent, LT, CT, C, CL, col_num, row_num, m_pd3dDevice, m_pVertexList);
	m_Child[1] = new Node(parent, CT, RT, CR, C, col_num, row_num, m_pd3dDevice, m_pVertexList);
	m_Child[2] = new Node(parent, CL, C, CB, LB, col_num, row_num, m_pd3dDevice, m_pVertexList);
	m_Child[3] = new Node(parent, C, CR, RB, CB, col_num, row_num, m_pd3dDevice, m_pVertexList);


}

void	Node::CreateIndexList(std::vector<SimpleVertex>* m_pVertexList, DWORD col_num, DWORD row_num) {

	DWORD LT = m_Corner[0];
	DWORD RT = m_Corner[1];
	DWORD RB = m_Corner[2];
	DWORD LB = m_Corner[3];
	DWORD Cells_row_num = (LB - LT) / col_num;
	DWORD Cells_col_num = RT - LT;
	DWORD Cells_total_num = Cells_row_num * Cells_col_num;
	m_Index_list.resize(Cells_total_num * 2 * 3);
	
	int iIndex = 0;
	Vector Min, Max;

	
	Min.x = (*m_pVertexList)[LB].p.x;
	Min.y = 100000.0f;
	Min.z = (*m_pVertexList)[LB].p.z;
	Max.x = (*m_pVertexList)[RT].p.x;
	Max.y = -100000.0f;
	Max.z = (*m_pVertexList)[RT].p.z;

	//Min.x = m_VertexList[LT].p.x;
	//Min.y = 100000.0f;
	//Min.z = m_VertexList[LB].p.z;
	//Max.x = m_VertexList[dwTR].p.x;
	//Max.y = -100000.0f;
	//Max.z = m_VertexList[dwTL].p.z;

	for (int dwRow = 0; dwRow < Cells_row_num; dwRow++)
	{
		for (int dwCol = 0; dwCol < Cells_col_num; dwCol++)
		{
			m_Index_list[iIndex + 0] = LT + dwCol + (dwRow * col_num);
			m_Index_list[iIndex + 1] = m_Index_list[iIndex + 0] + 1;
			m_Index_list[iIndex + 2] = LT + dwCol + ((dwRow + 1) * col_num);

			m_Index_list[iIndex + 3] = m_Index_list[iIndex + 2];
			m_Index_list[iIndex + 4] = m_Index_list[iIndex + 1];
			m_Index_list[iIndex + 5] = m_Index_list[iIndex + 2] + 1;

			for (DWORD dwVertex = 0; dwVertex < 6; dwVertex++)
			{
				if (Min.y > (*m_pVertexList)[m_Index_list[iIndex + dwVertex]].p.y)
				{
					Min.y = (*m_pVertexList)[m_Index_list[iIndex + dwVertex]].p.y;
				}
				if (Max.y < (*m_pVertexList)[m_Index_list[iIndex + dwVertex]].p.y)
				{
					Max.y = (*m_pVertexList)[m_Index_list[iIndex + dwVertex]].p.y;
				}
			}
			iIndex += 6;
		}
	}
	//m_dwFace = m_IndexList.size() / 3;
	
	m_OBB.v_center = (Max + Min) * 0.5f;
	
	m_OBB.axis[0] = { 1,0,0 };
	m_OBB.axis[1] = { 0,1,0 };
	m_OBB.axis[2] = { 0,0,1 };
	m_OBB.extent[0] = Max.x - m_OBB.v_center.x;
	m_OBB.extent[1] = Max.y - m_OBB.v_center.y;
	m_OBB.extent[2] = Max.z - m_OBB.v_center.z;
}



HRESULT	Node::CreateIndexBuffer(DWORD col_num, DWORD row_num) {

	HRESULT hr;
	CreateIndexList(m_pVertexList, col_num, row_num);
	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(DWORD) * m_Index_list.size(); // 바이트 용량
	// GPU 메모리에 할당
	bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_Index_list.at(0);
	hr = m_pd3dDevice->CreateBuffer(&bd , &sd , &m_Index_buffer);
	return hr;

}

Node::Node(Node* parent, DWORD LT, DWORD RT, DWORD RB, DWORD LB, DWORD col_num, DWORD row_num, ID3D11Device* pd3dDevice, std::vector<SimpleVertex>* VertexList) {

	if (parent != nullptr)
	{
		m_Depth = parent->m_Depth + 1;
	}
	m_Corner[0] = LT;
	m_Corner[1] = RT;
	m_Corner[2] = RB;
	m_Corner[3] = LB;
	m_bLeaf = false;
	m_Child.resize(4);
	m_pd3dDevice = pd3dDevice;
	m_pVertexList = VertexList;

	
	CreateIndexBuffer(col_num, row_num);
	

}

Node::~Node() {

	if (m_Index_buffer)	m_Index_buffer->Release();
	delete m_Child[0];
	delete m_Child[1];
	delete m_Child[2];
	delete m_Child[3];
	m_Child[0] = nullptr;
	m_Child[1] = nullptr;
	m_Child[2] = nullptr;
	m_Child[3] = nullptr;

}