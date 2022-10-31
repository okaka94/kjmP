#pragma once
#include "Shape.h"
#include "TMath.h"

enum P_POSITION {
	P_BACK = 0,
	P_FRONT,
	P_ONPLANE,
	P_SPANNING,
};

struct Plane {
	float a, b, c, d;
	void Create(Vector v0, Vector v1, Vector v2)	{
		
		Vector E0 = v1 - v0;
		Vector E1 = v2 - v0;
		Vector normal = E0 ^ E1;
		normal.Normalize_vector();
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -(normal | v0);

	}
	void Create(Vector normal, Vector v0) {

		normal.Normalize_vector();
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -(normal | v0);

	}
};


class Frustum
{

	//Matrix		m_View_matrix;
	//Matrix		m_Proj_matrix;
public:
	TBASIS_EX::TVector3  m_Vertex[8];
	Plane		m_Plane[6];
	Shape_box*	Frustum_box=nullptr;
public:
	void	Create_frustum(Matrix* V_mat, Matrix* P_mat);
	void	Create_frustum_box(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	//void	Render_frustum_box(Matrix* V_mat, Matrix* P_mat);
	bool	Render(Matrix* V_mat, Matrix* P_mat);
	P_POSITION Classify_point(Vector v);
	P_POSITION Classify_sphere(Sphere s);
	P_POSITION Classify_AABB(AABB box);	// 비어있음
	P_POSITION Classify_OBB(OBB box);

};