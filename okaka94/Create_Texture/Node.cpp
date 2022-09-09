#include "Node.h"


Node::Node(Node* parent, Vector v_min, Vector v_size) {
	box.Set_box(v_min, v_size);
	depth = 0;

	if (parent != nullptr) {
		depth = parent->depth + 1;
		Parent_node = parent;
	}



}

Node::Node(Node* parent, float x, float y, float w, float h) {
	rect.Set_rect(x, y, w, h);
	depth = 0;

	if (parent != nullptr) {
		depth = parent->depth + 1;
		Parent_node = parent;
	}
}

Node::~Node() {
	for (int i = 0; i < Child_node.size(); i++) {
		if(Child_node[i]!=nullptr)
		delete Child_node[i];
	//	std::cout << "delete "<< i  << std::endl;
	}
		
	
}