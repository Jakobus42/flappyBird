#include "../../include/entity/Pipe.hpp"

namespace entity {

/**
 * @brief Constructs a new Pipe object.
 */
Pipe::Pipe(std::size_t id, bool isUpper, std::size_t velocity, std::size_t spacing, std::size_t gap,
           const std::vector<std::string>& texturePaths)
    : AEntity(velocity, texturePaths),
      _id(id),
      _gap(gap),
      _isUpper(isUpper),
      _y(_isUpper ? getUpperPipeY() : getLowerPipeY()),
      _spacing(spacing) {
    _sprite.setScale(3, 3);
    _sprite.setPosition(SCREEN_WIDTH + (_id * _spacing), _y);
    if (_isUpper) {
        _sprite.setRotation(180);
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
Pipe::Pipe(const Pipe& other) : AEntity(other) { *this = other; }

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
        _isUpper = other._isUpper;
    }
    return *this;
}

/**
 * @brief Get a random Y position for the lower pipe.
 * @return The Y position.
 */
std::size_t Pipe::getLowerPipeY() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(SCREEN_HEIGHT - SCREEN_HEIGHT / 1.5,
                                         SCREEN_HEIGHT - SCREEN_HEIGHT / 4);
    return dist(gen);
}

/**
 * @brief Get Y position for the upper pipe based on the lower pipe.
 * @return The Y position for the upper pipe.
 */
std::size_t Pipe::getUpperPipeY() {
    return getLowerPipeY() - _gap - _sprite.getGlobalBounds().height;
}

bool Pipe::move(float maxXPosition) {
    _sprite.move(_velocity, 0);
    if (_sprite.getPosition().x < -_sprite.getGlobalBounds().width) {
        _y = _isUpper ? getUpperPipeY() : getLowerPipeY();
        _sprite.setPosition(maxXPosition + _sprite.getGlobalBounds().width,
                            _sprite.getPosition().y);
    }
    return false;
}

void Pipe::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    switchToNextTexture(3, currentFrame);
    window.draw(_sprite);
}

} /* namespace entity */
