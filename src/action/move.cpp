#include "move.hpp"

namespace space_wars {

Move::Move(char direction) : direction_(direction) {

}

char Move::direction() const {
  return direction_;
}

std::string Move::str() const {
  return std::string(1, direction_);
}

void Move::PrintJSON(std::ostream& stream) const {
  stream << "{ \"type\": \"move\", \"direction\":\"" << direction_ << "\"}";
}

void Move::perform(int player_id, Universe& universe) const {
  (void)player_id;
  (void)universe;

  // Do nothing, as this is a test action
}

}
