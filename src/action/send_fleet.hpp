#pragma once

#include "../action.hpp"

namespace space_wars {
namespace action {

class SendFleet : public Action {
 public:
  SendFleet(int origin_id, int destination_id, int num_ships);

  std::string str() const;

  void PrintJSON(std::ostream& stream) const;

 protected:
  void perform(int player_id, Universe& universe) const;

 public:
  int origin_id_;
  int destination_id_;
  int num_ships_;
};

}
}
