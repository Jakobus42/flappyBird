#include <SFML/Graphics.hpp>
#include <iostream>

void moveBird(sf::Sprite& bird, sf::Keyboard::Key key) {
  if (key == sf::Keyboard::W) {
      bird.move(0, -100);
  }
}

int main() {
  auto window = sf::RenderWindow{{1920u, 1080u}, "Flappy Bird"};
  window.setFramerateLimit(60);

  sf::Texture birdTexture;
  sf::Texture bgTexture;

  if (!birdTexture.loadFromFile("assets/sprites/yellowbird-upflap.png"))
      return EXIT_FAILURE;

  if (!bgTexture.loadFromFile("assets/sprites/background-day-wide.png"))
      return EXIT_FAILURE;

  sf::Sprite background(bgTexture);
  sf::Sprite bird(birdTexture);

  bird.setScale(4, 4);
  bird.setPosition((window.getSize().x / 2) - ((birdTexture.getSize().x * bird.getScale().x) / 2), (window.getSize().y / 2)  - ((birdTexture.getSize().y * bird.getScale().y) / 2));
  
  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) || event.type == sf::Event::Closed) {
          window.close();
      }
      moveBird(bird, event.key.code);
    }
    bird.move(0, 2);
    window.draw(background);
    window.draw(bird);
    window.display();
    window.clear();
  }
}