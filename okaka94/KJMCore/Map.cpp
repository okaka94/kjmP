#include "Map.h"

bool Map::Build(ID3D11Device* pd3dDevice, UINT width, UINT height, Camera* cam) {
	rows_num = height;
	cols_num = width;
	m_VertexList.resize((width) * (height));		// 2^n + 1 개수로 정점 구성해야 공간 분할시 셀이 잘리지 않음
	
	int half_width = width / 2;
	int half_height = height / 2;
	//float cell_size = 1.0f;									// 정점간 거리 조절로 셀 하나의 크기 조정 가능

	if (m_Height_list.size() == 0) {
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				m_VertexList[row * width + col].p = { (float)(col - half_width) * cell_size,
				0,
				(float)(half_height - row) * cell_size };  // z 좌표는 - 연산 (좌상단 정점 -1,0,1)
				m_VertexList[row * width + col].c = { 1.0f,1.0f,1.0f,1.0f };
				m_VertexList[row * width + col].t = { (float)col / (width - 1) * 10, (float)row / (height - 1) * 10 };			// uv좌표계는 0 ~ 1로 정규화
			}
		}
	}

	else{
		for (int row = 0; row < height; row++) {	
			for (int col = 0; col < width; col++) {
				m_VertexList[row * width + col].p = { (float)(col - half_width) * cell_size,
				m_Height_list[row * width + col] * max_Height,
				(float)(half_height - row) * cell_size };  // z 좌표는 - 연산 (좌상단 정점 -1,0,1)
				m_VertexList[row * width + col].c = { 1.0f,1.0f,1.0f,1.0f };
				m_VertexList[row * width + col].t = { (float)col / (width - 1)*10, (float)row / (height - 1)*10 };			// uv좌표계는 0 ~ 1로 정규화
			}
		}
	}

	m_IndexList.resize((width - 1) * (height - 1) * 2 * 3);		// 셀 하나에 삼각형 페이스 2개 * 페이스 1개에 인덱스 3개
	faces_num = m_IndexList.size() / 3;
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

	//Generate Normal

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

bool Map::Load_height_map(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, W_STR Texture) {

	ComPtr<ID3D11Resource> texture;
	HRESULT hr = DirectX::CreateWICTextureFromFileEx(pd3dDevice, Texture.c_str(), 0, 
		D3D11_USAGE_STAGING, 0,										// Staging 
		D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE, 0, 
		WIC_LOADER_DEFAULT, texture.GetAddressOf(), nullptr);

	ID3D11Texture2D* tex_2d = NULL;
	if (FAILED(texture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&tex_2d))) {			// texture Resoucre -> tex2D
		return false;
	}

	D3D11_TEXTURE2D_DESC td;
	tex_2d->GetDesc(&td);

	m_Height_list.resize(td.Height * td.Width);

	D3D11_MAPPED_SUBRESOURCE	Mapped_face;		// D3D11_MAPPED_SUBRESOURCE : Provides access to subresource data.
	if (SUCCEEDED(pContext->Map(tex_2d, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &Mapped_face))) {
		UCHAR* Texels = (UCHAR*)Mapped_face.pData;
		for (UINT row = 0; row < td.Height; row++) {
			UINT row_start = row * Mapped_face.RowPitch;
			for (UINT col = 0; col < td.Width; col++) {
				UINT col_start = col * 4;
				UINT Green = Texels[row_start + col_start + 1];
				m_Height_list[row * td.Width + col] = (float)Green / 255.0f;		// 0 ~ 1 Range
			}
		}
		pContext->Unmap(tex_2d, D3D11CalcSubresource(0, 0, 1));
	}

	rows_num = td.Height;
	cols_num = td.Width;

	tex_2d->Release();		// uuidof -> release()

	return true;
}

void Map::Gen_vertex_n() {

	std::vector<Vector> face_normals;
	face_normals.resize(faces_num);
	UINT face_idx = 0;
	for (UINT i = 0; i < m_IndexList.size(); i += 3) {
		UINT i0 = m_IndexList[i+0];
		UINT i1 = m_IndexList[i+1];
		UINT i2 = m_IndexList[i+2];
		face_normals[face_idx++] = Calc_face_normal(i0,i1,i2);
	}
	struct Vertex_info {
		std::vector<UINT>	adjacent_face_idx;
		Vector				vertex_normal;
	};

	std::vector<Vertex_info> Vertex_info_list;
	Vertex_info_list.resize(rows_num* cols_num);
	for (UINT face = 0; face < faces_num; face++) {
		for (UINT i = 0; i < 3; i++) {
			UINT i0 = m_IndexList[face * 3 + i];						// i0 = 해당 인덱스의 정점 위치가 들어있음
			Vertex_info_list[i0].adjacent_face_idx.push_back(face);		// i0번 정점에 인접한 face의 번호를 push_back
		}

	}
	for (UINT vertex_num = 0; vertex_num < Vertex_info_list.size(); vertex_num++) {
		for (UINT i = 0; i < Vertex_info_list[vertex_num].adjacent_face_idx.size(); i++) {
			Vertex_info_list[vertex_num].vertex_normal += face_normals[Vertex_info_list[vertex_num].adjacent_face_idx[i]];
		}
		Vertex_info_list[vertex_num].vertex_normal.Normalize_vector();
		m_VertexList[vertex_num].n = Vertex_info_list[vertex_num].vertex_normal;
	}

}

Vector Map::Calc_face_normal(UINT i0, UINT i1, UINT i2) {

	Vector face_normal;

	Vector E0 = m_VertexList[i1].p - m_VertexList[i0].p;
	Vector E1 = m_VertexList[i2].p - m_VertexList[i0].p;
	
	face_normal = E0 ^ E1;
	face_normal.Normalize_vector();
		
	return face_normal;
}

float Map::Get_height(float x, float z) {


	int cell_cols_num = cols_num - 1;
	int cell_rows_num = rows_num - 1;

	float cell_x = (float)(cell_cols_num * cell_size / 2.0f + x);
	float cell_z = (float)(cell_rows_num * cell_size / 2.0f + z);

	cell_x = cell_x / cell_size;
	cell_z = cell_z / cell_size;

	float vertex_col = ::floorf(cell_x);
	float vertex_row = ::floorf(cell_z);

	
	if (vertex_col < 0.0f)  vertex_col = 0.0f;
	if (vertex_row < 0.0f)  vertex_row = 0.0f;
	if ((float)(cell_cols_num - 2) < vertex_col)	vertex_col = (float)(cell_cols_num - 2);
	if ((float)(cell_rows_num - 2) < vertex_row)	vertex_row = (float)(cell_rows_num - 2);

	
	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D
	float A = Get_height_map((int)vertex_row, (int)vertex_col);
	float B = Get_height_map((int)vertex_row, (int)vertex_col + 1);
	float C = Get_height_map((int)vertex_row + 1, (int)vertex_col);
	float D = Get_height_map((int)vertex_row + 1, (int)vertex_col + 1);

	float delta_x = cell_x - vertex_col;
	float delta_z = cell_z - vertex_row;
	float height = 0.0f;

	// 위 삼각형
	if (delta_z < (1.0f - delta_x))  //ABC
	{
		float height_diff_x = B - A; // A->B
		float height_diff_z = C - A; // A->C	
						  
		height = A + Lerp(0.0f, height_diff_x, delta_x) + Lerp(0.0f, height_diff_z, delta_z);
	}
	// 아래페이스를 기준으로 보간한다.
	else // DCB
	{
		float uy = C - D; // D->C
		float vy = B - D; // D->B
						  
		height = D + Lerp(0.0f, uy, 1.0f - delta_x) + Lerp(0.0f, vy, 1.0f - delta_z);
	}
	return height;
}


float Map::Get_height_map(int row, int col) {

	return m_VertexList[row * (cols_num) + col].p.y;		 // (cols_num) == width ?? row_num이 맞는지?

}

float Map::Lerp(float fStart, float fEnd, float fTangent)
{
	return fStart - (fStart * fTangent) + (fEnd * fTangent);
}