#ifndef P3A_GAME_CONFIGURATION_H_
#define P3A_GAME_CONFIGURATION_H_

#include "Engine/Types.h"

namespace P3A {
namespace Game {
class Configuration {
  public:
    inline Configuration(uint32 const& _hero_max, uint32 const& _creature_max,
                          uint32 const& _missile_max, real32 const& _interval)
        : hero_max_(_hero_max),
          creature_max_(_creature_max),
          missile_max_(_missile_max),
          interval_(_interval) { }
    inline Configuration(Configuration && _other)
        : hero_max_(_other.hero_max_),
          creature_max_(_other.creature_max_),
          missile_max_(_other.missile_max_),
          interval_(_other.interval_) { }
    inline Configuration(Configuration const& _other)
        : hero_max_(_other.hero_max_),
          creature_max_(_other.creature_max_),
          interval_(_other.interval_) { }
    inline Configuration & operator=(Configuration && _other) = delete;
    inline Configuration & operator=(Configuration const& _other) = delete;
    inline virtual ~Configuration(void) = default;

    inline uint32 hero_max(void) const { return hero_max_; }
    inline void set_hero_max(uint32 const& _hero_max) { hero_max_ = _hero_max; }
    inline uint32 creature_max(void) const { return creature_max_; }
    inline void set_creature_max(uint32 const& _creature_max) { creature_max_ = _creature_max; }
    inline uint32 missile_max(void) const { return missile_max_; }
    inline void set_missile_max(uint32 const& _missile_max) { missile_max_ = _missile_max; }

    inline real32 interval(void) const { return interval_; }
    inline void set_interval(real32 const& _interval) { interval_ = _interval; }

  private:
    uint32 hero_max_ = 0;
    uint32 creature_max_ = 0;
    uint32 missile_max_ = 0;

    real32 interval_ = 0.f;
};
}
}

#endif