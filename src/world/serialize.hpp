#pragma once

#include <ostream>
#include "system.hpp"

namespace space_wars {

class Universe;

void Serialize(const Universe& universe, std::ostream& stream);
void Serialize(const System& system, std::ostream& stream);
void Serialize(const Sun& sun, std::ostream& stream);
void Serialize(const std::vector<Planet*>& planets, std::ostream& stream);
void Serialize(const Planet& planet, std::ostream& stream);

}
