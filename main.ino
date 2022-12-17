#include <Arduino.h>

// NOTE: ESP32 is not an SPI-compatible LED chipset (I guess?)
// #define FASTLED_ALL_PINS_HARDWARE_SPI
#include <FastLED.h>

#include "snowflake.h"

#define NUM_LEDS 60
#define NUM_STRIPS 10

constexpr int used_pins[NUM_STRIPS] = {
  0, 4, 16, 17, 5,
  12, 14, 27, 26, 25
};

SnowStrip<NUM_LEDS> strips[10];

void setup() {
  strips[0].setup<used_pins[0]>();
  strips[1].setup<used_pins[1]>();
  strips[2].setup<used_pins[2]>();
  strips[3].setup<used_pins[3]>();
  strips[4].setup<used_pins[4]>();
  strips[5].setup<used_pins[5]>();
  strips[6].setup<used_pins[6]>();
  strips[7].setup<used_pins[7]>();
  strips[8].setup<used_pins[8]>();
  strips[9].setup<used_pins[9]>();
}

void loop() {
  for (int i=0; i<NUM_STRIPS; ++i) {
    strips[i].tick();
  }

  FastLED.show();
}
