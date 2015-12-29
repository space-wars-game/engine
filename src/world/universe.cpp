#include <iostream>
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

  auto it = fleets.begin();

  while(it != fleets.end()) {
    Fleet* fleet = *it;

    fleet->Update(delta);

    if(fleet->has_arrived()) {
      planets[fleet->destination_id]->FleetArrives(fleet->owner, fleet->ships);

      delete fleet;
      it = fleets.erase(it);
    } else {
      ++it;
    }
  }
}

void Universe::MoveFleet(int player_id, int origin_id, int destination_id, int num_ships) {
  auto origin_it = planets.find(origin_id);

  if(origin_it == planets.end()) {
    return;
  }

  auto destination_it = planets.find(destination_id);

  if(destination_it == planets.end()) {
    return;
  }

  Planet& origin = *(origin_it->second);

  if(origin.owner != player_id or origin.ships < num_ships) {
    return;
  }

  origin.ships -= num_ships;

  Planet& destination = *(destination_it->second);

  fleets.push_back(new Fleet(player_id, num_ships, destination_id, origin.distance(destination)));
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
