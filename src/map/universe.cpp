#include "universe.hpp"
#include "../action/move.hpp"

namespace space_wars {


Universe::Universe() : solar_system_(time(NULL)) {

}

void Universe::Read(std::istream& stream) {
  std::string section;

  while(stream >> section) {
    if(section == "PLAYERS") {
      float x, y;

      while(stream >> x >> y) {
        Ship* ship = new Ship;
        ship->x = x;
        ship->y = y;

        ships_.push_back(ship);
      }
    }
  }
}

void Universe::Update(int player, const mmpg::Action& action) {
  // TODO: Improve action abstraction. Polymorphism?
  if(action.type() == "move") {
    const Move& move = (const Move&) action;

    switch(move.direction()) {
      case 'U':
        ships_[player]->y += 0.1f;
        break;
      case 'D':
        ships_[player]->y -= 0.1f;
        break;
      case 'L':
        ships_[player]->x -= 0.1f;
        break;
      case 'R':
        ships_[player]->x += 0.1f;
        break;
    }
  }
}

void Universe::Print(std::ostream& stream) {
  stream << "PLAYERS" << std::endl;

  for(Ship* ship : ships_) {
    stream << ship->x << ' ' << ship->y << std::endl;
  }
}


void Universe::PrintJSON(std::ostream& stream) {
  stream << "{\"players\":[";

  for(Ship* ship : ships_) {
    stream << "{\"x\":" << ship->x << ",\"y\":" << ship->y << "}";
  }

  stream << "],\"sun\":";

  solar_system_.sun->PrintJSON(stream);

  stream << "}";
}

mmpg::Action* Universe::ParseAction(std::istream& data) {
  char t;

  data >> t;

  switch(t) {
    case 'U':
    case 'D':
    case 'L':
    case 'R':
      return new Move(t);

    default:
      return 0;
  }
}

}
