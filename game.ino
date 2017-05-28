/* Game: at the start 6 leds are lit: 5 random red leds (checkpoints) and 1 yellow (player). 
   The player is controlled by joystick. When a checkpoint is reached, it changes its color to green. 
   When the player reaches all checkpoints, the game is restarted (it can be restarted also by pressing the joystick). */

// Used hardware: Arduino Uno, Adafruit NeoMatrix (8x8), joystick

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
int restartButton = 0;

const int blinkTime = 100;

const int matrix_pin = 6;

// player will start from top left
int player = 0;

// the array with red leds
int leds[5];

// how many leds the player has reached
int reachedLeds = 0;

// declaring the matrix (dig_pin = 6)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, matrix_pin,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE);

// setPixelColor(red, green, blue)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// checks whether the new chosen led is already on

int check(int counter, int num) {
  Serial.print(" ! check ! ");
  int c = counter;
  int change = 0;
  
  for (c = counter; c >= 0; c--) {
    if (leds[c] == num) {
      change++;
      break;
    }
  }

  return change;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sets random 5 red leds (this function is a little buggy)

void setRandomLEDs() {
  reachedLeds = 0;
  int counter = 0;
  int counter_2 = 0;
  int led = 0;
  int change = 0;

  for (counter_2 = 0; counter_2 < 5; counter_2++) {
    leds[counter_2] = 0;
  }
  
  while (counter < 5) {
    led = random(1, 63);

    Serial.print(" setRandomLEDs(): led: ");
    Serial.print(led);
    Serial.print(" ");

    if (counter != 0) {
      change = check(counter, led);
      Serial.print(" setRandomLEDs(): change: ");
      Serial.print(change);
      Serial.print(" ");

      while (change != 0) {
        led = random(1, 63);
        Serial.print(" setRandomLEDs: new led after change: ");
        Serial.print(led);
        Serial.print(" "); 
      }
    }
    
    leds[counter] = led;
    change = 0;
    counter++;
    
    matrix.setPixelColor(led, 255, 0, 0);
    matrix.show();
    Serial.print(" setRandomLEDs: final led: ");
    Serial.print(led);
    Serial.print("|| ");
  }

  Serial.print(" ~ End of random leds ~ "); 
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void restart() {
  player = 0;
  matrix.setPixelColor(player, 255, 255, 0);
  
  setRandomLEDs();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setAll(int red, int green, int blue) {
  Serial.print(" setAll ");
  int c = 0;

  for (c = 0; c < 64; c++) {
    matrix.setPixelColor(c, red, green, blue);
  }

  matrix.show();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// those functions spc...() exist because I'm lazy

void spc(int led, int red, int green, int blue) {
  matrix.setPixelColor(led ,red, green, blue);
  matrix.show();
}

void spcY(int led) {
  matrix.setPixelColor(led ,255, 255, 0);
  matrix.show();
}

void spcG(int led) {
  matrix.setPixelColor(led ,0, 255, 0);
  matrix.show();
}

void spcR(int led) {
  matrix.setPixelColor(led ,255, 0, 0);
  matrix.show();
}

void spcT(int led) {
  matrix.setPixelColor(led , 0, 0, 0);
  matrix.show();
}

void spcRCP(int led) {
  spcT(led);
  delay(blinkTime);
  spcG(led);
  delay(blinkTime);
  spcT(led);
  delay(blinkTime);
  spcG(led);
  delay(blinkTime);
  spcT(led);
  delay(blinkTime);
  spcG(led);  
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void moveLeft() {
  Serial.print(" * moveLeft() with player: ");
  Serial.print(player);
  int reachedCP = 0;

  if (((player >= 1) && (player <= 7)) || ((player >= 9) && (player <= 15)) || ((player >= 17) && (player <= 23)) || ((player >= 25) && (player <= 31)) || ((player >= 33) && (player <= 39)) || ((player >= 41) && (player <= 47)) || ((player >= 49) && (player <= 55)) || ((player >= 57) && (player <= 63))) { 
    spcT(player);
    player--;
    Serial.print(" moveleft: rights ");

    int counter = 0;
    for (counter = 0; counter < 5; counter++) {
      Serial.print(" in for() ");
      if (player == leds[counter]) {
        reachedLeds++;
        reachedCP++;
        leds[counter] = 64;
      }
    }

    if (reachedCP == 0) {
      spcY(player);
      Serial.print(" not reachedcp ");
    } else {
      spcRCP(player);
      Serial.print(" reachedcp ");
    }
  }

  if ((player == 0) || (player == 8) || (player == 16) || (player == 24) || (player == 32) || (player == 40) || (player == 48) || (player == 56)) {
    spcT(player);
    player += 7;
    Serial.print(" moveleft: lefts ");
    
    int counter = 0;
    for (counter = 0; counter < 5; counter++) {
      Serial.print(" in for() ");
      if (player == leds[counter]) {
        reachedLeds++;
        reachedCP++;
        leds[counter] = 64;
      }
    }

    if (reachedCP == 0) {
      spcY(player);
      Serial.print(" not reachedcp ");
    } else {
      spcRCP(player);
      Serial.print(" reachedcp ");
    }
  }
  
  Serial.print(" new player: ");
  Serial.print(player);
  Serial.print(" * ");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void moveRight() {
  Serial.print(" * moveRight() with player: ");
  Serial.print(player);
  int reachedCP = 0;

  if (((player >= 0) && (player <= 6)) || ((player >= 8) && (player <= 14)) || ((player >= 16) && (player <= 22)) || ((player >= 24) && (player <= 30)) || ((player >= 32) && (player <= 38)) || ((player >= 40) && (player <= 46)) || ((player >= 48) && (player <= 54)) || ((player >= 56) && (player <= 62))) { 
    spcT(player);
    player++;
    Serial.print(" moveright: lefts: ");

    int counter = 0;
    for (counter = 0; counter < 5; counter++) {
      Serial.print(" in for() ");
      if (player == leds[counter]) {
        reachedLeds++;
        reachedCP++;
        leds[counter] = 64;
      }
    }

    if (reachedCP == 0) {
      spcY(player);
      Serial.print(" not reachedcp ");
    } else {
      spcRCP(player);
      Serial.print(" reachedcp ");
    }
  }

  if ((player == 7) || (player == 15) || (player == 23) || (player == 31) || (player == 39) || (player == 47) || (player == 55) || (player == 63)) {
    spcT(player);
    player -= 7;
    Serial.print(" moveright: rights ");
    
    int counter = 0;
    for (counter = 0; counter < 5; counter++) {
      Serial.print(" in for() ");
      if (player == leds[counter]) {
        reachedLeds++;
        reachedCP++;
        leds[counter] = 64;
      }
    }

    if (reachedCP == 0) {
      spcY(player);
      Serial.print(" not reachedcp ");
    } else {
      spcRCP(player);
      Serial.print(" reachedcp ");
    }
  }
  
  Serial.print(" new player: ");
  Serial.print(player);
  Serial.print(" * ");

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void moveDown() {
  Serial.print(" * moveDown() with player: ");
  Serial.print(player);
  int reachedCP = 0;

  if ((player >= 0) && (player <= 55) ) { 
    spcT(player);
    player += 8;
    Serial.print(" movedown: 0-55: ");

    int counter = 0;
    for (counter = 0; counter < 5; counter++) {
      Serial.print(" in for() ");
      if (player == leds[counter]) {
        reachedLeds++;
        reachedCP++;
        leds[counter] = 64;
      }
    }

    if (reachedCP == 0) {
      spcY(player);
      Serial.print(" not reachedcp ");
    } else {
      spcRCP(player);
      Serial.print(" reachedcp ");
    }
  }

  if ((player >= 56) && (player <= 63)) {
    spcT(player);
    player -= 56;
    Serial.print(" movedown: 56-63: ");
    
    int counter = 0;
    for (counter = 0; counter < 5; counter++) {
      Serial.print(" in for() ");
      if (player == leds[counter]) {
        reachedLeds++;
        reachedCP++;
        leds[counter] = 64;
      }
    }

    if (reachedCP == 0) {
      spcY(player);
      Serial.print(" not reachedcp ");
    } else {
      spcRCP(player);
      Serial.print(" reachedcp ");
    }
  }

  Serial.print(" new player: ");
  Serial.print(player);
  Serial.print(" * ");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void moveUp() {
  Serial.print(" * moveUp() with player: ");
  Serial.print(player);
  int reachedCP = 0;

  if ((player >= 8) && (player <= 63)) { 
    spcT(player);
    player -= 8;
    Serial.print(" moveup: player 8-63: ");

    int counter = 0;
    for (counter = 0; counter < 5; counter++) {
      Serial.print(" in for() ");
      if (player == leds[counter]) {
        reachedLeds++;
        reachedCP++;
        leds[counter] = 64;
      }
    }

    if (reachedCP == 0) {
      spcY(player);
      Serial.print(" not reachedcp ");
    } else {
      spcRCP(player);
      Serial.print(" reachedcp ");
    }
  }

  if ((player >= 0) && (player <= 7)) {
    spcT(player);
    Serial.print(" moveup: player: 0-7");
    player += 56;
    
    int counter = 0;
    for (counter = 0; counter < 5; counter++) {
      Serial.print(" in for() ");
      if (player == leds[counter]) {
        reachedLeds++;
        reachedCP++;
        leds[counter] = 64;
      }
    }

    if (reachedCP == 0) {
      spcY(player);
      Serial.print(" not reachedcp ");
    } else {
      spcRCP(player);
      Serial.print(" reachedcp ");
    }
  }
  
  Serial.print(" new player: ");
  Serial.print(player);
  Serial.print(" * ");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setup() {
  Serial.print(" setup()  ");
  matrix.begin();
  matrix.setBrightness(64);

  spcY(player);
  setRandomLEDs();
  
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void loop() {
  Serial.print(" loop ");
  x = analogRead(x_pin);
  y = analogRead(y_pin);
  restartButton = digitalRead(SW_pin);

  Serial.print(" - in loop(): restartButton: ");
  Serial.print(restartButton);
  Serial.print(" - ");

  if (reachedLeds == 5) {
    Serial.print(" loop : reachedLeds = 5 ");
    setAll(0, 255, 0);
    delay(500);
    matrix.clear();
    matrix.show();
    restart();
  }

  if (restartButton != 1) {
    Serial.print(" loop: restartButton != 1");
    setAll(0, 0, 255);
    delay(500);
    matrix.clear();
    matrix.show();
    restart();
  }

  if ((x == 1023) || (x == 0) || (y == 1023) || (y == 0)) {
    if (y == 1023) {
      // left
      moveLeft();
      Serial.print(" loop: left ");
    }
    
    if (y == 0) {
      // right
      moveRight();
      Serial.print(" loop: right ");
    }
    
    if (x == 1023) {
      // down
      moveDown();
      Serial.print(" loop: down ");
    }
    
    if (x == 0) {
      // up
      moveUp();
      Serial.print(" loop: up ");      
    }
  }
  
  delay(150);
}

// 12th May 2017