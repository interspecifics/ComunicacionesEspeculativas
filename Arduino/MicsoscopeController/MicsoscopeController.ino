
#include <Stepper.h>
const int buttonFor = 9; 
const int buttonBack = 10;
const int buttonSteps = 11;

int led = 3;
int led2 = 12;
int pot = 0;

int delayval = 500; // delay for half a second

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 4 through 7:
Stepper myStepper(stepsPerRevolution, 4, 5, 6, 7);

int stepCount = 0;         // number of steps the motor has taken
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int potValue = 0;
int writeValue;


void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(buttonFor, INPUT);
  pinMode(buttonBack, INPUT);
  pinMode(buttonSteps, INPUT);
  pinMode(pot, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);

  myStepper.setSpeed(30);
}

void loop() {

//____________ led brightness 
potValue = analogRead(pot);
writeValue = (255./1023) *potValue;

analogWrite(led, writeValue);
analogWrite(led2, writeValue);

    
    buttonState1 = digitalRead(buttonFor);
    buttonState2 = digitalRead(buttonBack);
    buttonState3 = digitalRead(buttonSteps);

//_____________controller for number of stpes ( 400 steps per click )

    if (buttonState3 == LOW) {

      if (buttonState1 == LOW) {
        myStepper.step(stepsPerRevolution);
        Serial.print("adelante:");
        Serial.println(stepCount);
        stepCount++;
      }

      else {
        myStepper.step(0);
        Serial.println("stop");
      }

      if (buttonState2 == LOW) {
        myStepper.step(-stepsPerRevolution);
        Serial.print("atras:");
        Serial.println(stepCount);
        stepCount++;
      }

      else {
        myStepper.step(0);
        Serial.println("stop");
      }
    }

//___________controller for number of stpes ( 1 step per click )

    if (buttonState3 == HIGH) {

      if (buttonState1 == LOW) {
        myStepper.step(1);
        Serial.print("adelante:");
        Serial.println(stepCount);
        stepCount++;
      }


      else {
        myStepper.step(0);
        Serial.println("stop");
      }

      if (buttonState2 == LOW) {
        myStepper.step(-1);
        Serial.print("atras:");
        Serial.println(stepCount);
        stepCount++;
      }

      else {
        // turn LED off:
        myStepper.step(0);
        Serial.println("stop");
      }
    }
  }

