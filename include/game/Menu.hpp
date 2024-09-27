#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace game {

/**
 * @class Menu
 * @brief Handles the game menu.
 */
class Menu {
public:
   enum class Option { START = 0, OPTIONS, EXIT };

    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);

    void moveUp();
    void moveDown();

    Option getSelectedOption() const;

private:
    Option _option;
    sf::Font _font;
    std::vector<sf::Text> _menuItems;

    void setupMenu(float width, float height);
};

}  // namespace game
