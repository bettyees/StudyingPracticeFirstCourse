#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define NUM_LEDS   64
#define MATRIX_W   8
#define MATRIX_H   8
#define BRIGHTNESS 100

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// координаты (x, y) -> индекс в ленте с учётом «змейки»
int XY(int x, int y) {
  if (y % 2 == 0) return y * MATRIX_W + x;
  else            return y * MATRIX_W + (MATRIX_W - 1 - x);
}

// смайлик
const byte anim1[8] = {
  B00111100, B01000010, B10100101, B10000001,
  B10100101, B10011001, B01000010, B00111100
};
// сердце
const byte anim2[8] = {
  B01100110, B11111111, B11111111, B11111111,
  B01111110, B00111100, B00011000, B00000000
};
// стрелка вверх
const byte anim3[8] = {
  B00011000, B00111100, B01111110, B11111111,
  B00011000, B00011000, B00011000, B00000000
};
// молния
const byte anim4[8] = {
  B00011110, B00111100, B01111000, B11111111,
  B00011110, B00111100, B01111000, B11110000
};
// восклицательный знак
const byte anim5[8] = {
  B00011000, B00011000, B00011000, B00011000,
  B00011000, B00000000, B00011000, B00000000
};

void drawFrame(const byte f[8], uint32_t color) {
  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 8; x++)
      strip.setPixelColor(XY(x, y), bitRead(f[y], 7 - x) ? color : 0);
  strip.show();
}

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  drawFrame(anim1, strip.Color(0, 255, 0));     // смайлик — зелёный
  delay(800);
  drawFrame(anim2, strip.Color(255, 0, 0));     // сердце — красный
  delay(800);
  drawFrame(anim3, strip.Color(0, 128, 255));   // стрелка — голубая
  delay(800);
  drawFrame(anim4, strip.Color(255, 255, 0));   // молния — жёлтая
  delay(800);
  drawFrame(anim5, strip.Color(255, 0, 255));   // знак — пурпурный
  delay(800);
}
