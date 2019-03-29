const int motSensor = 2;

int inUse = 0;
int moveCount = 0;

int val = 0;

const long fiveMinutes = 5 * 60 * 1000UL;
long lastSampleTime;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(motSensor, INPUT);
  Serial.begin(9600);

  lastSampleTime = millis();
}

// the loop function runs over and over again forever
void loop() {
  //Set up variables to record movement in last 5 minutes
  long now = millis();

  // Check if python request available
  String request = Serial.readString();
  if (request.equals("1")) {
    // Respond to python request
    Serial.println((String) inUse);
  } else {
    // Check last five minutes
    if (now - lastSampleTime < fiveMinutes) {
      // Check motion Sensor
      val = digitalRead(motSensor);
      if (val == HIGH) {
        moveCount += 1;
      }
    } else {
      // Evaluate whether room is in use (based on no. of movements in last 5 minutes)
      if (moveCount > 5) {
        inUse = 1;
      } else {
        inUse = 0;
      }
      lastSampleTime = millis();
    }
  }
}
