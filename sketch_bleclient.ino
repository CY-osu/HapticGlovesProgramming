#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>

#define SERVICE_UUID        "81ca0651-4ef2-4862-9f74-0509985682b8"
#define CHARACTERISTIC_UUID "cba1d466-344c-4be3-ab3f-189f80dd7518"

BLEClient* pClient = nullptr;
BLERemoteCharacteristic* pRemoteCharacteristic = nullptr;

// Server MAC address (replace with the correct address of your server)
BLEAddress serverAddress("f0:f5:bd:90:2a:9e");
// Reconnection interval in milliseconds
const int RECONNECT_INTERVAL = 5000;
unsigned long lastReconnectAttempt = 0;

// Callback function to handle notifications from the server
void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    Serial.print("Notification received: ");
    Serial.write(pData, length);
    Serial.println();
}

// Function to connect to the BLE server
bool connectToServer() {
  Serial.println("Attempting to connect to server...");

  // Create a new BLE client if not already initialized
  if (pClient == nullptr) {
    pClient = BLEDevice::createClient();
  }

  // Try to connect to the server
  if (!pClient->connect(serverAddress)) {
    Serial.println("Failed to connect to server");
    return false;
  }
  Serial.println("Connected to server");

  // Get the service
  BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
  if (pRemoteService == nullptr) {
    Serial.println("Failed to find the service UUID");
    pClient->disconnect();
    return false;
  }

  // Get the characteristic
  pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.println("Failed to find the characteristic UUID");
    pClient->disconnect();
    return false;
  }

  // Register for notifications if supported
  if (pRemoteCharacteristic->canNotify()) {
    pRemoteCharacteristic->registerForNotify(notifyCallback);
  }

  Serial.println("Client setup complete");
  return true;
}

void setup() {
  Serial.end();
  Serial.begin(9600);
  if (Serial.available()) {
    Serial.println("Serial communication successful!");
  } else {
    Serial.println("Serial communication failed...");
  }
  Serial.println("Starting BLE Client...");

  // Initialize BLE
  BLEDevice::init("ESP32_Client");

  // Initial connection attempt
  if (!connectToServer()) {
    Serial.println("Initial connection failed. Will retry...");
  }
}

void loop() {
  // Check if the client is connected to the server
  if (!pClient->isConnected()) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastReconnectAttempt > RECONNECT_INTERVAL) {
      lastReconnectAttempt = currentMillis;
      if (connectToServer()) {
        Serial.println("Reconnected to server");
      } else {
        Serial.println("Reconnection failed");
      }
    }
    return;  // Skip sending commands while disconnected
  }

  // Send commands to the server
  char command;
  if (Serial.available() > 0) {
    command = Serial.read();
    Serial.print("Sending command: ");
    Serial.println(command);

    if (pRemoteCharacteristic != nullptr && pRemoteCharacteristic->canWrite()) {
      pRemoteCharacteristic->writeValue(command);  // Send command to server
      delay(1000);  // Adjust delay as needed
    }
  }
}
