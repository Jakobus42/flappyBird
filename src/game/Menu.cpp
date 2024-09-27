#include "../../include/game/Menu.hpp"

namespace game {

Menu::Menu(float width, float height) {
    if (!_font.loadFromFile("font.ttf")) {  // TODO don't hardcode path
        throw std::runtime_error("Can't load font");
    }

    setupMenu(width, height);
    _option = Option::START;
    _menuItems[static_cast<std::size_t>(_option)].setFillColor(sf::Color::Red);
    _menuItems[static_cast<std::size_t>(_option)].setStyle(sf::Text::Bold);
}

Menu::~Menu() {}

void Menu::setupMenu(float width, float height) {
    std::vector<std::string> options = {"Start Game", "Options", "Exit"};
    float verticalOffset = 80.0f;
    float startingHeight = height / 2.0f - (options.size() * verticalOffset) / 2.0f;

    for (std::size_t i = 0; i < options.size(); i++) {
        sf::Text text;
        text.setFont(_font);
        text.setString(options[i]);
        text.setCharacterSize(60);
        text.setFillColor(sf::Color::White);
        text.setPosition(sf::Vector2f(
            width / 2.0f - text.getGlobalBounds().width / 2.0,
            startingHeight + i * verticalOffset)); 
        _menuItems.push_back(text);
    }
}

void Menu::draw(sf::RenderWindow &window) {
    for (const auto &item : _menuItems) {
        window.draw(item);
    }
}

void Menu::moveUp() {
    if (_option > Option::START) {
        _menuItems[static_cast<std::size_t>(_option)].setFillColor(sf::Color::White);
        _menuItems[static_cast<std::size_t>(_option)].setStyle(sf::Text::Regular);
        _option = static_cast<Option>(static_cast<int>(_option) - 1);
        _menuItems[static_cast<std::size_t>(_option)].setFillColor(sf::Color::Blue);
        _menuItems[static_cast<std::size_t>(_option)].setStyle(sf::Text::Bold);
    }
}

void Menu::moveDown() {
    if (_option < Option::EXIT) {
        _menuItems[static_cast<std::size_t>(_option)].setFillColor(sf::Color::White);
        _menuItems[static_cast<std::size_t>(_option)].setStyle(sf::Text::Regular);
        _option = static_cast<Option>(static_cast<int>(_option) + 1);
        _menuItems[static_cast<std::size_t>(_option)].setFillColor(sf::Color::Blue);
        _menuItems[static_cast<std::size_t>(_option)].setStyle(sf::Text::Bold);
    }
}

Menu::Option Menu::getSelectedOption() const {
    return _option;
}

}  // namespace game
