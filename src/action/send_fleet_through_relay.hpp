#pragma once

#include "../action.hpp"

namespace space_wars {
namespace action {

class SendFleetThroughRelay : public Action {
 public:
  SendFleetThroughRelay(int origin_id, int origin_relay, int destination_relay, int destination_id, int ships);

  std::string str() const;

  void PrintJSON(std::ostream& stream) const;

 protected:
  void perform(int player_id, Universe& universe) const;

 public:
  int origin_id;
  int origin_relay;

  int destination_relay;
  int destination_id;

  int num_ships;
};

}
}
