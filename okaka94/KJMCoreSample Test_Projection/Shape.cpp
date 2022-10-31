#include "Shape.h"

void Shape_box::CreateVertexList() {
	// 상단
	  // 1    2
	  // 0    3
	// 하단
	  // 5    6
	  // 4    7  


	m_VertexList.resize(24);

	// 상단
	m_VertexList[0].p = { -1.0f,  1.0f, -1.0f };	m_VertexList[0].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[0].t = { 0.0f,1.0f };
	m_VertexList[1].p = { -1.0f,  1.0f, 1.0f };		m_VertexList[1].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[1].t = { 0.0f,0.0f };
	m_VertexList[2].p = { 1.0f, 1.0f, 1.0f };		m_VertexList[2].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[2].t = { 1.0f,0.0f };
	m_VertexList[3].p = { 1.0f, 1.0f, -1.0f };		m_VertexList[3].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[3].t = { 1.0f,1.0f };

	// 하단
	m_VertexList[4].p = { -1.0f,  -1.0f, -1.0f };	m_VertexList[4].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[4].t = { 1.0f,1.0f };
	m_VertexList[5].p = { -1.0f,  -1.0f, 1.0f };	m_VertexList[5].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[5].t = { 1.0f,0.0f };
	m_VertexList[6].p = { 1.0f, -1.0f, 1.0f };		m_VertexList[6].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[6].t = { 0.0f,0.0f };
	m_VertexList[7].p = { 1.0f, -1.0f, -1.0f };		m_VertexList[7].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[7].t = { 0.0f,1.0f };

	// 앞면
	m_VertexList[8].p = { -1.0f,  -1.0f, -1.0f };	m_VertexList[8].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[8].t = { 0.0f,1.0f };
	m_VertexList[9].p = { -1.0f,  1.0f, -1.0f };	m_VertexList[9].c = { 1.0f, 1.0f, 1.0f, 1.0f };		m_VertexList[9].t = { 0.0f,0.0f };
	m_VertexList[10].p = { 1.0f, 1.0f, -1.0f };		m_VertexList[10].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[10].t = { 1.0f,0.0f };
	m_VertexList[11].p = { 1.0f, -1.0f, -1.0f };	m_VertexList[11].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[11].t = { 1.0f,1.0f };

	// 뒷면
	m_VertexList[12].p = { 1.0f,  -1.0f, 1.0f };	m_VertexList[12].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[12].t = { 0.0f,1.0f };
	m_VertexList[13].p = { 1.0f,  1.0f, 1.0f };		m_VertexList[13].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[13].t = { 0.0f,0.0f };
	m_VertexList[14].p = { -1.0f, 1.0f, 1.0f };		m_VertexList[14].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[14].t = { 1.0f,0.0f };
	m_VertexList[15].p = { -1.0f, -1.0f, 1.0f };	m_VertexList[15].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[15].t = { 1.0f,1.0f };

	// 왼쪽면
	m_VertexList[16].p = { -1.0f,  -1.0f, 1.0f };	m_VertexList[16].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[16].t = { 0.0f,1.0f };
	m_VertexList[17].p = { -1.0f,  1.0f, 1.0f };	m_VertexList[17].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[17].t = { 0.0f,0.0f };
	m_VertexList[18].p = { -1.0f, 1.0f, -1.0f };	m_VertexList[18].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[18].t = { 1.0f,0.0f };
	m_VertexList[19].p = { -1.0f, -1.0f, -1.0f };	m_VertexList[19].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[19].t = { 1.0f,1.0f };

	// 오른쪽면
	m_VertexList[20].p = { 1.0f,  -1.0f, -1.0f };	m_VertexList[20].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[20].t = { 0.0f,1.0f };
	m_VertexList[21].p = { 1.0f,  1.0f, -1.0f };	m_VertexList[21].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[21].t = { 0.0f,0.0f };
	m_VertexList[22].p = { 1.0f, 1.0f, 1.0f };		m_VertexList[22].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[22].t = { 1.0f,0.0f };
	m_VertexList[23].p = { 1.0f, -1.0f, 1.0f };		m_VertexList[23].c = { 1.0f, 1.0f, 1.0f, 1.0f };	m_VertexList[23].t = { 1.0f,1.0f };


	m_InitVertexList = m_VertexList;

}

void Shape_box::CreateIndexList() {

	m_IndexList.resize(36);
	int iIndex = 0;

	// 상단
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 3; 	m_IndexList[iIndex++] = 3;	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2;
	// 하단
	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 7; 	m_IndexList[iIndex++] = 5;  m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 7; 	m_IndexList[iIndex++] = 6;
	// 앞면
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 11; m_IndexList[iIndex++] = 11;	m_IndexList[iIndex++] = 9; m_IndexList[iIndex++] = 10;
	// 뒷면
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13;	m_IndexList[iIndex++] = 15; m_IndexList[iIndex++] = 15;	m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14;
	// 왼쪽면
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17;	m_IndexList[iIndex++] = 19; m_IndexList[iIndex++] = 19;	m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18;
	// 오른쪽면
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 23; m_IndexList[iIndex++] = 23;	m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22;


}

bool Shape_box::Render() {

	Pre_Render();
	Post_Render();

	return true;
}

bool Shape_box::Frame() {

	
	return true;
}