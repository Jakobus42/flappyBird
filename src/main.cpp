#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/game/GameManager.hpp"

int main()
{
  try {
    while (true) {
        game::GameManager game;
        if(game.menu()) {
          break ;
        }
        if(game.run()) {
          break ;
        }
        game.reset();  
    }
  }
   catch (std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return EXIT_FAILURE;
  }
}