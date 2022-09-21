#include "Object.h"


//bool Object3D::Frame() { return true; }
bool Object2D::Frame() { return true; }

//void Object3D::Set_default() {}

//Object3D::~Object3D() {}
Object2D::~Object2D() { }

//bool Object3D::Render() {
//	std::cout << "object: " << box.v_min.x << " , " << box.v_min.y << " , " 
//			  << box.v_min.z << " , " << box.v_size.x << " , " << box.v_size.y 
//			  << " , " << box.v_size.z << std::endl;
//
//	return true;
//}
//bool Object2D::Render() {
//	std::cout << "object: " << rect.x << " , " << rect.y << " , " << rect.nx << " , " 
//			  << rect.ny << std::endl;
//
//	return true;
//}
//
//void Object3D::Set_sphere(Box box) {			// x, y 는 애초에 cx,cy 넘겨줌 (( rect 기반으로  -> circle 외접원 생성 ))
//	sphere.v_center = box.v_center;
//	sphere.r = ((box.v_size) / 2.0f).Get_length();	// size의 반이 반지름임
//	
//}
//
//void Object3D::Set_sphere(Vector v_center, float r) {
//	sphere.v_center = v_center;
//	sphere.r = r;
//}
//
//void Object3D::Set_position(Vector v_pos, Vector v_size) {
//	box.Set_box(v_pos, v_size);
//	Set_sphere(box);
//}
//
//void Object3D::Add_force(Vector force) {
//	this->force += force;
//}



//Object3D::Object3D()
//{
//	Vector v_min, v_size;
//	v_min.x = 20 + (rand() % 80);
//	v_min.y = 20 + (rand() % 80);
//	v_min.z = 20 + (rand() % 80);
//	v_size.x = 5.0f + (rand() % 5);
//	v_size.y = 5.0f + (rand() % 5);
//	v_size.z = 5.0f + (rand() % 5);
//
//	box.Set_box(v_min, v_size);
//	Set_sphere(box);
//	direction.x = cos(rand());
//	direction.y = sin(rand());
//	direction.z = 1.0f - cos(rand());
//	direction.Normalize_vector();
//	mass = 100.0f;
//	speed = 10.0f;
//	friction = 0.0f;
//
//}
//
//bool Object3D::Init() {
//
//	
//
//	return true;
//}
//

void Object2D::UpdateVertextBuffer() {

	float x1 = m_vDrawPos.x;
	float y1 = m_vDrawPos.y;
	float w1 = m_vDrawSize.x;
	float h1 = m_vDrawSize.y;

	m_VertexList[0].p = { x1, y1, 0.0f };
	m_VertexList[0].t = {m_rtUV.x,  m_rtUV.y };

	m_VertexList[1].p = { x1 + w1, y1, 0.0f };
	m_VertexList[1].t = { m_rtUV.x+m_rtUV.w,  m_rtUV.y };

	m_VertexList[2].p = { x1, y1 - h1, 0.0f };
	m_VertexList[2].t = { m_rtUV.x,  m_rtUV.y+m_rtUV.h };

	m_VertexList[3].p = { x1 + w1, y1 - h1, 0.0f };
	m_VertexList[3].t = { m_rtUV.x + m_rtUV.w ,m_rtUV.y + m_rtUV.h };

	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);

}

void Object2D::Set_rect(Rect rt) {						// t값 설정
	
	m_rtInit = rt;
	m_ptImgSize.x = m_pTexture->m_Desc.Width;
	m_ptImgSize.y = m_pTexture->m_Desc.Height;

	m_rtUV.x = rt.x / m_ptImgSize.x;
	m_rtUV.y = rt.y / m_ptImgSize.y;
	m_rtUV.w = rt.w / m_ptImgSize.x;
	m_rtUV.h = rt.h / m_ptImgSize.y;
}

void Object2D::Set_rect(float x, float y, float w, float h) {						// t값 설정

	m_rtInit = { x,y,w,h };
	m_ptImgSize.x = m_pTexture->m_Desc.Width;
	m_ptImgSize.y = m_pTexture->m_Desc.Height;

	m_rtUV.x = x / m_ptImgSize.x;
	m_rtUV.y = y / m_ptImgSize.y;
	m_rtUV.w = w / m_ptImgSize.x;
	m_rtUV.h = h / m_ptImgSize.y;
}


void Object2D::Set_position(Vector2D pos) {				// p값 설정  -- Set_pos 분리하기
	
	m_vPos = pos;
	
	ScreenToNDC();			// 화면 좌표계 -> NDC 좌표계

	UpdateVertextBuffer();
}

void Object2D::ScreenToNDC() {

	m_vDrawPos.x = (m_vPos.x / g_rtClient.right) * 2.0f - 1.0f;
	m_vDrawPos.y = -((m_vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
	m_vDrawSize.x = (m_rtInit.w / g_rtClient.right) * 2;
	m_vDrawSize.y = (m_rtInit.h / g_rtClient.bottom) * 2;

}

void Object2D::Set_position(Vector2D pos, Vector2D cam_pos) {				// p값 설정  -- Set_pos 분리하기

	m_vPos = pos;

	ScreenToCam(cam_pos,m_vViewSize);			// 월드 좌표 -> 뷰 좌표 -> NDC 좌표

	UpdateVertextBuffer();
}

void Object2D::ScreenToCam(Vector2D cam_pos, Vector2D view_size) {

	Vector2D View_pos = m_vPos;			// 오브젝트 pos (월드 좌표) 기준으로 변환

	View_pos.x = View_pos.x - cam_pos.x;
	View_pos.y = View_pos.y - cam_pos.y;

	m_vDrawPos.x = (View_pos.x / view_size.x) * 2.0f ;			// View pos 기준으로 NDC로 변환
	m_vDrawPos.y = -((View_pos.y / view_size.y) * 2.0f);		// 클라이언트 크기에 맞춰 -1~1 정규화하지 않음
	m_vDrawSize.x = (m_rtInit.w / view_size.x) * 2;
	m_vDrawSize.y = (m_rtInit.h / view_size.y) * 2;				

}
