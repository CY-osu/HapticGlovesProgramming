#include <Adafruit_NeoPixel.h>

#define ledPin 8
#define numPixels 1

Adafruit_NeoPixel rgbLED(numPixels, ledPin, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rgbLED.begin();
  rgbLED.show();
  Serial.println("Set up!");
}

//const int BUFFER_SIZE = 50;
//char buf[BUFFER_SIZE];

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("In loop!");
  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.print(command);
    if (command == '0') {
      rgbLED.setPixelColor(0, rgbLED.Color(0, 0, 0));
      //rgbLED.show();
    } else if (command == '1') {
      rgbLED.setPixelColor(0, rgbLED.Color(255, 0, 0));
      //rgbLED.show();
    } else if (command == '2') {
      rgbLED.setPixelColor(0, rgbLED.Color(0, 0, 255));
      //rgbLED.show();
    }
     else if (command == '3') {
      rgbLED.setPixelColor(0, rgbLED.Color(255, 255, 255));
      //rgbLED.show();
    }
    rgbLED.show();
    delay(500);
  }

}