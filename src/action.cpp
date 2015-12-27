#include "action.hpp"

namespace space_wars {

void Action::Perform(int player_id, mmpg::World& world) const {
  perform(player_id, static_cast<Universe&>(world));
}

}
