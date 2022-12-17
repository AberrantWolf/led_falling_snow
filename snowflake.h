#include <FastLED.h>

#define MAX_FLAKE_VELOCITY 8

struct Snowflake {
  uint16_t pos;
  uint8_t velocity_countdown;
  uint8_t velocity;

  uint8_t distance() {
    // Would it work to do like...
    // *(uint8_t*)(&pos)
    // to just reinterpret the top byte?
    return uint8_t(pos >> 8);
  }

  uint8_t sub_distance() {
    return uint8_t(pos & 0xff);
  }

  void update_velocity() {
    velocity = random8(MAX_FLAKE_VELOCITY);
    velocity_countdown = random8(64, 256);
  }

  void tick() {
    pos += velocity;
    if (--velocity_countdown == 0) {
      update_velocity();
    }
  }
};

#define FLAKE_COUNT 3

template<int NUM_LEDS>
class SnowStrip {
  CRGB _leds[NUM_LEDS];
  Snowflake _snowflakes[FLAKE_COUNT];

public:
  template<int DATA_PIN>
  void setup () {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(_leds, NUM_LEDS);
    for (int i=0; i < FLAKE_COUNT; ++i) {
      // process each flake
      auto& flake = _snowflakes[i];
      flake.pos = 0;
      flake.update_velocity();
    }
  };

  void tick() {
    memset(_leds, 0, sizeof(_leds));
    for (int i=0; i < FLAKE_COUNT; ++i) {
      auto& flake = _snowflakes[i];
      const auto led = flake.distance();
      
      if (led == NUM_LEDS) {
        flake.pos = 0;
        flake.update_velocity();
        continue;
      }

      const uint8_t sub = flake.sub_distance();

      // TODO: Add colors instead of setting them...
      _leds[led] = CRGB::White;
      _leds[led].fadeLightBy(sub);
      if (led < NUM_LEDS-1) {
        _leds[led + 1] = CRGB::White;
        _leds[led + 1].fadeLightBy(~sub);
      }

      flake.tick();
    }
  }
};