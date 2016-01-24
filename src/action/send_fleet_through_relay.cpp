#include "send_fleet_through_relay.hpp"

namespace space_wars {
namespace action {

SendFleetThroughRelay::SendFleetThroughRelay(int origin_id, int origin_relay, int destination_relay, int destination_id,
                                             int ships) : origin_id(origin_id),
                                                          origin_relay(origin_relay),
                                                          destination_relay(destination_relay),
                                                          destination_id(destination_id),
                                                          num_ships(ships)
{

}

void SendFleetThroughRelay::perform(int player_id, Universe& universe) const {
  universe.SendFleetThroughRelay(player_id, origin_id, origin_relay, destination_relay, destination_id, num_ships);
}

std::string SendFleetThroughRelay::str() const {
  return "R " + std::to_string(origin_id) + " " + std::to_string(origin_relay) + " " +
      std::to_string(destination_relay) + " " + std::to_string(destination_id) + " " + std::to_string(num_ships);
}

void SendFleetThroughRelay::PrintJSON(std::ostream& stream) const {
  stream << "{\"type\":\"send_fleet_through_relay\",\"origin\":" << origin_id << ",\"destination\":"
  << destination_id <<  ",\"ships\":" << num_ships << ",\"relays\":[" << origin_relay << ',' << destination_relay
  << "]}";
}

}
}
