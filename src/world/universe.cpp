#include "universe.hpp"
#include "serialize.hpp"

namespace space_wars {


Universe::Universe() : system(0) {

}

Universe::~Universe() {
  if(system != 0) {
    delete system;
  }
}

void Universe::Update(float delta) {
  for(Planet* planet : system->planets) {
    planet->GenerateShips(delta);
  }
}

void Universe::Print(std::ostream& stream) {
  Serialize(*this, stream);
}


void Universe::PrintJSON(std::ostream& stream) {
  json_serializer_.Serialize(*this, stream);
}

const std::vector<int>& Universe::owned_planets(int player_id) const {
  return player_planets.find(player_id)->second;
}

const Planet& Universe::planet(int planet_id) const {
  return *planets.find(planet_id)->second;
}

}
