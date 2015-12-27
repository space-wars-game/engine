#include <mmpg/player/process.hpp>
#include "../../space_wars.hpp"

using namespace space_wars;

int main(int argc, char* argv[]) {

  SpaceWars space_wars;

  mmpg::player::Process player(argc, argv);
  player.Run(space_wars);

  return 0;
}
