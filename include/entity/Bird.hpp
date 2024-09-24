#pragma once

#include "AEntity.hpp"
namespace entity {

/**
 * @class Bird
 * @brief ...
 */
class Bird: public AEntity {
    public:
        Bird();
        ~Bird();
        Bird(const Bird &other);
        Bird& operator=(const Bird &other);

        bool move();
};

} /* namespace entity */
