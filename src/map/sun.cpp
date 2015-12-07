#include "sun.hpp"

namespace space_wars {

unsigned int Sun::MIN_RADIUS = 15;
unsigned int Sun::MAX_RADIUS = 30;

Sun::Sun(TYPE type, unsigned int radius) : type(type), radius(radius) {

}

}
