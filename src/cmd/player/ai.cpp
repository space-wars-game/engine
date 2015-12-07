#include <ai.hpp>
#include "../../action/move.hpp"

namespace space_wars {

mmpg::Action* AI::MoveUp() const {
  return new Move('U');
}

mmpg::Action* AI::MoveDown() const {
  return new Move('D');
}

mmpg::Action* AI::MoveLeft() const {
  return new Move('L');
}

mmpg::Action* AI::MoveRight() const {
  return new Move('R');
}

}
