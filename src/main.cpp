#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/entity/Bird.hpp"
#include "../include/game/GameManager.hpp"

int main() {
  try {
  auto window = sf::RenderWindow{{1920u, 1080u}, "Flappy Bird"};
  sf::Texture bgTexture;
  entity::Bird bird(window.getSize().x / 2, window.getSize().y / 2);
  std::size_t currentFrame = 0;

  window.setFramerateLimit(60);

  sf::Texture birdTexture;
  sf::Texture bgTexture;

  if (!birdTexture.loadFromFile("assets/sprites/yellowbird-upflap.png"))
      return EXIT_FAILURE;

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
    window.draw(background);
    bird.draw(window, currentFrame);
    window.display();
    window.clear();
    currentFrame++;
  } 
  } catch (std::exception& e) {
    std::cerr << "Error" << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}