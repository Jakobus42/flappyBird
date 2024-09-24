#include "../../include/entity/AEntity.hpp"

namespace entity {

/**
 * @brief Constructs a new AEntity object.
 */
AEntity::AEntity(){}

/**
 * @brief Destroys the AEntity object.
 */
AEntity::~AEntity() {}

/**
 * @brief Copy constructor.
 * @param other The other AEntity object to copy.
 */
AEntity::AEntity(const AEntity& other) {
    *this = other;
}

/**
 * @brief Copy assignment operator.
 * @param other The other AEntity object to assign from.
 * @return A reference to the assigned AEntity object.
 */
AEntity& AEntity::operator=(const AEntity& other) {
    if (this != &other) {
        _textures = other._textures;
        _sprite = other._sprite;
    }
    return *this;
}

const std::vector<sf::Texture>& AEntity::getTexture() const {
    return _textures;
}

const sf::Sprite& AEntity::getSprite() const {
    return _sprite;
}

void AEntity::setTextures(std::vector<std::string>& texturePaths) {
    for (auto it = texturePaths.begin(); it != texturePaths.end(); ++it) {
        sf::Texture texture;
        if(!texture.loadFromFile(*it)) {
            throw std::runtime_error("cant load " + *it);
        }
        _textures.push_back(texture);
    }
}

} /* namespace entity */
