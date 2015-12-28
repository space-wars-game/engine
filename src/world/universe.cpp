#include "universe.hpp"

namespace space_wars {


Universe::Universe() {

}

void Universe::Update(float delta) {
  for(Planet* planet : system->planets) {
    planet->GenerateShips(delta);
  }
}

void Universe::Print(std::ostream& stream) {
  // TODO: Normal serializer
  (void)stream;
}


void Universe::PrintJSON(std::ostream& stream) {
  json_serializer_.Serialize(*this, stream);
}

}
