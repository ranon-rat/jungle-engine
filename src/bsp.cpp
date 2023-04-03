#include <bsp.hpp>

BSP::BSP(player::Player& player, WadData wad) : player(player), wad(wad) {}


void BSP::render_node(int id) {
	std::cout<<"hello world";
	
}

void BSP::update() {}
