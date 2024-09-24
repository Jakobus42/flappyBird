#include "../../include/entity/Bird.hpp"

namespace entity {

/**
 * @brief Constructs a new Bird object.
 */
Bird::Bird(std::size_t x, std::size_t y): 
AEntity(),
_currentTexture(0),
_velocity(0) {
    std::vector<std::string> texturePaths = {
        "assets/sprites/yellowbird-upflap.png",
        "assets/sprites/yellowbird-midflap.png",
        "assets/sprites/yellowbird-downflap.png",
    };
    setTextures(texturePaths);
    _sprite.setScale(4, 4);
    _sprite.setPosition(x, y - (_textures[_currentTexture].getSize().y * _sprite.getScale().y) / 2);
}

/**
 * @brief Destroys the Bird object.
 */
Bird::~Bird() {}

/**
 * @brief Copy constructor.
 * @param other The other Bird object to copy.
 */
Bird::Bird(const Bird& other): 
AEntity(other) {}

/**
 * @brief Copy assignment operator.
 * @param other The other Bird object to assign from.
 * @return A reference to the assigned Bird object.
 */
Bird& Bird::operator=(const Bird& other) {
    if (this != &other) {
        _textures = other._textures;
        _sprite = other._sprite;
    }
    return *this;
}

bool Bird::jump(std::size_t currentFrame) {
    _velocity = -13.5f;
    _sprite.move(0, _velocity);
    return true;
}

bool Bird::move(std::size_t) {
    _velocity += 0.65f;
    _sprite.move(0, _velocity);
    return true;
}

void Bird::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    _sprite.setTexture(_textures[_currentTexture]);
    window.draw(_sprite);
    if (currentFrame % 3 == 1){
        _currentTexture++;
        if (_currentTexture >= _textures.size()) {
            _currentTexture = 0;
        }
        return ;
    }
}

} /* namespace entity */
