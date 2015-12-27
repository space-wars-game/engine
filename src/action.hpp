#pragma once

#include <mmpg/action.hpp>
#include "world/universe.hpp"

namespace space_wars {

class Action : public mmpg::Action {
 public:
  void Perform(int player_id, mmpg::World& world) const;

 protected:
  virtual void perform(int player_id, Universe& universe) const = 0;
};

}
