#include "Map.h"

bool Map::Build(ID3D11Device* pd3dDevice, UINT width, UINT height, Camera* cam) {
	rows_num = height;
	cols_num = width;
	m_VertexList.resize((width) * (height));		// 2^n + 1 ������ ���� �����ؾ� ���� ���ҽ� ���� �߸��� ����
	
	int half_width = width / 2;
	int half_height = height / 2;
	float cell_size = 1.0f;									// ������ �Ÿ� ������ �� �ϳ��� ũ�� ���� ����

	for (int row = 0; row < height; row++) {	
		for (int col = 0; col < width; col++) {
			m_VertexList[row * width + col].p = { (float)(col - half_width) * cell_size, 
			0.0f ,
			(float)(half_height - row) * cell_size };  // z ��ǥ�� - ���� (�»�� ���� -1,0,1)
			m_VertexList[row * width + col].c = { 1.0f,1.0f,1.0f,1.0f };
			m_VertexList[row * width + col].t = { (float)col / (width - 1)*10, (float)row / (height - 1)*10 };			// uv��ǥ��� 0 ~ 1�� ����ȭ
		}
	}

	m_IndexList.resize((width - 1) * (height - 1) * 2 * 3);		// �� �ϳ��� �ﰢ�� ���̽� 2�� * ���̽� 1���� �ε��� 3��
	UINT index = 0;
	for (int row = 0; row < height - 1; row++) {				// width�� 9�� 7�������� 8,16,17���� �ѹ��� �ε����ϹǷ� row < height - 1 �̷������� ����� ��
		for (int col = 0; col < width - 1; col++) {
			UINT next_row = row + 1;
			//UINT next_col = col + 1;
			m_IndexList[index + 0] = row * width + col;
			m_IndexList[index + 1] = m_IndexList[index + 0] + 1;	// �ð���� �ε���
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