#include "../../include/entity/Pipe.hpp"

namespace entity {

/**
 * @brief Constructs a new Pipe object.
 */
Pipe::Pipe(std::size_t id):
AEntity(),
_velocity(-10.0f),
_id(id) {
    std::vector<std::string> texturePaths = {
        "/Users/jakobsadjina/timo/flappyBird/assets/sprites/pipe-green.png"
    };
    //TODO set random y
    setTextures(texturePaths);
    _sprite.setScale(3, 3);
    _sprite.setPosition(SCREEN_WIDTH + 800 * _id, std::rand() % (SCREEN_HEIGHT / 2));
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
AEntity(other) {}

/**
 * @brief Copy assignment operator.
 * @param other The other Pipe object to assign from.
 * @return A reference to the assigned Pipe object.
 */
Pipe& Pipe::operator=(const Pipe& other) {
    if (this != &other) {
        _textures = other._textures;
        _sprite = other._sprite;
    }
    return *this;
}

bool Pipe::move(std::size_t) {
    _sprite.move(_velocity, 0);
    if (_sprite.getPosition().x < -_sprite.getTexture()->getSize().x) {
        _sprite.setPosition(SCREEN_WIDTH + 800 * _id, std::rand() % (SCREEN_HEIGHT / 2));
    }
    return 0;
}

void Pipe::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    _sprite.setTexture(_textures[_currentTexture]);
    window.draw(_sprite);
}

} /* namespace entity */
