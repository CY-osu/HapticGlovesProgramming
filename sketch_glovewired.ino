#include <Adafruit_NeoPixel.h>

#define ledPin 8
#define numPixels 1

Adafruit_NeoPixel rgbLED(numPixels, ledPin, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rgbLED.begin();
  rgbLED.show();
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.println("Set up!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.print(command);
    if (command == '0') {
      rgbLED.setPixelColor(0, rgbLED.Color(0, 0, 0));
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    } else if (command == '1') {
      rgbLED.setPixelColor(0, rgbLED.Color(255, 0, 0));
      digitalWrite(6, HIGH);
    } else if (command == '2') {
      rgbLED.setPixelColor(0, rgbLED.Color(0, 0, 255));
      digitalWrite(5, HIGH);
    }
    rgbLED.show();
    delay(500);
  }

}