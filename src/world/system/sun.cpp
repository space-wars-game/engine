#include "sun.hpp"

namespace space_wars {

unsigned int Sun::MIN_RADIUS = 25;
unsigned int Sun::MAX_RADIUS = 40;

Sun::Sun() {

}

Sun::Sun(TYPE type, unsigned int radius) : type(type), radius(radius) {

}

}
