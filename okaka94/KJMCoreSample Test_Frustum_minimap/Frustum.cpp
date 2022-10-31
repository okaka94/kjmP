#include "Frustum.h"

void	Frustum::Create_frustum_box(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) {
	Frustum_box = new Shape_box;
	Frustum_box->Create(pd3dDevice, pImmediateContext, L"DefaultShape_Constant.txt", L"../../data/map/grass_0.bmp");

}

bool	Frustum::Render(Matrix* V_mat, Matrix* P_mat) {

	Vector pos[8];
	pos[0] = *(Vector*)&m_Vertex[0];
	pos[1] = *(Vector*)&m_Vertex[1];
	pos[2] = *(Vector*)&m_Vertex[2];
	pos[3] = *(Vector*)&m_Vertex[3];
	pos[4] = *(Vector*)&m_Vertex[4];
	pos[5] = *(Vector*)&m_Vertex[5];
	pos[6] = *(Vector*)&m_Vertex[6];
	pos[7] = *(Vector*)&m_Vertex[7];
	

	// 상단
	Frustum_box->m_VertexList[0].p = pos[0];	Frustum_box->m_VertexList[0].c = { 1.0f, 1.0f, 1.0f, 0.5f };		Frustum_box->m_VertexList[0].t = { 0.0f,1.0f };
	Frustum_box->m_VertexList[1].p = pos[1];	Frustum_box->m_VertexList[1].c = { 1.0f, 1.0f, 1.0f, 0.5f };		Frustum_box->m_VertexList[1].t = { 0.0f,0.0f };
	Frustum_box->m_VertexList[2].p = pos[2];	Frustum_box->m_VertexList[2].c = { 1.0f, 1.0f, 1.0f, 0.5f };		Frustum_box->m_VertexList[2].t = { 1.0f,0.0f };
	Frustum_box->m_VertexList[3].p = pos[3];	Frustum_box->m_VertexList[3].c = { 1.0f, 1.0f, 1.0f, 0.5f };		Frustum_box->m_VertexList[3].t = { 1.0f,1.0f };

	// 하단
	Frustum_box->m_VertexList[4].p = pos[4];	Frustum_box->m_VertexList[4].c = { 1.0f, 0.0f, 1.0f, 0.5f };		Frustum_box->m_VertexList[4].t = { 1.0f,1.0f };
	Frustum_box->m_VertexList[5].p = pos[5];	Frustum_box->m_VertexList[5].c = { 1.0f, 0.0f, 1.0f, 0.5f };		Frustum_box->m_VertexList[5].t = { 1.0f,0.0f };
	Frustum_box->m_VertexList[6].p = pos[6];	Frustum_box->m_VertexList[6].c = { 1.0f, 0.0f, 1.0f, 0.5f };		Frustum_box->m_VertexList[6].t = { 0.0f,0.0f };
	Frustum_box->m_VertexList[7].p = pos[7];	Frustum_box->m_VertexList[7].c = { 1.0f, 0.0f, 1.0f, 0.5f };		Frustum_box->m_VertexList[7].t = { 0.0f,1.0f };

	// 앞면
	Frustum_box->m_VertexList[8].p = pos[4];	Frustum_box->m_VertexList[8].c = { 0.6f, 1.0f, 0.0f, 0.5f };		Frustum_box->m_VertexList[8].t = { 0.0f,1.0f };
	Frustum_box->m_VertexList[9].p = pos[0];	Frustum_box->m_VertexList[9].c = { 0.6f, 1.0f, 0.0f, 0.5f };		Frustum_box->m_VertexList[9].t = { 0.0f,0.0f };
	Frustum_box->m_VertexList[10].p = pos[3];	Frustum_box->m_VertexList[10].c = { 0.6f, 1.0f, 0.0f, 0.5f };		Frustum_box->m_VertexList[10].t = { 1.0f,0.0f };
	Frustum_box->m_VertexList[11].p = pos[7];	Frustum_box->m_VertexList[11].c = { 0.6f, 1.0f, 0.0f, 0.5f };		Frustum_box->m_VertexList[11].t = { 1.0f,1.0f };

	// 뒷면
	Frustum_box->m_VertexList[12].p = pos[6];	Frustum_box->m_VertexList[12].c = { 0.0f, 1.0f, 1.0f, 0.5f };	Frustum_box->m_VertexList[12].t = { 0.0f,1.0f };
	Frustum_box->m_VertexList[13].p = pos[2];	Frustum_box->m_VertexList[13].c = { 0.0f, 1.0f, 1.0f, 0.5f };	Frustum_box->m_VertexList[13].t = { 0.0f,0.0f };
	Frustum_box->m_VertexList[14].p = pos[1];	Frustum_box->m_VertexList[14].c = { 0.0f, 1.0f, 1.0f, 0.5f };	Frustum_box->m_VertexList[14].t = { 1.0f,0.0f };
	Frustum_box->m_VertexList[15].p = pos[5];	Frustum_box->m_VertexList[15].c = { 0.0f, 1.0f, 1.0f, 0.5f };	Frustum_box->m_VertexList[15].t = { 1.0f,1.0f };

	// 왼쪽면
	Frustum_box->m_VertexList[16].p = pos[5];	Frustum_box->m_VertexList[16].c = { 0.0f, 0.0f, 1.0f, 0.5f };	Frustum_box->m_VertexList[16].t = { 0.0f,1.0f };
	Frustum_box->m_VertexList[17].p = pos[1];	Frustum_box->m_VertexList[17].c = { 0.0f, 0.0f, 1.0f, 0.5f };	Frustum_box->m_VertexList[17].t = { 0.0f,0.0f };
	Frustum_box->m_VertexList[18].p = pos[0];	Frustum_box->m_VertexList[18].c = { 0.0f, 0.0f, 1.0f, 0.5f };	Frustum_box->m_VertexList[18].t = { 1.0f,0.0f };
	Frustum_box->m_VertexList[19].p = pos[4];	Frustum_box->m_VertexList[19].c = { 0.0f, 0.0f, 1.0f, 0.5f };	Frustum_box->m_VertexList[19].t = { 1.0f,1.0f };

	// 오른쪽면
	Frustum_box->m_VertexList[20].p = pos[7];	Frustum_box->m_VertexList[20].c = { 1.0f, 0.0f, 0.0f, 0.5f };	Frustum_box->m_VertexList[20].t = { 0.0f,1.0f };
	Frustum_box->m_VertexList[21].p = pos[3];	Frustum_box->m_VertexList[21].c = { 1.0f, 0.0f, 0.0f, 0.5f };	Frustum_box->m_VertexList[21].t = { 0.0f,0.0f };
	Frustum_box->m_VertexList[22].p = pos[2];	Frustum_box->m_VertexList[22].c = { 1.0f, 0.0f, 0.0f, 0.5f };	Frustum_box->m_VertexList[22].t = { 1.0f,0.0f };
	Frustum_box->m_VertexList[23].p = pos[6];	Frustum_box->m_VertexList[23].c = { 1.0f, 0.0f, 0.0f, 0.5f };	Frustum_box->m_VertexList[23].t = { 1.0f,1.0f };

	//Frustum_box->m_InitVertexList = Frustum_box->m_VertexList;

	//m_InitVertexList = m_VertexList;
	Frustum_box->SetMatrix(NULL, V_mat, P_mat);
	Frustum_box->UpdateVertexBuffer();
	Frustum_box->Render();

	return true;
}
	



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
		//if (fDistance == 0) return P_ONPLANE;		// 평면과 정점은 ONPLANE 판정 바로 리턴하기 애매함 
		if (fDistance < 0) return P_BACK;		// distance > 0 이면 평면의 앞에 , <0이면 평면의 뒤 
	}

	return P_FRONT;		// 모든 면의 안쪽에 있어야함 , 이 경우 ONPLANE 따로 판정 없기때문에 한면에 접하면서 내부에 있는 경우도 포함돼있음
}


P_POSITION Frustum::Classify_sphere(Sphere s) {

	Vector center = s.v_center;

	for (int iPlane = 0; iPlane < 6; iPlane++)
	{
		float fDistance = m_Plane[iPlane].a * center.x + m_Plane[iPlane].b * center.y + m_Plane[iPlane].c * center.z + m_Plane[iPlane].d;
		// 평면 NormV이 원점을 바라보고 있으면 d값은 양수가 됨 , d는 원점과의 거리
		//if (fDistance == 0) return P_ONPLANE;		// 평면과 정점은 ONPLANE 판정 바로 리턴하기 애매함 
		if (fDistance <= -(s.r)) return P_BACK;		// 평면으로부터 -r만큼의 거리값이 프러스텀 내부로 들어오는 마지노선임 , 따라서 -r보다 d값이 작다면 평면 밖임
	}

	return P_FRONT;		// 모든 면의 안쪽에 있어야함 , 이 경우 ONPLANE 따로 판정 없기때문에 한면에 접하면서 내부에 있는 경우도 포함돼있음
}

P_POSITION Frustum::Classify_AABB(AABB box) {

	//Vector min = box.v_min;
	//Vector max = box.v_max;

	//for (int iPlane = 0; iPlane < 6; iPlane++)
	//{
	//	float min_d = m_Plane[iPlane].a * min.x + m_Plane[iPlane].b * min.y + m_Plane[iPlane].c * min.z + m_Plane[iPlane].d;
	//	float max_d = m_Plane[iPlane].a * max.x + m_Plane[iPlane].b * max.y + m_Plane[iPlane].c * max.z + m_Plane[iPlane].d;

	//	if ((min_d * max_d) > 0 && (min_d < 0 || max_d < 0 )) return P_BACK;		
	//}

	return P_FRONT;	
}

P_POSITION	 Frustum::Classify_OBB(OBB box)
{
	float		PlaneToCenter = 0.0;
	float		fDistance = 0.0f;
	Vector		Dir_v;
	//T_POSITION  t_Position;

	//t_Position = P_FRONT;
	for (int iPlane = 0; iPlane < 6; iPlane++)
	{
		Dir_v = box.axis[0] * box.extent[0];
		fDistance = fabs(m_Plane[iPlane].a * Dir_v.x + m_Plane[iPlane].b * Dir_v.y + m_Plane[iPlane].c * Dir_v.z);
		Dir_v = box.axis[1] * box.extent[1];
		fDistance += fabs(m_Plane[iPlane].a * Dir_v.x + m_Plane[iPlane].b * Dir_v.y + m_Plane[iPlane].c * Dir_v.z);
		Dir_v = box.axis[2] * box.extent[2];
		fDistance += fabs(m_Plane[iPlane].a * Dir_v.x + m_Plane[iPlane].b * Dir_v.y + m_Plane[iPlane].c * Dir_v.z);

		PlaneToCenter = m_Plane[iPlane].a * box.v_center.x + m_Plane[iPlane].b * box.v_center.y +
			m_Plane[iPlane].c * box.v_center.z + m_Plane[iPlane].d;

		if (PlaneToCenter <= -(fDistance)) return P_BACK;

		/*if (PlaneToCenter < 0)
		{
			t_Position = P_BACK;
			if (fPlaneToCenter > -fDistance)
			{
				t_Position = P_SPANNING;
			}
			break;
		}*/
	}
	return P_FRONT;
}