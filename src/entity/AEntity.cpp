#include "../../include/entity/AEntity.hpp"
#include <stdexcept>

namespace entity {

/**
 * @brief Constructs a new AEntity object with the given velocity and textures.
 */
AEntity::AEntity(float velocity, const std::vector<std::string>& texturePaths)
    : _velocity(velocity), _currentTexture(0) {
    // Load the textures using the provided file paths
    setTextures(texturePaths);

    // Set the initial texture for the sprite if available
    if (!_textures.empty()) {
        _sprite.setTexture(_textures[_currentTexture]);
    }
}

/**
 * @brief Destroys the AEntity object.
 */
AEntity::~AEntity() {}

/**
 * @brief Copy constructor.
 */
AEntity::AEntity(const AEntity& other) {
    *this = other;
}

/**
 * @brief Copy assignment operator.
 */
AEntity& AEntity::operator=(const AEntity& other) {
    if (this != &other) {
        _textures = other._textures;
        _sprite = other._sprite;
        _velocity = other._velocity;
        _currentTexture = other._currentTexture;
    }
    return *this;
}

/**
 * @brief Gets the textures used by the entity.
 */
const std::vector<sf::Texture>& AEntity::getTexture() const {
    return _textures;
}

/**
 * @brief Gets the sprite of the entity.
 */
const sf::Sprite& AEntity::getSprite() const {
    return _sprite;
}

/**
 * @brief Sets the textures for the entity by loading them from file paths.
 */
void AEntity::setTextures(const std::vector<std::string>& texturePaths) {
    for (const auto& texturePath : texturePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
        _textures.push_back(texture);
    }

    // Set the initial texture after loading
    if (!_textures.empty()) {
        _currentTexture = 0;  // Start with the first texture
        _sprite.setTexture(_textures[_currentTexture]);
    }
}

/**
 * @brief Switches to the next texture in the texture list for animation purposes.
 */
void AEntity::switchToNextTexture(std::size_t frameDelay, std::size_t currentFrame) {
    if (!_textures.empty()) {
        if (currentFrame % frameDelay == 0) {
            _currentTexture = (_currentTexture + 1) % _textures.size();
            _sprite.setTexture(_textures[_currentTexture]);
        }
    }
}

/**
 * @brief Checks for a collision with another entity.
 */
bool AEntity::checkCollision(std::shared_ptr<entity::AEntity> other) const {
    return _sprite.getGlobalBounds().intersects(other->_sprite.getGlobalBounds());
}

} /* namespace entity */
