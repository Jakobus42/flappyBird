#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/entity/Bird.hpp"
#include "../include/game/GameManager.hpp"

int main()
{
  try
  {
    auto window = sf::RenderWindow{{SCREEN_WIDTH, SCREEN_HEIGHT}, "Flappy Bird"};
    entity::Bird bird(window.getSize().x / 4, window.getSize().y / 2);
    std::size_t currentFrame = 0;

    window.setFramerateLimit(60);

    sf::Texture bgTexture;
    sf::Texture floorTexture;
    if (!floorTexture.loadFromFile("assets/sprites/base_wide_only.png")) 
    {
      return EXIT_FAILURE;
    }
    if (!bgTexture.loadFromFile("assets/sprites/background-day-wide.png"))
      return EXIT_FAILURE;
    sf::Sprite background(bgTexture);
    sf::Sprite floor(floorTexture);
    floor.setPosition(0, window.getSize().y - floorTexture.getSize().y);

    while (window.isOpen())
    {
      for (auto event = sf::Event{}; window.pollEvent(event);)
      {
        if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) || event.type == sf::Event::Closed)
        {
          window.close();
        }
        if (event.key.code == sf::Keyboard::Space)
        {
          bird.jump(currentFrame);
        }
      }
      window.draw(background);
      window.draw(floor);
      bird.move(currentFrame);
      bird.draw(window, currentFrame);
      window.display();
      window.clear();
      currentFrame++;
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}