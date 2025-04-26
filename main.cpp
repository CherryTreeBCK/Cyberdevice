/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 40
#define TFT_CS 37
#define TFT_RST 46
#define TFT_MISO 45         
#define TFT_MOSI 42           
#define TFT_CLK 41 

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

String messages[16];
int message_index = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
 
  tft.begin();
  tft.fillScreen(BLACK);
}


void loop(void) {
  Serial.println("Please enter your chat: ");
  
  while (Serial.available() == 0) {
  }

  String input = Serial.readString();

  int hours = (millis() / 3600000) % 24;
  int minutes = (millis() / 60000) % 60;
  int decaSeconds = (millis()/ 10000) % 10;
  int seconds = (millis()/1000) % 10;
  String timestamp = "(" + String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes) + ":" + String(decaSeconds) + String(seconds) + ") ";
  messages[message_index] = timestamp + input;
  message_index++;
  unsigned long start = micros();
  tft.setCursor(0, 0);
  
  if (message_index > 15) {
    message_index = 15;
    for (int i = 0; i < 15; i++)
      messages[i] = messages[i + 1];
  }

  for (int i = 0; i < message_index; i++) {
    tft.setTextColor(BLUE);  
    tft.print(messages[i].substring(0, 9)); // Print timestamp in blue
    tft.setTextColor(WHITE);  
    tft.println(messages[i].substring(9)); // Print message in white
  }
}
