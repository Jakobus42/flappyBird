#include <SFML/Graphics.hpp>

int main() {
  auto window = sf::RenderWindow{{1920u, 1080u}, "Flappyird"};
  window.setFramerateLimit(144);
  sf::Texture texture;

  if (!texture.loadFromFile("assets/sprites/yellowbird-upflap.png"))
      return EXIT_FAILURE;
  sf::Sprite sprite(texture);
  sprite.setScale(4, 4);
  sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();
    window.draw(sprite);
    window.display();
  }
}
