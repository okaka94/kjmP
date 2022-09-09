#pragma once
#include "Object.h"
#include "Node.h"

class Quad_tree {

public:
	Node* Root_node;
public:
	std::vector<Object*>  Get_collision_list(Object* obj);

	void	 Create(float w, float h);
	Node*	 Create_node(Node* parent, float x, float y, float w, float h);
	void	 Build_tree(Node* node);
	void	 Add_static_obj(Object* obj);
	void	 Add_dynamic_obj(Object* obj);
	Node*	 Find_node(Node* node, Object* obj);

	void	 Get_collision_obj(Node* node, Object* obj, std::vector<Object*>& list);
	void	 Reset_dynamic_obj_list(Node* node);

	~Quad_tree() {
		delete Root_node;
	}
};



