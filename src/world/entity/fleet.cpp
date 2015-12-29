#include "fleet.hpp"

namespace space_wars {


Fleet::Fleet(int owner, int ships, int destination_id, float distance) :
    owner(owner), ships(ships), destination_id(destination_id)
{
  time_left_ = distance / 40.f;
}


void Fleet::Update(float delta) {
  time_left_ -= delta;
}

bool Fleet::has_arrived() const {
  return time_left_ <= 0;
}

}
