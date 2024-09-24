#include "../../include/entity/AEntity.hpp"

namespace entity {

/**
 * @brief Constructs a new AEntity object.
 */
AEntity::AEntity() {

}

/**
 * @brief Destroys the AEntity object.
 */
AEntity::~AEntity() {

}

/**
 * @brief Copy constructor.
 * @param other The other AEntity object to copy.
 */
AEntity::AEntity(const AEntity &) {

}

/**
 * @brief Copy assignment operator.
 * @param other The other AEntity object to assign from.
 * @return A reference to the assigned AEntity object.
 */
AEntity& AEntity::operator=(const AEntity &) {
    return *this;
}

} /* namespace entity */
