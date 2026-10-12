// RP2040 Chip - test code
// Board: Use the Raspberry Pi Pico, this tells arduino ide to use the Earle Philhower RP2040 core
// Libraries: Adafruit GFX, Adafruit ST7735 and ST7789
//
// Tests each part, it's for YOU to make the actual games and fun stuff!
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// display (SPI0, SCK = 18, MOSI = 19)
#define TFT_CS    17
#define TFT_DC    20
#define TFT_RST   21
#define BACKLIGHT 22

// sound
#define AMP_ON  14
#define SPEAKER 15

// thumbstick
#define STICK_VCC   26
#define STICK_X     27
#define STICK_Y     28
#define STICK_GND   29
#define STICK_CLICK 10

// the 8 buttons are on GPIO2 to GPIO9
int buttons[8] = {2, 3, 4, 5, 6, 7, 8, 9};

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);  // USB
  Serial1.begin(9600);   // expansion header (TX = GPIO0, RX = GPIO1). add your own modules, like a gyro, gps, etc. 
  // buttons connect to ground, so use the pull-ups
  for (int i = 0; i < 8; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(STICK_CLICK, INPUT_PULLUP);
  // two pins are used as power and ground
  // swap them around if they don't work, not sure if this will work. 
  pinMode(STICK_VCC, OUTPUT);
  digitalWrite(STICK_VCC, HIGH);
  pinMode(STICK_GND, OUTPUT);
  digitalWrite(STICK_GND, LOW);

  // backlight for the tft
  pinMode(BACKLIGHT, OUTPUT);
  digitalWrite(BACKLIGHT, HIGH);

  // screen
  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("RP2040 Chip");

  // turn the amp on and play a startup beep
  pinMode(AMP_ON, OUTPUT);
  digitalWrite(AMP_ON, HIGH);
  tone(SPEAKER, 880, 200);

  Serial1.println("hello from the expansion header");
}

void loop() {
  // buttons: 1 = pressed
  tft.setCursor(10, 50);
  tft.print("Buttons: ");
  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttons[i]) == LOW) {
      tft.print("1");
    } else {
      tft.print("0");
    }
  }

  // thumbstick
  int x = analogRead(STICK_X);
  int y = analogRead(STICK_Y);

  tft.setCursor(10, 80);
  tft.print("X: ");
  tft.print(x);
  tft.print("    ");  // clears old digits

  tft.setCursor(10, 110);
  tft.print("Y: ");
  tft.print(y);
  tft.print("    ");

  // beep when the stick is clicked
  if (digitalRead(STICK_CLICK) == LOW) {
    tone(SPEAKER, 440, 100);
  }

  // also print the stick to the computer
  Serial.print(x);
  Serial.print(" ");
  Serial.println(y);

  delay(50);
}

// NOW GO MAKE YOUR OWN GAMES!!
