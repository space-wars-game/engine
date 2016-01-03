#pragma once

#include <ostream>
#include "../world/system.hpp"

namespace space_wars {

class Universe;

namespace serialize {
namespace raw {

void Structure(const Universe& universe, std::ostream& stream);
void Structure(const std::vector<System*>& systems, std::ostream& stream);
void Structure(const System& system, std::ostream& stream);
void Structure(const Sun& sun, std::ostream& stream);
void Structure(const std::vector<Planet*>& planets, std::ostream& stream);
void Structure(const Planet& planet, std::ostream& stream);

void Data(const Universe& universe, std::ostream& stream);

}
}
}
