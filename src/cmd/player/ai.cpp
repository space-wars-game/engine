#include <ai.hpp>
#include <iostream>
#include "../../world/universe.hpp"

namespace space_wars {

void AI::ScanUniverse() {
  if(universe_ != 0) {
    delete universe_;
  }

  universe_ = static_cast<Universe*>(read_world());
}

void AI::RefreshWorld() {
  ScanUniverse();
}

void AI::SendShips(int origin_id, int connection_id, int num_ships) {
  (void)origin_id;
  (void)connection_id;
  (void)num_ships;

  // TODO: Send ship logic
}

const std::vector<int>& AI::owned_planets(int player_id) const {
  return universe_->owned_planets(player_id);
}

const Planet& AI::planet(int planet_id) const {
  return universe_->planet(planet_id);
}

}
