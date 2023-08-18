long idleCounts = 999;
long counter = 0;
int laserLightPin = D5;
int laserSensePin = D6;
int tripActive = D4;
int testModePin = D3;

bool isOk = true;

// write here what should happen when the laser beam is interrupted
void triggerAlarm() { 
  digitalWrite(tripActive, HIGH);  // activate the alarm pin
}

void setup {
  pinMode(tripActive, OUTPUT);
  pinMode(laserLightPin, OUTPUT);
  pinMode(laserSensePin, INPUT);
  pinMode(testModePin, INPUT);

  digitalWrite(tripActive, LOW);   // deactivate the alarm pin
  digitalWrite(testModePin, LOW);  // deactivate the alarm pin
}


void loop {
  if (digitalRead(testModePin) != HIGH) {
    counter = (counter + 1) % (idleCounts + 1);
    if (counter == 0) { // time to take a measurement
      digitalWrite(laserLightPin, HIGH); // light on the laser
      isOk = digitalRead(laserSensePin) == HIGH; // did the sensor pick it up
    }
    digitalWrite(laserLightPin, LOW);
    if (isOk == false) {
      triggerAlarm();
    }
  }
  else { // test mode activated
    digitalWrite(laserLightPin, HIGH); // light on the laser
    delay(1000); // make sure to see the laser spot for longer periods
  }
}