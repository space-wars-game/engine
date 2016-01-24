#include <ai.hpp>
#include "../../world/universe.hpp"
#include "../../action/send_fleet.hpp"
#include "../../action/send_fleet_through_relay.hpp"

namespace space_wars {

void AI::world(mmpg::World* world) {
  universe_ = static_cast<Universe*>(world);
}

void AI::ScanUniverse() {
  RefreshWorld(universe_);
}

void AI::SendFleet(int origin_id, int connection_id, int num_ships) {
  if(num_ships <= 0)
    return;

  ChangeAction(new action::SendFleet(origin_id, connection_id, num_ships));
}

void AI::SendFleet(int origin_id, int relay_a, int relay_b, int destination_id, int num_ships) {
  if(num_ships <= 0)
    return;

  ChangeAction(new action::SendFleetThroughRelay(origin_id, relay_a, relay_b, destination_id, num_ships));
}

const std::vector<int>& AI::owned_planets(int player_id) const {
  return universe_->owned_planets(player_id);
}

const Planet& AI::planet(int planet_id) const {
  return universe_->planet(planet_id);
}

const Relay& AI::relay(int relay_id) const {
  return universe_->relay(relay_id);
}

}
