#include "../../include/entity/Pipe.hpp"

namespace entity {

/**
 * @brief Constructs a new Pipe object.
 */


Pipe::Pipe(std::size_t id):
AEntity(),
_velocity(-10.0f),
_id(id),
_y(getRandomY()) {
    std::vector<std::string> texturePaths = {
        "/Users/jakobsadjina/timo/flappyBird/assets/sprites/pipe-green.png"
    };
    setTextures(texturePaths);
    _sprite.setScale(3, 3);
    _sprite.setPosition(SCREEN_WIDTH + (_id * PIPE_SPACING), _y);
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
    }
    return *this;
}

int64_t Pipe::getRandomY() {
    std::random_device rd; 
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(SCREEN_HEIGHT - SCREEN_HEIGHT / 1.5, SCREEN_HEIGHT - SCREEN_HEIGHT / 4);
    return dist(gen);
}

bool Pipe::move(std::size_t) {
    _y = getRandomY();
    _sprite.move(_velocity, 0);
    
    if (_sprite.getPosition().x < -_sprite.getGlobalBounds().width) {
        _sprite.setPosition(SCREEN_WIDTH + PIPE_SPACING, _y);
    } 
    return 0;
}

void Pipe::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    Pipe tmp(*this);
    _sprite.setTexture(_textures[_currentTexture]);
    tmp._sprite.setTexture(tmp._textures[_currentTexture]);
    tmp._sprite.setRotation(180);
    tmp._sprite.move(tmp._sprite.getGlobalBounds().width , -350);

    // tmp._sprite.setPosition(SCREEN_WIDTH + PIPE_SPACING, _y - (_sprite.getGlobalBounds().height - 200));
    window.draw(_sprite);
    window.draw(tmp._sprite);
}

} /* namespace entity */
