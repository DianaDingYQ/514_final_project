// #include <Arduino.h>
// #include <Wire.h>
// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEScan.h>
// #include <BLEAdvertisedDevice.h>
// #include <Stepper.h>

// #define COIL_A1 6  // GPIO6 (D6)
// #define COIL_A2 5  // GPIO5 (D5)
// #define COIL_B1 4  // GPIO4 (D4)
// #define COIL_B2 3  // GPIO3 (D3)

// // Stepper motor step sequence (full step mode)
// const int stepSequence[4][4] = {
//     {1, 0, 1, 0}, // Step 1
//     {0, 1, 1, 0}, // Step 2
//     {0, 1, 0, 1}, // Step 3
//     {1, 0, 0, 1}  // Step 4
// };

// #define STEPS_PER_REV 200  // Number of steps per full rotation
// #define STEP_DELAY 5        // Adjust speed (smaller = faster)
// #define DEG_PER_STEP (360.0 / STEPS_PER_REV)  // Degrees per step

// // === LED Setup ===
// #define LED_PIN 10  

// // === BLE UUIDs ===
// static BLEUUID serviceUUID("191e60c4-72c1-44b7-b3d1-230d0817fb3a");
// static BLEUUID charUUID("87654321-4321-6789-4321-fedcba987654");

// BLEAdvertisedDevice* targetDevice;
// BLEClient* pClient;
// BLERemoteCharacteristic* pRemoteCharacteristic;
// bool connected = false;
// String moistureBuffer = "";

// // === Notification Callback (Handles Incoming Data) ===
// void notifyCallback(BLERemoteCharacteristic* characteristic, uint8_t* data, size_t length, bool isNotify) {
//     String receivedChunk = "";
//     for (size_t i = 0; i < length; i++) {
//         receivedChunk += (char)data[i];
//     }

//     Serial.print("📡 Received Chunk: ");
//     Serial.println(receivedChunk);

//     moistureBuffer += receivedChunk;

//     // Extract the moisture percentage
//     int moistureIndex = moistureBuffer.indexOf("Moisture: ");
//     if (moistureIndex != -1) {
//         moistureIndex += 10;  // Move index to the start of the value
//         int percentIndex = moistureBuffer.indexOf("%", moistureIndex);
//         if (percentIndex != -1) {
//             String moistureValueStr = moistureBuffer.substring(moistureIndex, percentIndex);
//             float moistureValue = moistureValueStr.toFloat();
//             Serial.print("💧 Moisture Value: ");
//             Serial.print(moistureValue);
//             Serial.println("%");

//             // LED Control Logic
//             if (moistureValue < 30.0 || moistureValue > 70.0) {
//                 Serial.println("🚨 LED ON - Moisture Alert");
//                 digitalWrite(LED_PIN, HIGH);
//             } else {
//                 Serial.println("✅ LED OFF - Moisture Normal");
//                 digitalWrite(LED_PIN, LOW);
//             }

//             // **Stepper Motor Control (Map moisture 0-100% to steps 0-315)**
//             int stepTarget = map(moistureValue, 0, 100, 0, STEPPER_STEPS);
//             Serial.print("⚙️ Moving Stepper to Position: ");
//             Serial.println(stepTarget);

//             stepper.setSpeed(15);  // Adjust speed for smooth motion
//             stepper.step(stepTarget);  // Move stepper motor to the target position
//         }
//     }

//     moistureBuffer = "";
// }

// // === Connect to BLE Server ===
// bool connectToServer() {
//     Serial.println("🔗 Connecting to BLE server...");
//     pClient = BLEDevice::createClient();
//     if (!pClient->connect(targetDevice)) {
//         Serial.println("❌ Connection failed!");
//         return false;
//     }

//     BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
//     if (!pRemoteService) {
//         Serial.println("❌ Service not found!");
//         pClient->disconnect();
//         return false;
//     }

//     pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
//     if (!pRemoteCharacteristic) {
//         Serial.println("❌ Characteristic not found!");
//         pClient->disconnect();
//         return false;
//     }

//     if (pRemoteCharacteristic->canNotify()) {
//         pRemoteCharacteristic->registerForNotify(notifyCallback);
//         Serial.println("✅ Notifications enabled!");
//         return true;
//     }

//     return false;
// }

// // === Scan for BLE Server ===
// void scanForServer() {
//     BLEScan* pBLEScan = BLEDevice::getScan();
//     pBLEScan->setActiveScan(true);
//     BLEScanResults devices = pBLEScan->start(3);
//     for (int i = 0; i < devices.getCount(); i++) {
//         BLEAdvertisedDevice device = devices.getDevice(i);
//         if (device.haveServiceUUID() && device.isAdvertisingService(serviceUUID)) {
//             targetDevice = new BLEAdvertisedDevice(device);
//             Serial.println("✅ Server found!");
//             return;
//         }
//     }
//     Serial.println("🔄 Server not found, rescanning...");
// }

// // === Setup ===
// void setup() {
//     Serial.begin(115200);
    
//     pinMode(LED_PIN, OUTPUT);
//     digitalWrite(LED_PIN, LOW);

//     stepper.setSpeed(10);  // Set initial speed

//     BLEDevice::init("");
//     BLEDevice::setMTU(64);

//     scanForServer();
//     if (targetDevice) connected = connectToServer();
// }

// // === Loop ===
// void loop() {
//     if (!connected) scanForServer();
//     yield();
//     delay(2000);
// }

// #include <Arduino.h>
// #include <Wire.h>
// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEScan.h>
// #include <BLEAdvertisedDevice.h>

// // === Stepper Motor Setup (Using Your Exact Code) ===
// #define COIL_A1 6  // GPIO6 (D6)
// #define COIL_A2 5  // GPIO5 (D5)
// #define COIL_B1 4  // GPIO4 (D4)
// #define COIL_B2 3  // GPIO3 (D3)

// // Stepper motor step sequence (full step mode)
// const int stepSequence[4][4] = {
//     {1, 0, 1, 0}, // Step 1
//     {0, 1, 1, 0}, // Step 2
//     {0, 1, 0, 1}, // Step 3
//     {1, 0, 0, 1}  // Step 4
// };

// #define STEPS_PER_REV 200  // Steps per full rotation
// #define STEP_DELAY 5        // Adjust speed (smaller = faster)
// #define DEG_PER_STEP (360.0 / STEPS_PER_REV)  // Degrees per step

// // === LED Setup ===
// #define LED_PIN 10  

// // === BLE UUIDs ===
// static BLEUUID serviceUUID("191e60c4-72c1-44b7-b3d1-230d0817fb3a");
// static BLEUUID charUUID("87654321-4321-6789-4321-fedcba987654");

// BLEAdvertisedDevice* targetDevice;
// BLEClient* pClient;
// BLERemoteCharacteristic* pRemoteCharacteristic;
// bool connected = false;
// String moistureBuffer = "";

// // === Function to Rotate Stepper by a Specific Degree ===
// void rotateStepper(float degrees, bool reverse) {
//     int steps = degrees / DEG_PER_STEP;  // Convert degrees to steps
//     Serial.print("🔄 Rotating ");
//     Serial.print(degrees);
//     Serial.print(" degrees (");
//     Serial.print(steps);
//     Serial.println(" steps)");

//     unsigned long stepStart = millis(); // Track step timing

//     for (int i = 0; i < steps; i++) {  
//         for (int step = 0; step < 4; step++) {
//             int s = reverse ? (3 - step) : step; // Reverse direction if needed
//             digitalWrite(COIL_A1, stepSequence[s][0]);
//             digitalWrite(COIL_A2, stepSequence[s][1]);
//             digitalWrite(COIL_B1, stepSequence[s][2]);
//             digitalWrite(COIL_B2, stepSequence[s][3]);
            
//             // **Replace delay() with millis() check**
//             while (millis() - stepStart < STEP_DELAY) {
//                 yield();  // Allow BLE to process in background
//             }
//             stepStart = millis();
//         }
//     }
// }


// // === BLE Notification Callback ===
// void notifyCallback(BLERemoteCharacteristic* characteristic, uint8_t* data, size_t length, bool isNotify) {
//     String receivedChunk = "";
//     for (size_t i = 0; i < length; i++) {
//         receivedChunk += (char)data[i];
//     }

//     Serial.print("📡 Received Chunk: ");
//     Serial.println(receivedChunk);

//     moistureBuffer += receivedChunk;

//     // Extract moisture percentage
//     int moistureIndex = moistureBuffer.indexOf("Moisture: ");
//     if (moistureIndex != -1) {
//         moistureIndex += 10;  // Move index to the start of the value
//         int percentIndex = moistureBuffer.indexOf("%", moistureIndex);
//         if (percentIndex != -1) {
//             String moistureValueStr = moistureBuffer.substring(moistureIndex, percentIndex);
//             float moistureValue = moistureValueStr.toFloat();
//             Serial.print("💧 Moisture Value: ");
//             Serial.print(moistureValue);
//             Serial.println("%");

//             // === LED Control Logic ===
//             if (moistureValue < 30.0 || moistureValue > 70.0) {
//                 Serial.println("🚨 LED ON - Moisture Alert");
//                 digitalWrite(LED_PIN, HIGH);
//             } else {
//                 Serial.println("✅ LED OFF - Moisture Normal");
//                 digitalWrite(LED_PIN, LOW);
//             }

//             // === Stepper Motor Control ===
//             if (moistureValue < 30.0) {
//                 Serial.println("⬅️ Rotating Left 90 degrees (Too Dry)");
//                 rotateStepper(90, false);  // Rotate left 90°
//             } 
//             else if (moistureValue > 70.0) {
//                 Serial.println("➡️ Rotating Right 90 degrees (Too Wet)");
//                 rotateStepper(90, true);   // Rotate right 90°
//             } 
//             else {
//                 Serial.println("⏸️ Keeping Stepper Position (Optimal Moisture)");
//             }
//         }
//     }

//     moistureBuffer = "";  // Clear buffer after processing
// }

// // === Connect to BLE Server ===
// bool connectToServer() {
//     Serial.println("🔗 Connecting to BLE server...");
//     pClient = BLEDevice::createClient();
//     if (!pClient->connect(targetDevice)) {
//         Serial.println("❌ Connection failed!");
//         return false;
//     }

//     BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
//     if (!pRemoteService) {
//         Serial.println("❌ Service not found!");
//         pClient->disconnect();
//         return false;
//     }

//     pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
//     if (!pRemoteCharacteristic) {
//         Serial.println("❌ Characteristic not found!");
//         pClient->disconnect();
//         return false;
//     }

//     if (pRemoteCharacteristic->canNotify()) {
//         pRemoteCharacteristic->registerForNotify(notifyCallback);
//         Serial.println("✅ Notifications enabled!");
//         return true;
//     }

//     return false;
// }

// // === Scan for BLE Server ===
// void scanForServer() {
//     BLEScan* pBLEScan = BLEDevice::getScan();
//     pBLEScan->setActiveScan(true);
//     BLEScanResults devices = pBLEScan->start(3);
//     for (int i = 0; i < devices.getCount(); i++) {
//         BLEAdvertisedDevice device = devices.getDevice(i);
//         if (device.haveServiceUUID() && device.isAdvertisingService(serviceUUID)) {
//             targetDevice = new BLEAdvertisedDevice(device);
//             Serial.println("✅ Server found!");
//             return;
//         }
//     }
//     Serial.println("🔄 Server not found, rescanning...");
// }

// // === Setup ===
// void setup() {
//     Serial.begin(115200);

//     pinMode(COIL_A1, OUTPUT);
//     pinMode(COIL_A2, OUTPUT);
//     pinMode(COIL_B1, OUTPUT);
//     pinMode(COIL_B2, OUTPUT);
//     pinMode(LED_PIN, OUTPUT);
//     digitalWrite(LED_PIN, LOW);  // Ensure LED starts OFF

//     Serial.println("🚀 Stepper Motor & LED Ready!");

//     BLEDevice::init("");
//     BLEDevice::setMTU(64);

//     scanForServer();
//     if (targetDevice) connected = connectToServer();
// }

// // === Loop ===
// void loop() {
//     if (!connected) scanForServer();
//     yield();
//     delay(2000);
// }



#include <Arduino.h>
#include <Wire.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// === Stepper Motor Setup ===
#define COIL_A1 D6  // GPIO6
#define COIL_A2 D5  // GPIO5
#define COIL_B1 D4  // GPIO4
#define COIL_B2 D3  // GPIO3

// Step sequence for full-step mode
const int stepSequence[4][4] = {
    {1, 0, 0, 1},  // Step 1
    {1, 0, 1, 0},  // Step 2
    {0, 1, 1, 0},  // Step 3
    {0, 1, 0, 1}   // Step 4
};

#define STEPS_PER_REV 400  // Steps per full revolution (adjust as needed)
#define STEP_DELAY 15       // **Adjust step delay for smoother movement**
#define DEG_PER_STEP (360.0 / STEPS_PER_REV)  // Degrees per step
#define MAX_ANGLE 180.0  // **Maximum allowed angle**
#define MIN_ANGLE 0.0    // **Minimum allowed angle**

float currentAngle = 90;  // **Initial angle (starts at the midpoint)**
float targetAngle = 90;   // **Target angle for movement**
bool motorMoving = false;

// === LED Setup ===
#define LED_PIN 10  

// === BLE UUIDs ===
static BLEUUID serviceUUID("191e60c4-72c1-44b7-b3d1-230d0817fb3a");
static BLEUUID charUUID("87654321-4321-6789-4321-fedcba987654");

BLEAdvertisedDevice* targetDevice;
BLEClient* pClient;
BLERemoteCharacteristic* pRemoteCharacteristic;
bool connected = false;
String moistureBuffer = "";

// === Update the target angle based on moisture level ===
void updateTargetAngle(float moisture) {
    targetAngle = map(moisture, 0, 100, MIN_ANGLE, MAX_ANGLE);
    Serial.print("🎯 Target Angle: ");
    Serial.println(targetAngle);
}

// === Gradually move the stepper motor to the target angle ===
void moveStepperToTarget() {
    if (abs(targetAngle - currentAngle) < DEG_PER_STEP) {
        motorMoving = false;  // **Stop if the angle is very close**
        return;
    }

    motorMoving = true;
    bool reverse = (targetAngle < currentAngle);  // **Determine direction**
    float stepCount = abs(targetAngle - currentAngle) / DEG_PER_STEP;

    Serial.print("🔄 Moving ");
    Serial.print(reverse ? "Left " : "Right ");
    Serial.print(stepCount);
    Serial.println(" steps");

    for (int i = 0; i < stepCount; i++) {  
        for (int step = 0; step < 4; step++) {
            int s = reverse ? (3 - step) : step;
            digitalWrite(COIL_A1, stepSequence[s][0]);
            digitalWrite(COIL_A2, stepSequence[s][1]);
            digitalWrite(COIL_B1, stepSequence[s][2]);
            digitalWrite(COIL_B2, stepSequence[s][3]);
            delay(STEP_DELAY);
        }
    }

    currentAngle = targetAngle;  // **Update current angle**
    Serial.print("✅ Stepper now at: ");
    Serial.print(currentAngle);
    Serial.println(" degrees");

    // **Stop the motor to prevent vibration**
    digitalWrite(COIL_A1, LOW);
    digitalWrite(COIL_A2, LOW);
    digitalWrite(COIL_B1, LOW);
    digitalWrite(COIL_B2, LOW);
    motorMoving = false;
}

// === BLE Notification Callback ===
void notifyCallback(BLERemoteCharacteristic* characteristic, uint8_t* data, size_t length, bool isNotify) {
    String receivedChunk = "";
    for (size_t i = 0; i < length; i++) {
        receivedChunk += (char)data[i];
    }

    Serial.print("📡 Received Chunk: ");
    Serial.println(receivedChunk);

    moistureBuffer += receivedChunk;

    // Extract moisture percentage
    int moistureIndex = moistureBuffer.indexOf("Moisture: ");
    if (moistureIndex != -1) {
        moistureIndex += 10;  
        int percentIndex = moistureBuffer.indexOf("%", moistureIndex);
        if (percentIndex != -1) {
            String moistureValueStr = moistureBuffer.substring(moistureIndex, percentIndex);
            float moistureValue = moistureValueStr.toFloat();
            Serial.print("💧 Moisture Value: ");
            Serial.print(moistureValue);
            Serial.println("%");

            // === LED Control Logic ===
            if (moistureValue < 30.0 || moistureValue > 70.0) {
                Serial.println("🚨 LED ON - Moisture Alert");
                digitalWrite(LED_PIN, HIGH);
            } else {
                Serial.println("✅ LED OFF - Moisture Normal");
                digitalWrite(LED_PIN, LOW);
            }

            // === Update Stepper Target Angle ===
            updateTargetAngle(moistureValue);
        }
    }

    moistureBuffer = "";  // Clear buffer after processing
}

// === Connect to BLE Server ===
bool connectToServer() {
    Serial.println("🔗 Connecting to BLE server...");
    pClient = BLEDevice::createClient();
    if (!pClient->connect(targetDevice)) {
        Serial.println("❌ Connection failed!");
        return false;
    }

    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (!pRemoteService) {
        Serial.println("❌ Service not found!");
        pClient->disconnect();
        return false;
    }

    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (!pRemoteCharacteristic) {
        Serial.println("❌ Characteristic not found!");
        pClient->disconnect();
        return false;
    }

    if (pRemoteCharacteristic->canNotify()) {
        pRemoteCharacteristic->registerForNotify(notifyCallback);
        Serial.println("✅ Notifications enabled!");
        return true;
    }

    return false;
}

// === Scan for BLE Server ===
void scanForServer() {
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true);
    BLEScanResults devices = pBLEScan->start(3);
    for (int i = 0; i < devices.getCount(); i++) {
        BLEAdvertisedDevice device = devices.getDevice(i);
        if (device.haveServiceUUID() && device.isAdvertisingService(serviceUUID)) {
            targetDevice = new BLEAdvertisedDevice(device);
            Serial.println("✅ Server found!");
            return;
        }
    }
    Serial.println("🔄 Server not found, rescanning...");
}

// === Setup ===
void setup() {
    Serial.begin(115200);

    pinMode(COIL_A1, OUTPUT);
    pinMode(COIL_A2, OUTPUT);
    pinMode(COIL_B1, OUTPUT);
    pinMode(COIL_B2, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.println("🚀 Stepper Motor & LED Ready!");

    BLEDevice::init("");
    BLEDevice::setMTU(64);

    scanForServer();
    if (targetDevice) connected = connectToServer();
}

// === Loop ===
void loop() {
    if (!connected) scanForServer();
    if (!motorMoving) moveStepperToTarget();  // **Gradually adjust angle**
    yield();
    delay(1000);
}

