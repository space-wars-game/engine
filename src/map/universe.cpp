#include "universe.hpp"
#include "../action/move.hpp"
#include "universe_generator.hpp"

namespace space_wars {


Universe::Universe() {

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

        ships.push_back(ship);
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
        ships[player]->y += 0.1f;
        break;
      case 'D':
        ships[player]->y -= 0.1f;
        break;
      case 'L':
        ships[player]->x -= 0.1f;
        break;
      case 'R':
        ships[player]->x += 0.1f;
        break;
    }
  }
}

void Universe::Print(std::ostream& stream) {
  stream << "PLAYERS" << std::endl;

  for(Ship* ship : ships) {
    stream << ship->x << ' ' << ship->y << std::endl;
  }
}


void Universe::PrintJSON(std::ostream& stream) {
  json_serializer_.Serialize(*this, stream);
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

void Universe::Generate(int seed) {
  UniverseGenerator generator(seed);
  generator.Generate(*this);
}

}
