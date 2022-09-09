#include "Object.h"


void Object3D::Frame(float delta_time) {}
void Object2D::Frame(float delta_time) {}

void Object3D::Set_default() {}
void Object2D::Set_default() {}

Object3D::~Object3D() {}
Object2D::~Object2D() {}

bool Object3D::Render() {
	std::cout << "object: " << box.v_min.x << " , " << box.v_min.y << " , " 
			  << box.v_min.z << " , " << box.v_size.x << " , " << box.v_size.y 
			  << " , " << box.v_size.z << std::endl;

	return true;
}
bool Object2D::Render() {
	std::cout << "object: " << rect.x << " , " << rect.y << " , " << rect.nx << " , " 
			  << rect.ny << std::endl;

	return true;
}

void Object3D::Set_sphere(Box box) {			// x, y 는 애초에 cx,cy 넘겨줌 (( rect 기반으로  -> circle 외접원 생성 ))
	sphere.v_center = box.v_center;
	sphere.r = ((box.v_size) / 2.0f).Get_length();	// size의 반이 반지름임
	
}

void Object3D::Set_sphere(Vector v_center, float r) {
	sphere.v_center = v_center;
	sphere.r = r;
}

void Object3D::Set_position(Vector v_pos, Vector v_size) {
	box.Set_box(v_pos, v_size);
	Set_sphere(box);
}

void Object3D::Add_force(Vector force) {
	this->force += force;
}



Object3D::Object3D()
{
	Vector v_min, v_size;
	v_min.x = 20 + (rand() % 80);
	v_min.y = 20 + (rand() % 80);
	v_min.z = 20 + (rand() % 80);
	v_size.x = 5.0f + (rand() % 5);
	v_size.y = 5.0f + (rand() % 5);
	v_size.z = 5.0f + (rand() % 5);

	box.Set_box(v_min, v_size);
	Set_sphere(box);
	direction.x = cos(rand());
	direction.y = sin(rand());
	direction.z = 1.0f - cos(rand());
	direction.Normalize_vector();
	mass = 100.0f;
	speed = 10.0f;
	friction = 0.0f;

}

bool Object3D::Init() {

	

	return true;
}



void Object2D::Set_circle(float x, float y, float w, float h) {
	float dx = (w / 2.0f);
	float dy = (h / 2.0f);

	circle.cx = x;
	circle.cy = y;
	circle.r = sqrt(dx * dx + dy * dy);
}

void Object2D::Set_position(float x, float y, float w, float h) {
	float x1 = (x / 100.0f) * 2 - 1.0f;
	float y1 = -((y / 100.0f) * 2 - 1.0f);
	float w1 = (w / 100.0f) * 2;
	float h1 = (h / 100.0f) * 2;

	m_VertexList[0].p = { x1, y1, 0.0f };
	m_VertexList[1].p = { x1 + w1, y1, 0.0f };
	m_VertexList[2].p = { x1, y1 - h1, 0.0f };
	m_VertexList[3].p = m_VertexList[2].p;
	m_VertexList[4].p = m_VertexList[1].p;
	m_VertexList[5].p = { x1 + w1, y1 - h1, 0.0f };

	rect.Set_rect(x, y, w, h);
	Set_circle(rect.cx, rect.cy, rect.w, rect.h);
}

void Object2D::Add_force(Vector2D force) {
	force2D += force;
}



Object2D::Object2D()
{
	rect.Set_rect(20+(rand() % 80),
		20+(rand() % 80),
		5.0f + (rand() % 5),
		5.0f + (rand() % 5));
	Set_circle(rect.cx, rect.cy, rect.w, rect.h);
	direction2D.x = cos(rand());
	direction2D.y = sin(rand());
	direction2D.Normalize_vector();
	mass = 100.0f;
	speed = 1.0f;
	friction = 10.0f;

}

bool Object2D::Init() {
	
	Set_position(rect.x, rect.y, rect.w, rect.h);

	return true;
}
