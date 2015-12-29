#include "send_fleet.hpp"

namespace space_wars {

SendFleet::SendFleet(int origin_id, int destination_id, int num_ships) :
    origin_id_(origin_id), destination_id_(destination_id), num_ships_(num_ships)
{

}

void SendFleet::perform(int player_id, Universe& universe) const {
  universe.MoveFleet(player_id, origin_id_, destination_id_, num_ships_);
}

std::string SendFleet::str() const {
  return "F " + std::to_string(origin_id_) + " " + std::to_string(destination_id_) + " " + std::to_string(num_ships_);
}

void SendFleet::PrintJSON(std::ostream& stream) const {
  stream << "{\"type\":\"send_fleet\",\"origin\":" << origin_id_ << ",\"destination\":" << destination_id_ <<
      ",\"ships\":" << num_ships_ << "}";
}

}
