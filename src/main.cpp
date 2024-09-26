#include <SFML/Graphics.hpp>
#include <iostream>

#include "../include/game/Config.hpp"
#include "../include/game/GameManager.hpp"

int main() {
    try {
        game::GameManager game;
        game.init();
        if(game.run()) {
            return 0;
        }
        game.reset();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}