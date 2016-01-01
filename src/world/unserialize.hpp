#pragma once

#include <istream>
#include "system.hpp"

namespace space_wars {

class Universe;

void Unserialize(Universe& universe, std::istream& stream);
void Unserialize(std::vector<System*>& systems, std::istream& stream, Universe& universe);
void Unserialize(System& system, std::istream& stream, Universe& universe);
void Unserialize(Sun& sun, std::istream& stream);
void Unserialize(std::vector<Planet*>& planets, std::istream& stream, Universe& universe);
void Unserialize(Planet& planet, std::istream& stream);

}
