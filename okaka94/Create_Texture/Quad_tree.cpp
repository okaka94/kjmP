#include "Quad_tree.h"

std::queue<Node*> Q;

//void	 Quad_tree::Reset_dynamic_obj_list(Node* node) {
//	if (node == nullptr) return;
//	node->Dynamic_obj_list.clear();
//	Reset_dynamic_obj_list(node->Child_node[0]);
//	Reset_dynamic_obj_list(node->Child_node[1]);
//	Reset_dynamic_obj_list(node->Child_node[2]);
//	Reset_dynamic_obj_list(node->Child_node[3]);
//
//}
void	Quad_tree::Set_default() {
	Create(100.0f, 100.0f);
}

Base_object* Quad_tree::New_static_obj() {
	Base_object* obj = new Map_object2D;
	return obj;
}
Base_object* Quad_tree::New_dynamic_obj() {
	Base_object* obj = new NPC_object2D;
	return obj;
}



void Quad_tree::Create(float w, float h) {
	Root_node = Create_node(nullptr, 0, 0, w, h);
	Build_tree(Root_node);
}

Node* Quad_tree::Create_node(Node* parent, float x, float y, float w, float h) {
	Node* new_node = new Node(parent, x, y, w, h);
	new_node->Child_node.resize(max_quadtree_child);

	return new_node;
}

void Quad_tree::Build_tree(Node* node) {
	if (node->depth >= 3) return;
	if (node == nullptr) return;

	float x = node->rect.x;
	float y = node->rect.y;
	float w = (node->rect.w) / 2.0f;
	float h = (node->rect.h) / 2.0f;

	node->Child_node[0] = Create_node(node, x, y, w, h);
	node->Child_node[1] = Create_node(node, x + w, y, w, h);
	node->Child_node[2] = Create_node(node, x, y + h, w, h);
	node->Child_node[3] = Create_node(node, x + w, y + h, w, h);

	for (int i = 0; i < 4; i++) {
		Build_tree(node->Child_node[i]);
	}

}
void Quad_tree::Add_static_obj(Base_object* obj) {

	Node* node = Find_node(Root_node, obj);

	if (node != nullptr) {
		node->Static_obj_list.push_back(obj);
	}

}

void Quad_tree::Add_dynamic_obj(Base_object* obj) {

	Node* node = Find_node(Root_node, obj);

	if (node != nullptr) {
		node->Dynamic_obj_list.push_back(obj);
	}

}

Node* Quad_tree::Find_node(Node* node, Base_object* obj) {

	do {
		for (int i = 0; i < 4; i++) {
			if (node->Child_node[i] != nullptr && Collision::Is_subset(node->Child_node[i]->rect, obj->rect)) {
				Q.push(node->Child_node[i]);
				break;
			}

		}
		if (Q.empty())
			break;
		node = Q.front();
		Q.pop();

	} while (node);
	return node;
}



std::vector<Base_object*> Quad_tree::Get_collision_list(Base_object* obj) {
	std::vector<Base_object*> list;

	Get_collision_obj(this->Root_node, obj, list);

	return list;
}

void Quad_tree::Get_collision_obj(Node* node, Base_object* obj, std::vector<Base_object*>& list) {

	if (node == nullptr) return;
	for (int i = 0; i < node->Static_obj_list.size(); i++) {								// 정적 오브젝트 충돌 확인

		if (Collision::Cmp_circle(node->Static_obj_list[i]->circle, obj->circle)) {
			if (Collision::Cmp_rect(node->Static_obj_list[i]->rect, obj->rect)) {
				list.push_back(node->Static_obj_list[i]);
			}
		}

	}
	for (int i = 0; i < node->Dynamic_obj_list.size(); i++) {								// 동적 오브젝트 충돌 확인

		if (Collision::Cmp_circle(node->Dynamic_obj_list[i]->circle, obj->circle)) {
			if (Collision::Cmp_rect(node->Dynamic_obj_list[i]->rect, obj->rect)) {
				list.push_back(node->Dynamic_obj_list[i]);
			}
		}

	}
	if (node->Child_node[0] != nullptr) {   // 꼭 필요? 어차피 재귀 종료 조건으로 들어가지 않나? -> 액세스 에러 방지
		for (int i = 0; i < 4; i++) {
			if (Collision::Cmp_rect(node->Child_node[i]->rect, obj->rect)) {			// child_node의 멤버 rect로 직접 비교? 위에서는 왜 obj 리스트랑 비교? -> 노드안에 오브젝트(플레이어)가 없다면 확인할 필요가 없으니까
				Get_collision_obj(node->Child_node[i], obj, list);
			}
		}
	}
}