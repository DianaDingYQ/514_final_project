// #include <Arduino.h>
// #if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
// #include <WiFi.h>
// #elif defined(ESP8266)
// #include <ESP8266WiFi.h>
// #endif

// #include <FirebaseClient.h>
// #include <WiFiClientSecure.h>

// #define WIFI_SSID "UW MPSK"
// #define WIFI_PASSWORD "Rm3;#3Lu(?)"  // Replace with your network password

// #define DATABASE_SECRET "AIzaSyAimfBsx8NXkr8NP7I6Cn2wCmW-ydOMPDk"
// #define DATABASE_URL "https://esp32-firebase-demo-54e74-default-rtdb.firebaseio.com"

// #define MAX_WIFI_RETRIES 5 // Maximum number of WiFi connection retries

// WiFiClientSecure ssl;
// DefaultNetwork network;
// AsyncClientClass client(ssl, getNetwork(network));

// FirebaseApp app;
// RealtimeDatabase Database;
// AsyncResult result;
// LegacyToken dbSecret(DATABASE_SECRET);

// // Ultrasonic sensor pins
// const int trigPin = 10;
// const int echoPin = 9;
// const float soundSpeed = 0.034;

// // Power-saving strategy
// #define DEEP_SLEEP_DURATION 60  // Deep sleep time (seconds) -> Extended to save power
// #define LIGHT_SLEEP_DURATION 30 // Light sleep duration when idle
// #define DETECTION_INTERVAL 1000 // Sensor detection interval (milliseconds)
// #define UPLOAD_INTERVAL 30000   // Data upload interval (milliseconds) -> Reduced WiFi usage

// unsigned long lastDetectionTime = 0;
// unsigned long lastUploadTime = 0;
// bool objectDetected = false; // Whether an object is detected

// void connectToWiFi();
// void initFirebase();
// void sendDataToFirebase(float distance);
// float measureDistance();
// void enterDeepSleep();
// void enterLightSleep();

// void setup() {
//     Serial.begin(115200);
//     delay(500);

//     pinMode(trigPin, OUTPUT);
//     pinMode(echoPin, INPUT);

//     Serial.println("Device started, beginning object detection...");

//     unsigned long startTime = millis();
//     while (millis() - startTime < 3000) { // Initial run for stability
//         measureDistance();
//         delay(100);
//     }
// }

// void loop() {
//     float distance = measureDistance();

//     // Detect object (distance < 50cm) and update detection time
//     if (distance < 50) {
//         objectDetected = true;
//         lastDetectionTime = millis(); // Update last detection timestamp
//     } else if (objectDetected && millis() - lastDetectionTime > 60000) {
//         // If no object detected for 60 seconds, enter deep sleep
//         Serial.println("No object detected for 60 seconds, entering deep sleep...");
//         enterDeepSleep();
//     }

//     // Reduce data upload frequency (every 30 seconds)
//     if (objectDetected && millis() - lastUploadTime > UPLOAD_INTERVAL) {
//         connectToWiFi();
//         initFirebase();
//         sendDataToFirebase(distance);
//         lastUploadTime = millis();
//         WiFi.disconnect(true); // Disconnect WiFi to save power
//     }

//     // If idle for 30 seconds, enter light sleep instead of full deep sleep
//     if (!objectDetected && millis() - lastDetectionTime > LIGHT_SLEEP_DURATION * 1000) {
//         Serial.println("No object detected recently, entering light sleep...");
//         enterLightSleep();
//     }

//     delay(DETECTION_INTERVAL); // Lower detection frequency to save power
// }

// // Function to measure distance
// float measureDistance() {
//     digitalWrite(trigPin, LOW);
//     delayMicroseconds(2);
//     digitalWrite(trigPin, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(trigPin, LOW);

//     long duration = pulseIn(echoPin, HIGH);
//     float distance = duration * soundSpeed / 2;

//     Serial.print("Measured Distance: ");
//     Serial.print(distance);
//     Serial.println(" cm");
//     return distance;
// }

// // Function to connect to WiFi
// void connectToWiFi() {
//     Serial.println(WiFi.macAddress());
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//     Serial.println("Connecting to WiFi...");
//     int wifiCnt = 0;
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//         wifiCnt++;
//         if (wifiCnt > MAX_WIFI_RETRIES) {
//             Serial.println("WiFi connection failed");
//             ESP.restart();
//         }
//     }
//     Serial.println("\nWiFi connected");
//     Serial.print("IP Address: ");
//     Serial.println(WiFi.localIP());
// }

// // Function to initialize Firebase
// void initFirebase() {
//     Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);
//     ssl.setInsecure();

// #if defined(ESP8266)
//     ssl.setBufferSizes(1024, 1024);
// #endif

//     Serial.println("Initializing Firebase...");
//     initializeApp(client, app, getAuth(dbSecret));
//     app.getApp<RealtimeDatabase>(Database);
//     Database.url(DATABASE_URL);
//     client.setAsyncResult(result);
// }

// // Function to send data to Firebase
// void sendDataToFirebase(float distance) {
//     Serial.print("Uploading data: ");
//     Serial.print(distance);
//     Serial.println(" cm");

//     if (millis() - lastUploadTime > UPLOAD_INTERVAL || lastUploadTime == 0) {
//         lastUploadTime = millis();

//         String name = Database.push<number_t>(client, "/test/distance", number_t(distance));
//         if (client.lastError().code() == 0) {
//             Firebase.printf("Upload successful, data name: %s\n", name.c_str());
//         }
//     }
// }

// // Function to enter deep sleep
// void enterDeepSleep() {
//     Serial.println("Device entering deep sleep mode...");
//     WiFi.disconnect(true);
//     esp_sleep_enable_timer_wakeup(DEEP_SLEEP_DURATION * 1000000); // Convert to microseconds
//     esp_deep_sleep_start();
// }

// // Function to enter light sleep
// void enterLightSleep() {
//     Serial.println("Entering light sleep mode...");
//     esp_sleep_enable_timer_wakeup(LIGHT_SLEEP_DURATION * 1000000);
//     esp_light_sleep_start();
// }

#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
 
#include <FirebaseClient.h>
#include <WiFiClientSecure.h>
 
 
#define WIFI_SSID "UW MPSK"
#define WIFI_PASSWORD "Rm3;#3Lu(?" // Replace with your network password
 
#define DATABASE_SECRET "AIzaSyAimfBsx8NXkr8NP7I6Cn2wCmW-ydOMPDk" // Replace with your database URL
#define DATABASE_URL "https://esp32-firebase-demo-54e74-default-rtdb.firebaseio.com" // Replace with your API key
 
#define STAGE_INTERVAL 12000 // 12 seconds each stage
#define MAX_WIFI_RETRIES 5 // Maximum number of WiFi connection retries
 
WiFiClientSecure ssl;
DefaultNetwork network;
AsyncClientClass client(ssl, getNetwork(network));
 
FirebaseApp app;
RealtimeDatabase Database;
AsyncResult result;
LegacyToken dbSecret(DATABASE_SECRET);
 
int uploadInterval = 1000; // 1 seconds each upload
unsigned long sendDataPrevMillis = 0;
int count = 0;
// bool signupOK = false;
 
// HC-SR04 Pins
const int trigPin = 10;
const int echoPin = 9;
 
// Define sound speed in cm/usec
const float soundSpeed = 0.034;
 
// Select desired rate
#define UPLOAD_INTERVAL 500   // 2 Hz
// #define UPLOAD_INTERVAL 1000  // 1 Hz
// #define UPLOAD_INTERVAL 2000  // 0.5 Hz
// #define UPLOAD_INTERVAL 3000  // 0.333 Hz
//#define UPLOAD_INTERVAL 4000  // 0.25 Hz
 
void connectToWiFi();
void initFirebase();
void sendDataToFirebase(float distance);
float measureDistance();
 
void setup() {
    Serial.begin(115200);
    delay(500);
 
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
 
    Serial.println("Running for 12 seconds without doing anything...");
    delay(STAGE_INTERVAL);
 
    Serial.println("Measuring distance for 12 seconds...");
    unsigned long startTime = millis();
    while (millis() - startTime < STAGE_INTERVAL) {
        measureDistance();
        delay(100);
    }
 
    Serial.println("Turning on WiFi and measuring for 12 seconds...");
    connectToWiFi();
    startTime = millis();
    while (millis() - startTime < STAGE_INTERVAL) {
        measureDistance();
        delay(100);
    }
 
    Serial.println("Turning on Firebase and sending data...");
    initFirebase();
    startTime = millis();
    while (millis() - startTime < STAGE_INTERVAL) {
        float currentDistance = measureDistance();
        sendDataToFirebase(currentDistance);
        delay(100);
    }
 
    Serial.println("Going to deep sleep for 12 seconds...");
    WiFi.disconnect();
    esp_sleep_enable_timer_wakeup(STAGE_INTERVAL * 1000);
    esp_deep_sleep_start();
}
 
void loop() {
    // Empty since we are handling logic in setup()
}
 
float measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
 
    long duration = pulseIn(echoPin, HIGH);
    float distance = duration * soundSpeed / 2;
 
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
}
 
void connectToWiFi() {
    Serial.println(WiFi.macAddress());
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Connecting to WiFi...");
    int wifiCnt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        wifiCnt++;
        if (wifiCnt > MAX_WIFI_RETRIES) {
            Serial.println("WiFi connection failed");
            ESP.restart();
        }
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
 
void initFirebase() {
    Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);
    ssl.setInsecure();
 
#if defined(ESP8266)
    ssl.setBufferSizes(1024, 1024);
#endif
 
    Serial.println("Initializing Firebase...");
    initializeApp(client, app, getAuth(dbSecret));
    app.getApp<RealtimeDatabase>(Database);
    Database.url(DATABASE_URL);
    client.setAsyncResult(result);
}
 
void sendDataToFirebase(float distance) {
    if (millis() - sendDataPrevMillis > UPLOAD_INTERVAL || sendDataPrevMillis == 0) {
        sendDataPrevMillis = millis();
 
        Serial.print("Pushing float value... ");
        String name = Database.push<number_t>(client, "/test/distance", number_t(distance));
        if (client.lastError().code() == 0) {
            Firebase.printf("ok, name: %s\n", name.c_str());
            count++;
        }
    }
}