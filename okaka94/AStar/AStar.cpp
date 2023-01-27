#include "AStar.h"

namespace AStar {

	MapGen::MapGen() {
		// 상하좌우
		_direction8.push_back({ 0,-1 });
		_direction8.push_back({ 0,+1 });
		_direction8.push_back({ -1,0 });
		_direction8.push_back({ +1,0 });
		//대각선
		_direction8.push_back({ -1,-1 });
		_direction8.push_back({ +1,-1 });
		_direction8.push_back({ -1,+1 });
		_direction8.push_back({ +1,+1 });
	}
	void MapGen::SetWorldSize(Index ws) {
		_worldSize = ws;
	}

	void MapGen::AddObstacle(Index i) {
		_obstacles.push_back(i);
	}

	std::list<Index> MapGen::FindPath(Index start, Index end) {

		std::list<Node*> OPENList, CLOSEDList;										// OPEN List , CLOSED List 구성
		//std::vector<Index> currentList;											// 방문 노드 리스트
		Node* currentNode = nullptr;												// 현재 위치

		OPENList.push_back(new Node(start));
		while (!OPENList.empty()) {
			currentNode = *OPENList.begin(); 
			for (auto OPENNode : OPENList) {
				if (OPENNode->_F <= currentNode->_F) {
					currentNode = OPENNode;
				}
			}
			
			if (currentNode->_index == end) {										// 현재 노드 == 목적지 (도착)
				break;
			}
			//currentList.push_back(currentNode->_index);							// 방문했으면 방문노드 리스트에 추가
			CLOSEDList.push_back(currentNode);										// -> CLOSED List에 추가
			auto iter = std::find(OPENList.begin(), OPENList.end(), currentNode);
			OPENList.erase(iter);													// -> OPEN List에서 제외

			for (unsigned int i = 0; i < 8; i++) {
				Index adjacentNode(currentNode->_index + _direction8[i]);			// 인접 노드 (8방향)

				if (DetectObstacle(adjacentNode)) {									// 이동불가 노드라면 다음 노드로 넘어감
					continue;
				}
				if (SearchNodeList(CLOSEDList, adjacentNode)) {						// 이미 방문한 노드라면 다음 노드로 넘어감
					continue;
				}
				unsigned int G = currentNode->_G + ((i < 4 ? 10 : 14));				// G = 시작노드부터 특정 노드까지 오는 비용

				Node* node = SearchNodeList(OPENList, adjacentNode);
				if (node == nullptr) {
					node = new Node(adjacentNode, currentNode);						// node(index , parent)
					node->_G = G;
					node->_H = GetDistance(node->_index, end);
					node->_F = node->_G + node->_H;
					OPENList.push_back(node);
				}
				else if (G < node->_G) {											// 인접 노드의 G값보다 현재 노드를 거친 경로의 G 값이 적다면 경로 수정
					node->_parent = currentNode;
					node->_G = G;
				}
			}
		}
		std::list<Index> path;
		while (currentNode != nullptr) {											// 부모노드 타고 올라가면서 pathList 구성
			path.push_front(currentNode->_index);
			currentNode = currentNode->_parent;
		}
		DeleteNodes(OPENList);
		DeleteNodes(CLOSEDList);
		
		return path;
	}

	bool MapGen::DetectObstacle(Index coord) {
		if (coord.x < 0 || coord.x >= _worldSize.x ||								// 맵 바깥쪽(world 밖 배열)도 못가는 곳
			coord.y < 0 || coord.y >= _worldSize.y) {
			return true;
		}
		
		if (std::find(_obstacles.begin(), _obstacles.end(), coord)					// 장애물과 인덱스 위치가 일치하면 못가는 곳
			!= _obstacles.end()) {
			return true;
		}

		return false;
	}

	Node* MapGen::SearchNodeList(std::list<Node*>& list, Index i) {
		for (auto node : list) {
			if (node->_index == i) {
				return node;
			}
		}
		return nullptr;
	}

	unsigned int MapGen::GetDistance(Index from, Index to) {
		/////////////////////////////////////////////
	}


}