#include "../../include/entity/Pipe.hpp"

namespace entity {

/**
 * @brief Constructs a new Pipe object.
 */
Pipe::Pipe(std::size_t id, bool isUpper, std::size_t velocity, const std::vector<std::string>& texturePaths):
AEntity(),
_id(id),
_isUpper(isUpper),
_y(isUpper ? getUpperPipeY() : getLowerPipeY()) {
    std::vector<std::string> texturePaths = {
        "assets/sprites/pipe-green.png"
    };
    setTextures(texturePaths);
    _sprite.setScale(3, 3);
    _sprite.setPosition(SCREEN_WIDTH + (_id * PIPE_SPACING), _y);
    if (isUpper) {
        _sprite.setRotation(180);  // Rotate the upper pipe
    }
}

/**
 * @brief Destroys the Pipe object.
 */
Pipe::~Pipe() {}

/**
 * @brief Copy constructor.
 * @param other The other Pipe object to copy.
 */
Pipe::Pipe(const Pipe& other): 
AEntity(other) {
    *this = other;
}

/**
 * @brief Copy assignment operator.
 * @param other The other Pipe object to assign from.
 * @return A reference to the assigned Pipe object.
 */
Pipe& Pipe::operator=(const Pipe& other) {
    if (this != &other) {
        _y = other._y;
        _id = other._id;
        _velocity = other._velocity;
        _currentTexture = other._currentTexture;
        _isUpper = other._isUpper;  // Copy isUpper value
    }
    return *this;
}

/**
 * @brief Get a random Y position for the lower pipe.
 * @return The Y position.
 */
int64_t Pipe::getLowerPipeY() {
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(SCREEN_HEIGHT - SCREEN_HEIGHT / 1.5, SCREEN_HEIGHT - SCREEN_HEIGHT / 4);
    return dist(gen);
}

/**
 * @brief Get Y position for the upper pipe based on the lower pipe.
 * @return The Y position for the upper pipe.
 */
int64_t Pipe::getUpperPipeY() {
    return getLowerPipeY() - PIPE_GAP - _sprite.getGlobalBounds().height;  // Adjust based on a gap
}

bool Pipe::move(std::size_t) {
    _sprite.move(_velocity, 0);
    
    if (_sprite.getPosition().x < -_sprite.getGlobalBounds().width) {
        // Reset position when the pipe moves out of view
        _y = _isUpper ? getUpperPipeY() : getLowerPipeY();
        _sprite.setPosition(SCREEN_WIDTH + PIPE_SPACING, _y);
    }
    return 0;
}

void Pipe::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    _sprite.setTexture(_textures[_currentTexture]);
    window.draw(_sprite);  // Draw only one pipe (either upper or lower)
}

bool Pipe::checkCollision(std::shared_ptr<entity::AEntity> other) const {
    return _sprite.getGlobalBounds().intersects(other->getSprite().getGlobalBounds());
}

} /* namespace entity */
