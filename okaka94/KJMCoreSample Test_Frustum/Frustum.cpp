#include "Frustum.h"


void	Frustum::Create_frustum(Matrix* V_mat, Matrix* P_mat) {

	TBASIS_EX::TMatrix view = *(TBASIS_EX::TMatrix*)V_mat;
	TBASIS_EX::TMatrix proj = *(TBASIS_EX::TMatrix*)P_mat;

	TBASIS_EX::TMatrix matInvViewProj = view * proj;
	TBASIS_EX::D3DXMatrixInverse(&matInvViewProj, NULL, &matInvViewProj);

	m_Vertex[0] = TBASIS_EX::TVector3(-1.0f, 1.0f, 0.0f);
	m_Vertex[1] = TBASIS_EX::TVector3(-1.0f, 1.0f, 1.0f);
	m_Vertex[2] = TBASIS_EX::TVector3(1.0f, 1.0f, 1.0f);
	m_Vertex[3] = TBASIS_EX::TVector3(1.0f, 1.0f, 0.0f);
	m_Vertex[4] = TBASIS_EX::TVector3(-1.0f, -1.0f, 0.0f);
	m_Vertex[5] = TBASIS_EX::TVector3(-1.0f, -1.0f, 1.0f);
	m_Vertex[6] = TBASIS_EX::TVector3(1.0f, -1.0f, 1.0f);
	m_Vertex[7] = TBASIS_EX::TVector3(1.0f, -1.0f, 0.0f);

	for (int iVer = 0; iVer < 8; iVer++)
	{
		TBASIS_EX::D3DXVec3TransformCoord(&m_Vertex[iVer], &m_Vertex[iVer], &matInvViewProj);
	}
	// 프러스텀이 안쪽을 향하도록 구성
	// 상단
	  // 1    2
	  // 0    3
	// 하단
	  // 5    6
	  // 4    7  
	m_Plane[0].Create(*((Vector*)&m_Vertex[0]),
		*((Vector*)&m_Vertex[1]),
		*((Vector*)&m_Vertex[5])); // left
	m_Plane[1].Create(*((Vector*)&m_Vertex[2]), // right
		*((Vector*)&m_Vertex[3]),
		*((Vector*)&m_Vertex[6]));
	m_Plane[2].Create(*((Vector*)&m_Vertex[0]), // top
		*((Vector*)&m_Vertex[2]),
		*((Vector*)&m_Vertex[1]));
	m_Plane[3].Create(*((Vector*)&m_Vertex[5]), // bottom
		*((Vector*)&m_Vertex[6]),
		*((Vector*)&m_Vertex[7]));
	m_Plane[4].Create(*((Vector*)&m_Vertex[3]), // near
		*((Vector*)&m_Vertex[0]),
		*((Vector*)&m_Vertex[4]));
	m_Plane[5].Create(*((Vector*)&m_Vertex[1]), // far
		*((Vector*)&m_Vertex[2]),
		*((Vector*)&m_Vertex[5]));

}

P_POSITION Frustum::Classify_point(Vector v) {

	for (int iPlane = 0; iPlane < 6; iPlane++)
	{
		float fDistance = m_Plane[iPlane].a * v.x +	m_Plane[iPlane].b * v.y + m_Plane[iPlane].c * v.z + m_Plane[iPlane].d;
		// 평면 NormV이 원점을 바라보고 있으면 d값은 양수가 됨 , d는 원점과의 거리
		if (fDistance == 0) return P_ONPLANE;
		if (fDistance < 0) return P_FRONT;
	}

	return P_BACK;
}
