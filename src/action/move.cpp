#include "move.hpp"

namespace space_wars {

Move::Move(char direction) : super("move"), direction_(direction) {

}

void Move::end_json(std::ostream& stream) const {
  stream << ",\"direction\":\"" << direction_ << "\"}";
}

char Move::direction() const {
  return direction_;
}

std::string Move::str() const {
  return std::string(1, direction_);
}

}
