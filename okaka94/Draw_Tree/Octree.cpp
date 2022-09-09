#include "Octree.h"



//void	 Octree::Reset_dynamic_obj_list(Node* node) {
//	if (node == nullptr) return;
//	node->Dynamic_obj_list.clear();
//
//	for (int i = 0; i < node->Child_node.size(); i++) {
//		Reset_dynamic_obj_list(node->Child_node[i]);
//	}
//	
//}

Base_object* Octree::New_static_obj() {
	Base_object* obj = new Map_object3D;
	return obj;
}
Base_object* Octree::New_dynamic_obj() {
	Base_object* dynamic_obj = new NPC_object3D;
	return dynamic_obj;
}

void	Octree::Set_default() {
	Create(Vector(0, 0, 0), Vector(100, 100, 100));
}

void Octree::Create(Vector v_min, Vector v_size) {
	Root_node = Create_node(nullptr, v_min, v_size);
	Build_tree(Root_node);
}

Node* Octree::Create_node(Node* parent, Vector v_min, Vector v_size) {
	Node* new_node = new Node(parent, v_min, v_size);
	new_node->Child_node.resize(max_octree_child);

	return new_node;
}

void Octree::Build_tree(Node* node) {
	if (node->depth >= 3) return;
	if (node == nullptr) return;

	Vector pos, size;
	pos = node->box.v_min;
	size = node->box.v_size/2.0f;
	
	node->Child_node[0] = Create_node(node, pos, size);

	pos.x = node->box.v_min.x + size.x;
	node->Child_node[1] = Create_node(node, pos, size);

	pos.x = node->box.v_min.x;
	pos.y = node->box.v_min.y + size.y;
	node->Child_node[2] = Create_node(node, pos, size);

	pos.x = node->box.v_min.x + size.x;
	node->Child_node[3] = Create_node(node, pos, size);					// z�� ��ȭ���� 4���� ����

	pos.x = node->box.v_min.x;
	pos.y = node->box.v_min.y;
	pos.z = node->box.v_min.z + size.z;
	node->Child_node[4] = Create_node(node, pos, size);

	pos.x = node->box.v_min.x + size.x;
	node->Child_node[5] = Create_node(node, pos, size);

	pos.x = node->box.v_min.x;
	pos.y = node->box.v_min.y + size.y;
	node->Child_node[6] = Create_node(node, pos, size);

	pos.x = node->box.v_min.x + size.x;
	node->Child_node[7] = Create_node(node, pos, size);					// z�� ���� �� 4����


	for (int i = 0; i < node->Child_node.size(); i++) {
		Build_tree(node->Child_node[i]);
	}

}
void Octree::Add_static_obj(Base_object* obj) {

	Node* node = Find_node(Root_node, obj);

	if (node != nullptr) {
		node->Static_obj_list.push_back(obj);
	}

}

void Octree::Add_dynamic_obj(Base_object* obj) {

	Node* node = Find_node(Root_node, obj);

	if (node != nullptr) {
		node->Dynamic_obj_list.push_back(obj);
	}

}

Node* Octree::Find_node(Node* node, Base_object* obj) {
	std::queue<Node*> Q;

	do {
		for (int i = 0; i < 8; i++) {
			if (node->Child_node[i] != nullptr && Collision::Is_subset(node->Child_node[i]->box, obj->box)) {
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



std::vector<Base_object*> Octree::Get_collision_list(Base_object* obj) {
	std::vector<Base_object*> list;

	Get_collision_obj(this->Root_node, obj, list);

	return list;
}

void Octree::Get_collision_obj(Node* node, Base_object* obj, std::vector<Base_object*>& list) {

	if (node == nullptr) return;
	for (int i = 0; i < node->Static_obj_list.size(); i++) {								// ���� ������Ʈ �浹 Ȯ��

		if (Collision::Cmp_sphere(node->Static_obj_list[i]->sphere, obj->sphere)) {
			if (Collision::Cmp_box(node->Static_obj_list[i]->box, obj->box)) {
				list.push_back(node->Static_obj_list[i]);
			}
		}

	}
	for (int i = 0; i < node->Dynamic_obj_list.size(); i++) {								// ���� ������Ʈ �浹 Ȯ��

		if (Collision::Cmp_sphere(node->Dynamic_obj_list[i]->sphere, obj->sphere)) {
			if (Collision::Cmp_box(node->Dynamic_obj_list[i]->box, obj->box)) {
				list.push_back(node->Dynamic_obj_list[i]);
			}
		}

	}
	if (node->Child_node[0] != nullptr) {   // �� �ʿ�? ������ ��� ���� �������� ���� �ʳ�? -> �׼��� ���� ����
		for (int i = 0; i < 8; i++) {
			if (Collision::Cmp_box(node->Child_node[i]->box, obj->box)) {			// child_node�� ��� rect�� ���� ��? �������� �� obj ����Ʈ�� ��? -> ���ȿ� ������Ʈ(�÷��̾�)�� ���ٸ� Ȯ���� �ʿ䰡 �����ϱ�
				Get_collision_obj(node->Child_node[i], obj, list);
			}
		}
	}
}