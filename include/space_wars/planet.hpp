#pragma once

#include <vector>
#include "celestial_body.hpp"

namespace space_wars {

class Planet : public CelestialBody {
 public:
  typedef CelestialBody super;

  static unsigned int MIN_RADIUS;
  static unsigned int MAX_RADIUS;

  static unsigned int MIN_DISTANCE_X;
  static unsigned int MAX_DISTANCE_X;

  static unsigned int MIN_DISTANCE_Y;
  static unsigned int MAX_DISTANCE_Y;

  static unsigned int MIN_NUM_CONNECTIONS;
  static unsigned int MAX_NUM_CONNECTIONS;

  static unsigned int NUM_TYPES;
  static unsigned int PROB_ROTATION_CLOCKWISE;
  static unsigned int MIN_ROTATION_SPEED;
  static unsigned int MAX_ROTATION_SPEED;

  Planet();
  Planet(unsigned int radius, unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position);

  bool is_owned() const;
  unsigned int ship_rate() const;
  bool HasConnection(int planet_id) const;
  bool CanSendFleet(int player_id, int num_ships) const;
  bool has_relay() const;

  void GenerateShips(float delta);
  void FleetArrives(int fleet_owner, int fleet_ships);

  unsigned int id;
  std::vector<int> connections;
  int relay;
  int owner;
  int ships;
  unsigned int type;
  int rotation_direction;
  unsigned int rotation_speed;

 private:
  float ships_accum;
};

}
