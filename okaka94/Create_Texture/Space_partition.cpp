#include "Space_partition.h"

void					Space_partition::Create(Vector v_min, Vector v_size) {}
void					Space_partition::Create(float w, float h) {}
void					Space_partition::Add_static_obj(Base_object* obj) {}
void					Space_partition::Add_dynamic_obj(Base_object* obj) {}
void					Space_partition::Set_default() {}
Base_object*			Space_partition::New_static_obj() { return nullptr; }
Base_object*			Space_partition::New_dynamic_obj() { return nullptr; }

void					Space_partition::Reset_dynamic_obj_list(Node* node) {
	if (node == nullptr) return;
	node->Dynamic_obj_list.clear();

	for (int i = 0; i < node->Child_node.size(); i++) {
		Reset_dynamic_obj_list(node->Child_node[i]);
	}
}

std::vector<Base_object*>  Space_partition::Get_collision_list(Base_object* obj) {
	std::vector<Base_object*> list; 
	return list; 
}

Space_partition::~Space_partition() {

}