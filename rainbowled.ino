#include <gfxfont.h>
#include <gamma.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>

// sw pin for the joystick
const int SW_pin = 2;
// x output
const int x_pin = 0;
// y output
const int y_pin = 1;

int x = 0;
int y = 0;
int restart_b = 0;

const int matrix_pin = 6;

// player will start from top left
int player = 0;

// the array with red leds
int leds[5];

// declaring the matrix (dig_pin = 6)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, matrix_pin,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE);

void setAll(int red, int green, int blue) {
  int c = 0;

  for (c = 0; c < 64; c++) {
    matrix.setPixelColor(c, red, green, blue);
  }

  matrix.show();
}

void setup() {
  matrix.begin();
  matrix.clear();
  matrix.setBrightness(50);
  matrix.show();
  
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
 int r = 0;
 int rr = 0;
 int rrr = 0;
 int button = digitalRead(SW_pin); int x = analogRead(x_pin);
 int y = analogRead(y_pin); 
  
// for (r = 0; r < 256; r++) {1

if (button == 1) {
 if (x == 0) {
  delay(300);
//   for (rrr = 0; rrr < 256; rrr++){
//     setAll(0, rrr, 256 - rrr);}
  setAll(0, 255, 255);
 }
 if (x == 1023){
  delay(400);
  setAll(255, 255, 0);
//   for (rrr = 0; rrr < 256; rrr++){
//     setAll(rrr, 0, 256 - rrr);}
 }
 if (y == 0){
  delay(500);
  setAll(255, 0, 255);
//   for (rrr = 0; rrr < 256; rrr++){
//     setAll(0, 256 - rrr, rrr);    } 
 }
 if (x == 0){
delay(200);
setAll(0, 255, 0);
//   for (rrr = 0; rrr < 256; rrr++){
//     setAll(rrr, 256 - rrr, 0);}
 }
}
 if (button != 1) {
 delay(300);
   for (rrr = 0; rrr < 256; rrr++) {
     setAll(256 - rrr, 0, rrr);
   }
 }
}
