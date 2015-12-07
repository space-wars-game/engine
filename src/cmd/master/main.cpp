#include <mmpg/master/process.hpp>
#include "../../map/universe.hpp"

using namespace space_wars;

int main() {
  mmpg::master::Process master;

  // This creates an empty universe
  Universe universe;

  // Generate a universe pseudo-randomly
  // TODO: Master process should call this when there's no saved world
  universe.Generate(time(NULL));

  // Run a master process with this universe
  master.Run(universe);

  return 0;
}
