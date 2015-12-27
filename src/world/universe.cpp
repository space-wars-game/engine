#include "universe.hpp"

namespace space_wars {


Universe::Universe() {

}

void Universe::Update(int player, const mmpg::Action& action) {
  (void)player;
  (void)action;
  // TODO: Update logic
}

void Universe::Print(std::ostream& stream) {
  // TODO: Normal serializer
  (void)stream;
}


void Universe::PrintJSON(std::ostream& stream) {
  json_serializer_.Serialize(*this, stream);
}

}
