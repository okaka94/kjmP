#pragma once
#include "NPC_object.h"
#include "Map_object.h"
#include "Node.h"

enum SPACE_TYPE {
	QUAD_TREE, OCTREE
};

class Space_partition
{

public:
	Node* Root_node;			// 템플릿화 필요
public:
	virtual std::vector<Base_object*>  Get_collision_list(Base_object* obj);
	virtual void	 Create(Vector v_min, Vector v_size);
	virtual void	 Create(float w, float h);
	virtual void	 Add_static_obj(Base_object* obj);
	virtual void	 Add_dynamic_obj(Base_object* obj);
	virtual void	 Reset_dynamic_obj_list(Node* node);
	virtual void	 Set_default();
public:
	virtual Base_object*	New_static_obj();
	virtual Base_object*	New_dynamic_obj();

	virtual ~Space_partition();
};

