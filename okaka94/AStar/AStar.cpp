#include "AStar.h"

namespace AStar {

	MapGen::MapGen() {
		// �����¿�
		_direction8.push_back({ 0,-1 });
		_direction8.push_back({ 0,+1 });
		_direction8.push_back({ -1,0 });
		_direction8.push_back({ +1,0 });
		//�밢��
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

		std::list<Node*> OPENList, CLOSEDList;										// OPEN List , CLOSED List ����
		//std::vector<Index> currentList;											// �湮 ��� ����Ʈ
		Node* currentNode = nullptr;												// ���� ��ġ

		OPENList.push_back(new Node(start));
		while (!OPENList.empty()) {
			currentNode = *OPENList.begin(); 
			for (auto OPENNode : OPENList) {
				if (OPENNode->_F <= currentNode->_F) {
					currentNode = OPENNode;
				}
			}
			
			if (currentNode->_index == end) {										// ���� ��� == ������ (����)
				break;
			}
			//currentList.push_back(currentNode->_index);							// �湮������ �湮��� ����Ʈ�� �߰�
			CLOSEDList.push_back(currentNode);										// -> CLOSED List�� �߰�
			auto iter = std::find(OPENList.begin(), OPENList.end(), currentNode);
			OPENList.erase(iter);													// -> OPEN List���� ����

			for (unsigned int i = 0; i < 8; i++) {
				Index adjacentNode(currentNode->_index + _direction8[i]);			// ���� ��� (8����)

				if (DetectObstacle(adjacentNode)) {									// �̵��Ұ� ����� ���� ���� �Ѿ
					continue;
				}
				if (SearchNodeList(CLOSEDList, adjacentNode)) {						// �̹� �湮�� ����� ���� ���� �Ѿ
					continue;
				}
				unsigned int G = currentNode->_G + ((i < 4 ? 10 : 14));				// G = ���۳����� Ư�� ������ ���� ���

				Node* node = SearchNodeList(OPENList, adjacentNode);
				if (node == nullptr) {
					node = new Node(adjacentNode, currentNode);						// node(index , parent)
					node->_G = G;
					node->_H = GetDistance(node->_index, end);
					node->_F = node->_G + node->_H;
					OPENList.push_back(node);
				}
				else if (G < node->_G) {											// ���� ����� G������ ���� ��带 ��ģ ����� G ���� ���ٸ� ��� ����
					node->_parent = currentNode;
					node->_G = G;
				}
			}
		}
		std::list<Index> path;
		while (currentNode != nullptr) {											// �θ��� Ÿ�� �ö󰡸鼭 pathList ����
			path.push_front(currentNode->_index);
			currentNode = currentNode->_parent;
		}
		DeleteNodes(OPENList);
		DeleteNodes(CLOSEDList);
		
		return path;
	}

	bool MapGen::DetectObstacle(Index coord) {
		if (coord.x < 0 || coord.x >= _worldSize.x ||								// �� �ٱ���(world �� �迭)�� ������ ��
			coord.y < 0 || coord.y >= _worldSize.y) {
			return true;
		}
		
		if (std::find(_obstacles.begin(), _obstacles.end(), coord)					// ��ֹ��� �ε��� ��ġ�� ��ġ�ϸ� ������ ��
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