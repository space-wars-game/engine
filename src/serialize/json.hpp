#pragma once

#include <ostream>
#include "../world/system.hpp"

namespace space_wars {

class Universe;

namespace serialize {
namespace json {

void Structure(const Universe& universe, std::ostream& stream);
void Structure(const std::vector<System*>& systems, std::ostream& stream);
void Structure(const System& system, std::ostream& stream);
void Structure(const Sun& sun, std::ostream& stream);
void Structure(const Relay& relay, std::ostream& stream);
void Structure(const std::vector<Planet*>& planets, std::ostream& stream);

void Data(const Universe& universe, std::ostream& stream);

}
}
}
