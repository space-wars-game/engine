#include "sun.hpp"

namespace space_wars {

unsigned int Sun::MIN_RADIUS = 25;
unsigned int Sun::MAX_RADIUS = 40;

Sun::Sun() : super(0, 0, 0, 0) {

}

Sun::Sun(TYPE type, unsigned int radius) : super(radius, 0, 0, 0), type(type) {

}

}
