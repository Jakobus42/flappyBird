#include <SFML/Graphics.hpp>
#include "../include/entity/Bird.hpp"
#include <iostream>

int main() {
  auto window = sf::RenderWindow{{1920u, 1080u}, "Flappy Bird"};
  sf::Texture bgTexture;
  entity::Bird bird(window.getSize().x / 2, window.getSize().y / 2);

  window.setFramerateLimit(60);
  if (!bgTexture.loadFromFile("assets/sprites/background-day-wide.png"))
      return EXIT_FAILURE;
  sf::Sprite background(bgTexture);

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) || event.type == sf::Event::Closed) {
          window.close();
      }
      if (event.key.code == sf::Keyboard::W) {
          bird.move();
      }
    }
    bird.draw(window);
    window.draw(background);
    window.display();
    window.clear();
  }
}