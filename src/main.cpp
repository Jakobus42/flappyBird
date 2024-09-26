#include <SFML/Graphics.hpp>
#include <iostream>

#include "../include/game/Config.hpp"
#include "../include/game/GameManager.hpp"

int main() {
    try {
        while(true) {
            game::GameManager game;
            game.init("config.json");
            if(game.run()) {
                return 0;
            }
            game.reset();
        }
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}