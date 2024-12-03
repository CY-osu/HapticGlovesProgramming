#include <Adafruit_NeoPixel.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define ledPin 8
#define numPixels 1

Adafruit_NeoPixel rgbLED(numPixels, ledPin, NEO_GRB + NEO_KHZ800);

// BLE service and characteristic UUIDs
#define SERVICE_UUID        "81ca0651-4ef2-4862-9f74-0509985682b8"
#define CHARACTERISTIC_UUID "cba1d466-344c-4be3-ab3f-189f80dd7518"

// Declare handleCommand function here so it is visible to MyCallbacks
void handleCommand(char command);

// Callback to handle incoming BLE data
class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();
    if (value.length() > 0) {
      char command = value[0];  // Get the first character of the received data
      handleCommand(command);   // Process the command
    }
  }
};

// Callback to handle connection and disconnection events
class ServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("Client connected.");
  }

  void onDisconnect(BLEServer* pServer) {
    Serial.println("Client disconnected. Restarting advertising...");
    // Restart advertising when the client disconnects
    BLEDevice::startAdvertising();
  }
};

void setup() {
  Serial.begin(9600);
  rgbLED.begin();
  rgbLED.show();

  // Initialize BLE server
  BLEDevice::init("ESP32_Server");
  BLEServer *pServer = BLEDevice::createServer();

  // Set server callbacks to monitor connections
  pServer->setCallbacks(new ServerCallbacks());

  // Create BLE service and characteristic
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());  // Set the callback to handle data received
  pService->start();

  // Start advertising the BLE service
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();
  Serial.println("ESP32 Server is ready and advertising.");
}

void loop() {
  // No need to do anything in the loop since the BLE callback handles events
}

// Define handleCommand function
void handleCommand(char command) {
  Serial.print("Received command: ");
  Serial.println(command);
  if (command == '0') {
    rgbLED.setPixelColor(0, rgbLED.Color(0, 0, 0));  // Turn off the LED
  } else if (command == '1') {
    rgbLED.setPixelColor(0, rgbLED.Color(255, 0, 0));  // Set LED to red
  } else if (command == '2') {
    rgbLED.setPixelColor(0, rgbLED.Color(0, 0, 255));  // Set LED to blue
  } else if (command == '3') {
    rgbLED.setPixelColor(0, rgbLED.Color(255, 255, 255));  // Set LED to white
  }
  rgbLED.show();  // Update the LED
}