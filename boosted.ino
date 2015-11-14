#include <Adafruit_NeoPixel.h>

#define PIN 6

#define GROUP_SIZE 15
#define GROUPS 4
#define NUM_PIXELS GROUP_SIZE * GROUPS
#define STRIP_SIZE 60

#define ACCEL_SLOW_1 150
#define ACCEL_SLOW_2 100
#define ACCEL_FAST_1 60
#define ACCEL_FAST_2 24


Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_SIZE, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  clearStrip(0, STRIP_SIZE);
}

unsigned int pos_pair = 14;
unsigned int moveSpeed = 0;
unsigned int accelDelay = ACCEL_SLOW_1;
boolean forward = true;

boolean play = true;

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'x') {
      suspend();
    }
    if (ch == 'r') {
      moveSpeed = 0;
    }
    Serial.println(ch);
  }
  if (!play) {
    delay(500);
    return;
  }

  clearStrip(0, NUM_PIXELS - 1);
  fillPos(pos_pair, 0 * GROUP_SIZE, GROUP_SIZE, false);
  fillPos(pos_pair, 1 * GROUP_SIZE, GROUP_SIZE, true);
  fillPos(pos_pair, 2 * GROUP_SIZE, GROUP_SIZE, false);
  fillPos(pos_pair, 3 * GROUP_SIZE, GROUP_SIZE, true);
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

  if (moveSpeed < 15) {
    accelDelay = ACCEL_SLOW_1;
  } else if (moveSpeed < 30) {
    accelDelay = ACCEL_SLOW_2;
  } else if (moveSpeed < 40) {
    accelDelay = ACCEL_FAST_1;
  } else if (moveSpeed >= 60) {
    accelDelay = ACCEL_FAST_2;
  }

  moveSpeed++;

  delay(accelDelay);
}

void suspend() {
  play = !play;
}

void fillPos(int pos, int startpoint, int group_size, boolean reversed) {
  unsigned int endpoint = startpoint + group_size -1;
  if (reversed) {
    pos = endpoint - pos;
  } else {
    pos = startpoint + pos;
  }

  strip.setPixelColor(pos, 0, 255, 0);
}


void clearStrip(uint8_t startpos, uint8_t endpos) {
  for( int i=startpos; i<=endpos; i++){
    strip.setPixelColor(i, 0, 0, 0);
  }
}
