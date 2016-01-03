#pragma once

#include <istream>
#include "world/system.hpp"

namespace space_wars {

class Universe;

namespace deserialize {

void Structure(Universe& universe, std::istream& stream);
void Structure(std::vector<System*>& systems, std::istream& stream, Universe& universe);
void Structure(System& system, std::istream& stream, Universe& universe);
void Structure(Sun& sun, std::istream& stream);
void Structure(std::vector<Planet*>& planets, std::istream& stream, Universe& universe);
void Structure(Planet& planet, std::istream& stream);

void Data(Universe& universe, std::istream& stream);

}
}
