#include <iostream>
#include "universe.hpp"
#include "../serialize/raw.hpp"
#include "../serialize/json.hpp"
#include "../deserialize.hpp"

namespace space_wars {


Universe::Universe() {

}

Universe::~Universe() {
  for(System* system : systems) {
    delete system;
  }
}

void Universe::Update(float delta) {
  for(System* system : systems) {
    for(Planet* planet : system->planets) {
      planet->GenerateShips(delta);
    }
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
  if(origin_id < 0 or origin_id >= planets.size() or destination_id < 0 or destination_id >= planets.size()) {
    return;
  }

  Planet& origin = *(planets[origin_id]);

  if(origin.owner != player_id or origin.ships < num_ships or !origin.HasConnection(destination_id)) {
    return;
  }

  origin.ships -= num_ships;

  Planet& destination = *(planets[destination_id]);

  fleets.push_back(new Fleet(player_id, num_ships, destination_id, origin.distance(destination)));
}

void Universe::PrintStructure(std::ostream& stream) const {
  serialize::raw::Structure(*this, stream);
}

void Universe::PrintViewerStructure(std::ostream& stream) const {
  serialize::json::Structure(*this, stream);
}

void Universe::ReadData(std::istream& stream) {
  deserialize::Data(*this, stream);
}

void Universe::PrintData(std::ostream& stream) const {
  serialize::raw::Data(*this, stream);
}

void Universe::PrintViewerData(std::ostream& stream) const {
  serialize::json::Data(*this, stream);
}

const std::vector<int>& Universe::owned_planets(int player_id) const {
  return player_planets.find(player_id)->second;
}

const Planet& Universe::planet(int planet_id) const {
  return *planets[planet_id];
}

}
