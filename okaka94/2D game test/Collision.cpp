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

