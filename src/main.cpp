
#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.hpp"
#include "./maps.hpp"
#include "player.hpp"



sf::RectangleShape wallGen(int x, int y) {
  sf::RectangleShape wall(sf::Vector2f(10, 10));
  wall.setOutlineColor(sf::Color(0, 0, 0));
  wall.setPosition(sf::Vector2f(x * 10, y * 10));
  wall.setOutlineThickness(1);
  return wall;
}
void drawMap(sf::RenderWindow *window) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      /// defino las caracteristicas de los sectores
      sf::RectangleShape wall = wallGen(x, y);
      sf::Color color;
      switch (map1[y][x]) {
        case 1:
          color = sf::Color::Red;
          break;
        case 2:
          color = sf::Color::Blue;
          break;
        case 3:
          color = sf::Color::White;
          break;
        case 4:
          color = sf::Color::Green;
          break;
        default:
          color = sf::Color::Yellow;
          break;
      }
      wall.setFillColor(color);

      window->draw(wall);
    }
  }
}
int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "jungle engine");
  Player player;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    player.Move();

    player.RayCast(&window, map1);
    drawMap(&window);
    player.Show(&window);

    window.display();

  }

  return 0;
}