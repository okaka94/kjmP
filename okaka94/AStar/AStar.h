#pragma once
#include <Windows.h>
#include <vector>
#include <list>
#include <set>
#include <iostream>

struct Index {
	int x, y;
	bool operator ==(const Index& i) {
		return (x == i.x && y == i.y);
	}
	Index operator + (const Index& i) {
		return { x + i.x, y + i.y };
	}
	Index() : x(0), y(0)
	{}
	Index(int fx, int fy) : x(fx) , y(fy)
	{}
};

namespace AStar {
	//using uint = unsigned int;
	//using pathlist = std::list<TIndex>;
	//using pathvector = std::vector<TIndex>;

	struct Node {
		unsigned int 
	};
}

