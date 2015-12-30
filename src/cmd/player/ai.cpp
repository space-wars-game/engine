#include <ai.hpp>
#include "../../world/universe.hpp"
#include "../../action/send_fleet.hpp"

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
  if(num_ships <= 0)
    return;

  ChangeAction(new SendFleet(origin_id, connection_id, num_ships));
}

const std::vector<int>& AI::owned_planets(int player_id) const {
  return universe_->owned_planets(player_id);
}

const Planet& AI::planet(int planet_id) const {
  return universe_->planet(planet_id);
}

}
