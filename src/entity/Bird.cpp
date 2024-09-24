#include "../../include/entity/Bird.hpp"

namespace entity {

/**
 * @brief Constructs a new Bird object.
 */
Bird::Bird() {

}

/**
 * @brief Destroys the Bird object.
 */
Bird::~Bird() {

}

/**
 * @brief Copy constructor.
 * @param other The other Bird object to copy.
 */
Bird::Bird(const Bird &) {

}

/**
 * @brief Copy assignment operator.
 * @param other The other Bird object to assign from.
 * @return A reference to the assigned Bird object.
 */
Bird& Bird::operator=(const Bird &) {
    return *this;
}

} /* namespace entity */
