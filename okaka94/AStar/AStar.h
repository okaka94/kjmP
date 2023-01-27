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
	//using nodeset = std::set<Node*>;

	struct Node {
		unsigned int _F, _G, _H;								// F : fitness , G : goal , H : heuristics
		Index _index;
		Node* _parent;
		void MakeF(){
			_F = _G + _H;
		}
		Node(Index i, Node* parent = nullptr) {
			_index = i;
			_parent = parent;
			_F = _G = _H = 0;
		}
	};

	class MapGen {
	private:
		Index				_worldSize;
		unsigned int		_direction;
		std::vector<Index>	_direction8;
		std::vector<Index>	_obstacles;
	public:
		void			 SetWorldSize(Index ws);
		void			 AddObstacle(Index i);
		std::list<Index> FindPath(Index start, Index end);
		bool			 DetectObstacle(Index coord);
		//Node*			 FindNodeList(std::set<Node*>& list, Index newI);
		Node*			 SearchNodeList(std::list<Node*>& list, Index newI);
		unsigned int	 GetDistance(Index from, Index to);
		//void			 DeleteNodes(std::set<Node*> nodes);
		void			 DeleteNodes(std::list<Node*> nodes);
		MapGen();
	};
}

