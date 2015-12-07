#pragma once

#include <mmpg/player/ai.hpp>

namespace space_wars {

class AI : public mmpg::AI {
 public:
  mmpg::Action* MoveUp() const;
  mmpg::Action* MoveDown() const;
  mmpg::Action* MoveLeft() const;
  mmpg::Action* MoveRight() const;
};

}
