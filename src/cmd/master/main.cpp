#include <mmpg/master/process.hpp>
#include "../../map/universe.hpp"

using namespace space_wars;

int main() {
  mmpg::master::Process master;

  Universe universe;
  master.Run(universe);

  return 0;
}
