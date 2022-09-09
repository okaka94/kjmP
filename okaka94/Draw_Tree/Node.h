#pragma once
#include <vector>
#include "Object.h"
#include <windows.h>
#include <map>

class Node {
public:
	Box box;
	Rect rect;
	int   depth;

	std::vector<Base_object*> Static_obj_list;
	std::vector<Base_object*> Dynamic_obj_list;
	std::vector<Node*> Child_node;
	Node* Parent_node;
	

public:
	Node(Node* parent, Vector v_min, Vector v_size);
	Node(Node* parent, float x, float y, float w, float h);
	~Node();
};
