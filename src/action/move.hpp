#pragma once

#include <mmpg/action.hpp>

namespace space_wars {

class Move : public mmpg::Action {
 public:
  typedef mmpg::Action super;

  Move(char direction);

  char direction() const;
  std::string str() const;

 protected:
  void end_json(std::ostream& stream) const;

 private:
  char direction_;
};

}
