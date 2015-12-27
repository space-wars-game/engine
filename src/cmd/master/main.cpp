#include <mmpg/master/process.hpp>
#include "../../space_wars.hpp"

using namespace space_wars;

int main() {
  // Create a game instance
  SpaceWars space_wars;

  // Run a master process for this game
  mmpg::master::Process master;
  master.Run(space_wars);

  return 0;
}
