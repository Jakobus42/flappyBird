#include <SFML/Graphics.hpp>

void moveBird(sf::Sprite& bird, sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::W: {
      bird.move(0, -100);
    }
    default: return ;
  }
}

int main() {
  auto window = sf::RenderWindow{{1920u, 1080u}, "Flappybird"};
  window.setFramerateLimit(144);
  sf::Texture texture;

  if (!texture.loadFromFile("assets/sprites/yellowbird-upflap.png"))
      return EXIT_FAILURE;
  sf::Sprite bird(texture);
  bird.setScale(4, 4);
  bird.setPosition(window.getSize().x / 2, window.getSize().y / 2);
  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) || event.type == sf::Event::Closed) {
          window.close();
      }
      moveBird(bird, event.key.code);
    }
    bird.move(0, 2);
    window.draw(bird);
    window.display();
    window.clear();
  }
}