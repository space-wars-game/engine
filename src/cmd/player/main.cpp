#include <player/process.hpp>
#include "map/universe.hpp"

using namespace space_wars;

int main(int argc, char* argv[]) {
  mmpg::player::Process player(argc, argv);

  Universe universe;
  player.Run(universe);

  return 0;
}
