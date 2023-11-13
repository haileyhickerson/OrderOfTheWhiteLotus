#include <Servo.h>

Servo pullupBar, hiddenDoor, moon, fakeWall;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int barPos = 0;
int doorPos = 0;
int moonPos = 0;
int wallPos = 0;

bool pullupCircuit = false;
bool doorCircuit = false;
bool moonCircuit = false;
bool wallCircuit = false;

bool pullupsDone = false;
bool doorDone = false;
bool moonDone = false;
bool wallDone = false;

void setup() {
  pullupBar.attach(6);
  hiddenDoor.attach(9); 
  
  pullupBar.write(barPos);
  hiddenDoor.write(doorPos);

}

void loop() {
  if (pullupCircuit == true && pullupsDone == false) {
    pullupsDone = true;
    doPullups();
  }
}

void doPullups() {
  // pull-up bar
  for (int i = 0; i < 5; i++) {
    for (barPos = 0; barPos <= 180; barPos += 1) {
      pullupBar.write(barPos);
      delay(5);
    }
    for (barPos = 180; barPos >= 0; barPos -= 1) { 
      pullupBar.write(barPos);             
      delay(5);                      
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
    delay(15);                       
  }
}
