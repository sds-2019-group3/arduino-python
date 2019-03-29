#include <OneWire.h>
#include <DallasTemperature.h>

const int soundSensor = 8;
const int tempSensor = 3;

int soundRead = 0;

int temp = 1;
int sound = 1;

const long fiveMinutes = 5 * 60 * 1000UL;
long lastSampleTime;

OneWire oneWire(tempSensor);
DallasTemperature sensors(&oneWire);
DeviceAddress sensorDeviceAddress;

// the setup function runs once when you press reset or power the board
void setup() {
  // Initialise digital pin for soundSensor
  pinMode(soundSensor, INPUT);
  
  sensors.begin();
  sensors.getAddress(sensorDeviceAddress, 0);
  sensors.setResolution(sensorDeviceAddress, 10);

  // Initialise Serial communication (baud rate)
  lastSampleTime = millis() - fiveMinutes;
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  //Check Serial
  char request = Serial.read();
  if (request == '1') {
    Serial.write(sound);
  }
  if (request == '2') {
    Serial.write(temp);
  }

  // Get new time
  long now = millis();
  if (digitalRead(soundSensor) == HIGH) {
    soundRead += 1;
  }
  now = millis();
  // Check if 5 minutes have passed
  if (now - lastSampleTime >= fiveMinutes) {
    // Set last sample time
    lastSampleTime = millis();
    if (soundRead > 100) {
      sound = 2;
    }
    if (soundRead >= 40 && soundRead <= 100) {
      sound = 1;
    }
    if (soundRead < 40) {
      sound = 0;
    }
    soundRead = 0;

    // Work out average temp over 10 readings
    float avTemp = 0.0f;
    for(int i = 0; i < 25; i++)
    {
      sensors.requestTemperatures();
      avTemp += sensors.getTempCByIndex(0);
      delay(100);
    }
    avTemp = avTemp/25;
    if (avTemp >= 22) {
      temp = 2;
    }
    if (avTemp < 22 && avTemp > 18) {
      temp = 1;
    }
    if (avTemp <= 18) {
      temp = 0;
    }
  }
  delay(500);
}

 