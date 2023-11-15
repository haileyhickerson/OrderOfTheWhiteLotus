#include <Servo.h>

Servo pullupBar, hiddenDoor, moon, fakeWall;  // create servo object to control a servo
// twelve servo objects can be created on most boards
const int pullupPin = 7;
const int eclipsePin = 8;
const int wallPin = 4;
int pullupPinVal, eclipsePinVal, wallPinVal;

int barPos = 20;
int doorPos = 0;
int moonPos = 60;
int wallPos = 180;

bool pullupCircuit = false;
bool doorCircuit = false;
bool moonCircuit = false;
bool wallCircuit = false;

bool pullupsDone = false;
bool doorDone = false;
bool moonDone = false;
bool wallDone = false;

void setup() {

  pinMode(pullupPin, INPUT);
  pinMode(eclipsePin, INPUT);
  pinMode(wallPin, INPUT);

  pullupBar.attach(6);
  hiddenDoor.attach(9); 
  moon.attach(5);
  fakeWall.attach(10);
  
  pullupBar.write(barPos);
  hiddenDoor.write(doorPos);
  moon.write(moonPos);
  fakeWall.write(wallPos);

}

void loop() {
  pullupPinVal = digitalRead(pullupPin);
  if (pullupPinVal == LOW) {
  } else {
    pullupCircuit = true;
  }

  if (pullupCircuit == true && pullupsDone == false) {
    pullupsDone = true;
    doPullups();
  }

  eclipsePinVal = digitalRead(eclipsePin);

  if (eclipsePinVal == LOW) {
  } else {
    if (doorDone == true) {
      moonCircuit = true;
    }
  }

  if (moonCircuit == true && moonDone == false) {
    moonDone = true;
    eclipse();
  }

  wallPinVal = digitalRead(wallPin);

  if (wallPinVal == LOW) {
  } else {
    if (moonDone == true) {
      wallCircuit = true;
    }
  }

  if (wallCircuit == true && wallDone == false) {
    wallDone = true;
    knockWall();
  }
}


void doPullups() {
  // pull-up bar
  for (int i = 0; i < 5; i++) {
    for (barPos = 20; barPos <= 40; barPos += 1) {
      pullupBar.write(barPos);
      delay(35);
    }
    delay(80);
    for (barPos = 40; barPos >= 20; barPos -= 1) { 
      pullupBar.write(barPos);             
      delay(35);                      
    }
  }
  delay(500);
  doorDone = true;
  openHiddenDoor();
}

void openHiddenDoor() {
  // hidden door opens
  for (doorPos = 0; doorPos <= 180; doorPos += 1) { 
    hiddenDoor.write(doorPos);     
    delay(5);                             
  }
}

void eclipse() {
  for (moonPos = 60; moonPos <= 90; moonPos += 1 ) {
    moon.write(moonPos);
    delay(90);
  }
}

void knockWall() {
  for (wallPos = 180; wallPos >=90; wallPos -= 1) {
    fakeWall.write(wallPos);
  }
}
