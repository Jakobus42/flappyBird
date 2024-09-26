#include "../../include/entity/PipePair.hpp"
#include <random>

namespace entity {

/**
 * @brief Constructs a new PipePair object.
 */
PipePair::PipePair(float velocity, std::size_t spacing, std::size_t gap, const std::vector<std::string>& texturePaths)
    : AEntity(velocity, texturePaths),
      _gap(gap),
      _randomY(getRandomY()) {
    _lowerPipe.setTexture(_textures[_currentTexture]);
    _upperPipe.setTexture(_textures[_currentTexture]);

    _lowerPipe.setScale(3, 3);
    _upperPipe.setScale(3, 3);
    _upperPipe.setRotation(180);
    _lowerPipe.setPosition(SCREEN_WIDTH, _randomY); //TODO dont hardcode
    _upperPipe.setPosition(SCREEN_WIDTH, getUpperPipeY());
}

/**
 * @brief Destroys the PipePair object.
 */
PipePair::~PipePair() {}

/**
 * @brief Copy constructor.
 * @param other The other PipePair object to copy.
 */
PipePair::PipePair(const PipePair& other) : AEntity(other) {
    *this = other;
}

/**
 * @brief Copy assignment operator.
 * @param other The other PipePair object to assign from.
 * @return A reference to the assigned PipePair object.
 */
PipePair& PipePair::operator=(const PipePair& other) {
    if (this != &other) {
        _velocity = other._velocity;
        _currentTexture = other._currentTexture;
        _gap = other._gap;
        _lowerPipe = other._lowerPipe;
        _upperPipe = other._upperPipe;
    }
    return *this;
}

/**
 * @brief Get a random Y position for the lower pipe.
 * @return The Y position.
 */
std::size_t PipePair::geRandomY() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(SCREEN_HEIGHT - SCREEN_HEIGHT / 1.5, SCREEN_HEIGHT - SCREEN_HEIGHT / 4);
    return dist(gen);
}

/**
 * @brief Get Y position for the upper pipe based on the lower pipe.
 * @return The Y position for the upper pipe.
 */
std::size_t PipePair::getUpperPipeY() {
    return _randomY - _gap - _lowerPipe.getGlobalBounds().height;
}

/**
 * @brief Move the pipes to the left.
 * @return true if the pipes are out of the screen, false otherwise.
 */
bool PipePair::move() {
    _lowerPipe.move(-_velocity, 0);
    _upperPipe.move(-_velocity, 0);
    if (_lowerPipe.getPosition().x + _lowerPipe.getGlobalBounds().width < 0) {
        return true;
    }
    return false;
}

/**
 * @brief Draw both pipes on the window.
 * @param window The SFML window where the pipes should be drawn.
 * @param currentFrame The current frame for texture switching.
 */
void PipePair::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    window.draw(_lowerPipe);
    window.draw(_upperPipe);
}

}  // namespace entity
