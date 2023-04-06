#include <vector>
#include <tuple>

#include "player.hpp"
#include "WADLoader.hpp"

class BSP
{
public:
    BSP(Player& player);

public:
    void render_node(int id);
    void update();

private:
    WADLoader loader;
    Player player;
};
