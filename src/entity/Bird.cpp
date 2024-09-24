#include "../../include/entity/Bird.hpp"

namespace entity {

/**
 * @brief Constructs a new Bird object.
 */
Bird::Bird(std::size_t x, std::size_t y): 
AEntity() {
    std::vector<std::string> texturePaths = {
        "assets/sprites/yellowbird-upflap.png",
        "assets/sprites/yellowbird-midflap.png",
        "assets/sprites/yellowbird-downflap.png",
    };
    setTextures(texturePaths);
    _sprite.setScale(4, 4);
    _sprite.setPosition(x, y);
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

bool Bird::move() {
    _sprite.move(0, -100);
    return true;
}

void Bird::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    static uint16_t currentTexture = 0;

    if (currentTexture >= _textures.size()) {
        currentTexture = 0;
    }
    std::cout << currentTexture << std::endl;
    _sprite.setTexture(_textures[currentTexture]);
    window.draw(_sprite);
    if (currentFrame % 3 == 1){
        currentTexture++;
        return ;
    }
}

} /* namespace entity */
