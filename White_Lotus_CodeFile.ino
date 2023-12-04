#include <Servo.h>

Servo pullupBar, hiddenDoor, moon, fakeWall;  

// defines input and output pins
const int whiteLEDPin = 11;
const int pullupPin = 7;
const int eclipsePin = 8;
const int wallPin = 4;
const int whiteLEDs = 12;
const int redLEDs = 3;

// defines input values for digital reading
int whiteLEDPinVal, pullupPinVal, eclipsePinVal, wallPinVal;

// defines starting positions for servos
int barPos = 20;
int doorPos = 0;
int moonPos = 120;
int wallPos = 175;

// booleans for whether or not a circuit is complete
bool whiteLEDCircuit = false;
bool pullupCircuit = false;
bool doorCircuit = false;
bool moonCircuit = false;
bool redLEDCircuit = false;
bool wallCircuit = false;

// booleans for whether an interaction has been completed already
bool whiteLEDsDone = false;
bool pullupsDone = false;
bool doorDone = false;
bool moonDone = false;
bool wallDone = false;



void setup() {
  // input pins
  pinMode(whiteLEDPin, INPUT);
  pinMode(pullupPin, INPUT);
  pinMode(eclipsePin, INPUT);
  pinMode(wallPin, INPUT);

  // output led pins
  pinMode(whiteLEDs, OUTPUT);
  pinMode(redLEDs, OUTPUT);

  // output servo pins
  pullupBar.attach(6);
  hiddenDoor.attach(9); 
  moon.attach(5);
  fakeWall.attach(10);
  
  // writes starting positions onto servos
  pullupBar.write(barPos);
  hiddenDoor.write(doorPos);
  moon.write(moonPos);
  fakeWall.write(wallPos);

  // starts with red LEDs off
  digitalWrite(redLEDs, LOW);
}

void loop() {

  // detects if circuit to turn on white LEDs is complete
  // (AKA if Iroh has stepped on the first circle)
  whiteLEDPinVal = digitalRead(whiteLEDPin);

  // if circuit is complete, makes white LED circuit boolean true
  if (whiteLEDPinVal == HIGH) {
    whiteLEDCircuit = true;
  }

  // if circuit boolean is true and white LEDs haven't already been turned
  // on, turns them on and marks interaction as "done"
  if (whiteLEDCircuit == true && whiteLEDsDone == false) {
    whiteLEDsOn();
    whiteLEDsDone = true;
  }
  
  // detects if circuit to trigger pullups is complete
  // (AKA if Iroh has stepped on the second circle under the pullup bar)
  pullupPinVal = digitalRead(pullupPin);

  // if he's stepped on the circuit & the white LEDs are done,
  // makes pullup circuit boolean true
  if (pullupPinVal == HIGH) {
    if (whiteLEDsDone == true) {
      pullupCircuit = true;
    }
  }

  // if circuit boolean is true and pullups haven't been done yet,
  // triggers pullups and marks interaction as done
  if (pullupCircuit == true && pullupsDone == false) {
    pullupsDone = true;
    doPullups();
  }

  // detects if circuit to trigger eclipse is complete
  // (AKA if Buff Iroh has stepped on the 1st rectangle)
  eclipsePinVal = digitalRead(eclipsePin);

  // if circuit is complete & the wall/door has already spun around,
  // makes moon circuit boolean true
  if (eclipsePinVal == HIGH) {
    if (doorDone == true) {
      moonCircuit = true;
    }
  }

  // if moon circuit boolean is true & the eclipse hasn't happened yet,
  // triggers eclipse & marks interaction as done
  if (moonCircuit == true && moonDone == false) {
    moonDone = true;
    eclipse();
  }


  // after the red LEDs turn on at the end of the eclipse, fades
  // red leds at varying brightnesses to simulate fire flickering
  // and allows for detection of the final interaction to knock
  // the wall over
  while (redLEDCircuit) {
    // detects if circuit to knock wall down is complete
    // (AKA if Buff Iroh has stepped on the second rectangle)
    wallPinVal = digitalRead(wallPin);
    // if circuit is complete and eclipse is done, sets wall
    // circuit boolean to true
    if (wallPinVal == HIGH) {
      if (moonDone == true) {
        wallCircuit = true;
      }
    }

    // if wall circuit boolean is true & wall hasn't
    // been knocked down yet, knocks down wall and
    // marks as done
    if (wallCircuit == true && wallDone == false) {
      wallDone = true;
      knockWall();
    }
    // flickers red LEDs to make fire effect
    // b1 = randomized lower brightness
    float b1 = random(5,150);
    // b2 = randomized higher brightness
    float b2 = random(180, 255);
    // fades from low to high brightness and back
    for (int i = b1; i <= b2; i += 8) {
      analogWrite(redLEDs, i);
      delay(15);
    }
    for (int i = b2; i>= b1; i -= 8) {
      analogWrite(redLEDs, i);
      delay(15);
    }
  }
}

// function to turn white LEDs on
void whiteLEDsOn() {
  digitalWrite(whiteLEDs, HIGH);
}

// function to trigger pull-ups
void doPullups() {
  // does 5 pullups by looping 5 times
  for (int i = 0; i < 5; i++) {

    // moves servo gradually from position 20 to 48 & back
    for (barPos = 20; barPos <= 48; barPos += 1) {
      pullupBar.write(barPos);
      delay(35);
    }
    delay(80);
    for (barPos = 48; barPos >= 20; barPos -= 1) { 
      pullupBar.write(barPos);             
      delay(35);                      
    }
  }
  // slight delay before spinning door
  delay(500);
  // triggers door spin and marks interaction as done
  doorDone = true;
  openHiddenDoor();
}

// function to spin hidden door
void openHiddenDoor() {
  // spins 180 degrees
  for (doorPos = 0; doorPos <= 180; doorPos += 1) { 
    hiddenDoor.write(doorPos);     
    delay(5);                             
  }
}

// function to trigger eclipse
void eclipse() {
  // gradually moves moon to cover sun
  for (moonPos = 120; moonPos >= 88; moonPos -= 2 ) {
    moon.write(moonPos);
    delay(80);
  }
  // turns on red LEDs
  redLEDCircuit = true;
  // turns off white LEDs
  digitalWrite(whiteLEDs, LOW);
}

// function that knocks down wall
void knockWall() {
  for (wallPos = 180; wallPos >=90; wallPos -= 1) {
    fakeWall.write(wallPos);
  }
}
