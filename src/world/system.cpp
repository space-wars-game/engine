
#include "system.hpp"

namespace space_wars {

unsigned int System::MIN_SIZE = 6;
unsigned int System::MAX_SIZE = 12;
unsigned int System::HOME_NUM_CONNECTIONS = 2;

System::System() {

}

System::~System() {
  delete sun;

  for(Planet* planet : planets) {
    delete planet;
  }
}

void System::Conquer(unsigned int planet_id, unsigned int player_id) {
  planets[planet_id]->owner = player_id;
}

}
