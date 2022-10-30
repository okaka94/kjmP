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
	// ���������� ������ ���ϵ��� ����
	// ���
	  // 1    2
	  // 0    3
	// �ϴ�
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
		// ��� NormV�� ������ �ٶ󺸰� ������ d���� ����� �� , d�� �������� �Ÿ�
		//if (fDistance == 0) return P_ONPLANE;		// ���� ������ ONPLANE ���� �ٷ� �����ϱ� �ָ��� 
		if (fDistance < 0) return P_BACK;		// distance > 0 �̸� ����� �տ� , <0�̸� ����� �� 
	}

	return P_FRONT;		// ��� ���� ���ʿ� �־���� , �� ��� ONPLANE ���� ���� ���⶧���� �Ѹ鿡 ���ϸ鼭 ���ο� �ִ� ��쵵 ���Ե�����
}


P_POSITION Frustum::Classify_sphere(Sphere s) {

	Vector center = s.v_center;

	for (int iPlane = 0; iPlane < 6; iPlane++)
	{
		float fDistance = m_Plane[iPlane].a * center.x + m_Plane[iPlane].b * center.y + m_Plane[iPlane].c * center.z + m_Plane[iPlane].d;
		// ��� NormV�� ������ �ٶ󺸰� ������ d���� ����� �� , d�� �������� �Ÿ�
		//if (fDistance == 0) return P_ONPLANE;		// ���� ������ ONPLANE ���� �ٷ� �����ϱ� �ָ��� 
		if (fDistance <= -(s.r)) return P_BACK;		// ������κ��� -r��ŭ�� �Ÿ����� �������� ���η� ������ �����뼱�� , ���� -r���� d���� �۴ٸ� ��� ����
	}

	return P_FRONT;		// ��� ���� ���ʿ� �־���� , �� ��� ONPLANE ���� ���� ���⶧���� �Ѹ鿡 ���ϸ鼭 ���ο� �ִ� ��쵵 ���Ե�����
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