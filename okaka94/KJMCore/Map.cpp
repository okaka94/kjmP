#include "Map.h"

bool Map::Build(ID3D11Device* pd3dDevice, UINT width, UINT height, Camera* cam) {
	rows_num = height;
	cols_num = width;
	m_VertexList.resize((width) * (height));		// 2^n + 1 개수로 정점 구성해야 공간 분할시 셀이 잘리지 않음
	
	int half_width = width / 2;
	int half_height = height / 2;
	float cell_size = 1.0f;									// 정점간 거리 조절로 셀 하나의 크기 조정 가능

	for (int row = 0; row < height; row++) {	
		for (int col = 0; col < width; col++) {
			m_VertexList[row * width + col].p = { (float)(col - half_width) * cell_size, 
			0.0f ,
			(float)(half_height - row) * cell_size };  // z 좌표는 - 연산 (좌상단 정점 -1,0,1)
			m_VertexList[row * width + col].c = { 1.0f,1.0f,1.0f,1.0f };
			m_VertexList[row * width + col].t = { (float)col / (width - 1)*10, (float)row / (height - 1)*10 };			// uv좌표계는 0 ~ 1로 정규화
		}
	}

	m_IndexList.resize((width - 1) * (height - 1) * 2 * 3);		// 셀 하나에 삼각형 페이스 2개 * 페이스 1개에 인덱스 3개
	UINT index = 0;
	for (int row = 0; row < height - 1; row++) {				// width가 9면 7정점에서 8,16,17까지 한번에 인덱싱하므로 row < height - 1 이런식으로 만들면 됨
		for (int col = 0; col < width - 1; col++) {
			UINT next_row = row + 1;
			//UINT next_col = col + 1;
			m_IndexList[index + 0] = row * width + col;
			m_IndexList[index + 1] = m_IndexList[index + 0] + 1;	// 시계방향 인덱싱
			m_IndexList[index + 2] = next_row * width + col;

			m_IndexList[index + 3] = m_IndexList[index + 2];
			m_IndexList[index + 4] = m_IndexList[index + 1];
			m_IndexList[index + 5] = m_IndexList[index + 3] + 1;

			index += 6;
		}
	}

	//Create_Qtree(pd3dDevice,cam);

	return true;
}

bool Map::Create_Qtree(ID3D11Device* pd3dDevice, Camera* cam) {

	Map_Qtree.Create(pd3dDevice ,cam , rows_num, cols_num, &m_VertexList);

	return true;
}
bool Map::Render() {

	Map_Qtree.Frame();
	
	for (auto node : Map_Qtree.m_Draw_list)
	{
		Pre_Render();
		m_pImmediateContext->IASetIndexBuffer(	node->m_Index_buffer, DXGI_FORMAT_R32_UINT, 0);
		m_pImmediateContext->DrawIndexed(node->m_Index_list.size(), 0, 0);
	}
	return true;
}