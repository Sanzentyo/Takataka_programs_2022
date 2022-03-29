#include <Adafruit_NeoPixel.h>

const int DIN_PIN = 6; // D6
const int LED_COUNT = 16; // LEDの数

Adafruit_NeoPixel pixels(LED_COUNT, DIN_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.clear();
  for (int i = 0;i < 16;i++) {
   pixels.setPixelColor(i, pixels.Color(128, 128, 128)); // 0番目の色を変える
  }
  pixels.show();
}

void loop() {

}
