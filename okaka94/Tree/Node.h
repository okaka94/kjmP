#pragma once
#include <vector>
#include "Object.h"
#include <windows.h>
#include <map>

class Node {
public:
	Rect rect;

	std::vector<Object*> Static_obj_list;
	std::vector<Object*> Dynamic_obj_list;
	Node* Child_node[4];
	Node* Parent_node;
	int   depth;

public:
	Node(Node* parent, float x, float y, float w, float h) {
		rect.Set_rect(x, y, w, h);
		depth = 0;

		if (parent != nullptr) {
			depth = parent->depth + 1;
			Parent_node = parent;
		}


		Child_node[0] = nullptr;
	}

	~Node() {
		delete Child_node[0];
		delete Child_node[1];
		delete Child_node[2];
		delete Child_node[3];
	}

};
