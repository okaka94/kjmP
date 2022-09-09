#pragma once
#include "Space_partition.h"

static const int max_octree_child = 8;

class Octree : public Space_partition
{
public:
	//Node2D* Root_node;
public:
	std::vector<Base_object*>  Get_collision_list(Base_object* obj);
	void	 Create(Vector v_min, Vector v_size);
	Node* Create_node(Node* parent, Vector v_min, Vector v_size);
	void	 Build_tree(Node* node);
	void	 Add_static_obj(Base_object* obj);
	void	 Add_dynamic_obj(Base_object* obj);
	Node* Find_node(Node* node, Base_object* obj);
	void	 Get_collision_obj(Node* node, Base_object* obj, std::vector<Base_object*>& list);
	//void	 Reset_dynamic_obj_list(Node* node);

	void	Set_default() override;
	Base_object* New_static_obj() override;
	Base_object* New_dynamic_obj() override;

	~Octree() {
		delete Root_node;
	}

};

