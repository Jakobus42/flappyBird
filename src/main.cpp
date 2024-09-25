#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/game/GameManager.hpp"

int main()
{
  try {
    game::GameManager game;
    game.start();
  } catch (std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return EXIT_FAILURE;
  }
}