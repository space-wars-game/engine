#pragma once


#include "../action.hpp"

namespace space_wars {

class Move : public Action {
 public:
  Move(char direction);

  char direction() const;
  std::string str() const;

  void PrintJSON(std::ostream& stream) const;

 protected:
  void perform(int player_id, Universe& universe) const;

 private:
  char direction_;
};

}
