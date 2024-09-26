#include "../../include/entity/PipePair.hpp"

namespace entity {

/**
 * @brief Constructs a new PipePair object.
 */
PipePair::PipePair() {

}

/**
 * @brief Destroys the PipePair object.
 */
PipePair::~PipePair() {

}

/**
 * @brief Copy constructor.
 * @param other The other PipePair object to copy.
 */
PipePair::PipePair(const PipePair &) {

}

/**
 * @brief Copy assignment operator.
 * @param other The other PipePair object to assign from.
 * @return A reference to the assigned PipePair object.
 */
PipePair& PipePair::operator=(const PipePair &) {
    return *this;
}

/**
 * @brief Constructs a new PipePair object.
 * @param id Identifier for the pipe pair.
 * @param velocity Speed at which pipes move.
 * @param spacing Distance between consecutive pipe pairs.
 * @param gap Gap between the upper and lower pipes.
 * @param texturePaths Paths to textures for the pipes.
 */
PipePair::PipePair(std::size_t id, std::size_t velocity, std::size_t spacing, std::size_t gap,
                   const std::vector<std::string>& texturePaths)
    : _id(id), _velocity(velocity), _spacing(spacing), _gap(gap) {
    
    _lowerPipe = std::make_shared<Pipe>(id, false, velocity, spacing, gap, texturePaths);
    
    _upperPipe = std::make_shared<Pipe>(id, true, velocity, spacing, gap, texturePaths);

    float xPosition = SCREEN_WIDTH + (_id * _spacing);
    _lowerPipe->setPosition(xPosition, _lowerPipe->getLowerPipeY());
    _upperPipe->setPosition(xPosition, _upperPipe->getUpperPipeY());
}

/**
 * @brief Move the pipe pair.
 * Moves both the upper and lower pipes together.
 */
bool PipePair::move() {
    _lowerPipe->move();
    _upperPipe->move();

    if (_lowerPipe->getSprite().getPosition().x < -_lowerPipe->getSprite().getGlobalBounds().width) {
        float newXPosition = SCREEN_WIDTH + _spacing;
        _lowerPipe->setPosition(newXPosition, _lowerPipe->getLowerPipeY());
        _upperPipe->setPosition(newXPosition, _upperPipe->getUpperPipeY());
    }

    return false;
}

/**
 * @brief Draw the pipe pair.
 * Draws both the upper and lower pipes to the screen.
 * @param window The render window.
 * @param currentFrame The current frame number.
 */
void PipePair::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    _lowerPipe->draw(window, currentFrame);
    _upperPipe->draw(window, currentFrame);
}

} /* namespace entity */

