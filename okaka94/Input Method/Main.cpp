#include "Game_core.h"


int main() {
	Game_core game;

	game.Get_instance(OCTREE);				// QUAD_TREE, OCTREE ����
	game.Run();
	std::cout << "End" << std::endl;
	return 0;
}