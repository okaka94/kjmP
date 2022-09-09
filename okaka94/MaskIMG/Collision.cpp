#include "Collision.h"

Collision_type Collision::Cmp_rect(Rect& a, Rect& b) {
	float max_x;	float min_x;
	float max_y;	float min_y;
	
	max_x = a.nx < b.nx ? b.nx : a.nx;
	min_x = a.x > b.x ? b.x : a.x;
	max_y = a.ny < b.ny ? b.ny : a.ny;
	min_y = a.y > b.y ? b.y : a.y;


	if (a.w + b.w >= max_x - min_x) {

		if (a.h + b.h >= max_y - min_y) {
													// 교집합 구해서 완전포함 관계인지 아닌지 판별
			float  x;	float  y;
			float nx;	float ny;

			x = a.x < b.x ? b.x : a.x;
			y = a.y < b.y ? b.y : a.y;
			nx = a.nx > b.nx ? b.nx : a.nx;
			ny = a.ny > b.ny ? b.ny : a.ny;

			Rect intersection;
			intersection.Set_rect(x, y, nx - x, ny - y);
			if (intersection == a || intersection == b)
				return  Collision_type::RECT_IN;

			return Collision_type::RECT_OVERLAP;

		}
	}



	return Collision_type::RECT_OUT;
}

bool Collision::Is_subset(Rect& a, Rect& b) {

	if (a.x <= b.x) {
		if (a.nx >= b.nx) {
			if (a.y <= b.y) {
				if (a.ny >= b.ny) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Collision::Cmp_circle(Circle& a, Circle& b) {

	float x;	float y;	float sum_r;	float distance;
	x = a.cx - b.cx;
	y = a.cy - b.cy;
	sum_r = a.r + b.r;
	distance = sqrt(x * x + y * y);

	if (distance <= sum_r) {
		return true;
	}

	return false;

}

 ///////////////////////////////////////////////// box //////////////////////////

Collision_type Collision::Cmp_box(Box& a, Box& b) {
	float max_x;	float min_x;
	float max_y;	float min_y;
	float max_z;	float min_z;

	max_x = a.v_min.x < b.v_min.x ? b.v_min.x : a.v_min.x;
	min_x = a.v_min.x > b.v_min.x ? b.v_min.x : a.v_min.x;
	max_y = a.v_min.y < b.v_min.y ? b.v_min.y : a.v_min.y;
	min_y = a.v_min.y > b.v_min.y ? b.v_min.y : a.v_min.y;
	max_z = a.v_min.z < b.v_min.z ? b.v_min.z : a.v_min.z;
	min_z = a.v_min.z > b.v_min.z ? b.v_min.z : a.v_min.z;


	if (a.v_size.x + b.v_size.x >= max_x - min_x) {

		if (a.v_size.y + b.v_size.y >= max_y - min_y) {

			if (a.v_size.z + b.v_size.z >= max_z - min_z) {

				// 교집합 구해서 완전포함 관계인지 아닌지 판별
				float  x;	float  y;	float  z;
				float  nx;	float  ny;	float  nz;
				

				x = a.v_min.x < b.v_min.x ? b.v_min.x : a.v_min.x;
				y = a.v_min.y < b.v_min.y ? b.v_min.y : a.v_min.y;
				z = a.v_min.z < b.v_min.z ? b.v_min.z : a.v_min.z;
				Vector pos(x,y,z);

				nx = a.v_max.x > b.v_max.x ? b.v_max.x : a.v_max.x;
				ny = a.v_max.y > b.v_max.y ? b.v_max.y : a.v_max.y;
				nz = a.v_max.z > b.v_max.z ? b.v_max.z : a.v_max.z;
				Vector max; (nx, ny, nz);

				Box intersection;
				intersection.Set_box(pos,max-pos);
				if (intersection == a || intersection == b)
					return  Collision_type::RECT_IN;

				return Collision_type::RECT_OVERLAP;
			}
			
		}
	}



	return Collision_type::RECT_OUT;
}

bool Collision::Is_subset(Box& a, Box& b) {

	if (a.v_min <= b.v_min) {
		if(a.v_max >= b.v_max)
		return true;
	}

	return false;
}

bool Collision::Cmp_sphere(Sphere& a, Sphere& b) {

	float sum_r;	float distance;

	sum_r = a.r + b.r;
	distance = (a.v_center - b.v_center).Get_length();

	if (distance <= sum_r) {
		return true;
	}

	return false;

}