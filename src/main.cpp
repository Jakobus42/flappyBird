#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/game/GameManager.hpp"
#include "../include/game/Config.hpp"

int main()
{
  try {
    // while (true) {
    //     game::GameManager game;
    //     if(game.menu()) {
    //       break ;
    //     }
    //     if(game.run()) {
    //       break ;
    //     }
    //     game.reset();  
    // }
    game::Config config;
      config.load("assets");
      auto birdTextures = config.getTextureCategory("bird");
      std::cout << "Textures for 'bird' category:" << std::endl;
      for (const auto& [subcategory, texturePaths] : birdTextures) {
          std::cout << "  Subcategory: " << subcategory << std::endl;
          for (const auto& texturePath : texturePaths) {
              std::cout << "    " << texturePath << std::endl;
          }
      }

      // Retrieve and print all sound effects for the "bird" category
      auto birdSounds = config.getSoundEffectCategory("bird");
      std::cout << "Sound effects for 'bird' category:" << std::endl;
      for (const auto& [subcategory, soundPaths] : birdSounds) {
          std::cout << "  Subcategory: " << subcategory << std::endl;
          for (const auto& soundPath : soundPaths) {
              std::cout << "    " << soundPath << std::endl;
          }
      }


      auto soundtracks = config.getSoundtrackPaths();
      std::cout << "Soundtracks:" << std::endl;
      for (const auto& soundtrack : soundtracks) {
          std::cout << "  " << soundtrack << std::endl;
      }

    
  }
   catch (std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return EXIT_FAILURE;
  }
}