#include "../../include/entity/AEntity.hpp"

namespace entity {

/**
 * @brief Constructs a new AEntity object.
 */
AEntity::AEntity(const sf::Texture& texture, const sf::Sprite& sprite): 
_texture(texture),
_sprite(sprite) {}

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
        _texture = other._texture;
        _sprite = other._sprite;
    }
    return *this;
}

const sf::Texture& AEntity::getTexture() const {
    return _texture;
}

const sf::Sprite& AEntity::getSprite() const {
    return _sprite;
}

} /* namespace entity */
