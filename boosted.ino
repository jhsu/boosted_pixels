#include <Adafruit_NeoPixel.h>

#define PIN 6

#define GROUP_SIZE 16
#define GROUPS 2
#define NUM_PIXELS GROUP_SIZE * GROUPS
#define STRIP_SIZE 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_SIZE, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  clearStrip(0, STRIP_SIZE);
  strip.show();
}

unsigned int pos_pair = 0;
boolean forward = true;

void loop() {
  
  fillPos(pos_pair, 0 * GROUP_SIZE, GROUP_SIZE, false);
  fillPos(pos_pair, 1 * GROUP_SIZE, GROUP_SIZE, true);
  
  strip.show();

  if (pos_pair == GROUP_SIZE - 1) {
    forward = false;
  } else if (pos_pair == 0) {
    forward = true;
  } 

  if (forward) {
    pos_pair = pos_pair + 1;
  } else {
    pos_pair = pos_pair - 1;
  }
}

void fillPos(int pos, int startpoint, int group_size, boolean reversed) {
  unsigned int endpoint = startpoint + group_size -1;
  clearStrip(startpoint, endpoint);
  if (reversed) {
    pos = endpoint - pos;
  } else {
    pos = startpoint + pos;
  }
  
  strip.setPixelColor(pos, 0, 255, 0);
}


void clearStrip(uint8_t startpos, uint8_t endpos) {
  for( int i=startpos; i<=endpos; i++){
    strip.setPixelColor(i, 0, 0, 0); strip.show();
  }
}
