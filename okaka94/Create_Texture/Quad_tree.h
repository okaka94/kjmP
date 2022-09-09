#pragma once
#include "Space_partition.h"

static const int max_quadtree_child = 4;

class Quad_tree : public Space_partition{

public:
	//Node2D* Root_node;
public:
	std::vector<Base_object*>  Get_collision_list(Base_object* obj);

	void	 Create(float w, float h);
	Node*	 Create_node(Node* parent, float x, float y, float w, float h);
	void	 Build_tree(Node* node);
	void	 Add_static_obj(Base_object* obj);
	void	 Add_dynamic_obj(Base_object* obj);
	Node*	 Find_node(Node* node, Base_object* obj);

	void	 Get_collision_obj(Node* node, Base_object* obj, std::vector<Base_object*>& list);
	//void	 Reset_dynamic_obj_list(Node* node);
	void	Set_default() override;

	Base_object* New_static_obj() override;
	Base_object* New_dynamic_obj() override;

	~Quad_tree() {
		delete Root_node;
	}
};



