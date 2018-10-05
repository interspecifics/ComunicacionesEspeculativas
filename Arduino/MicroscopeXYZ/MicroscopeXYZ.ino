
#include <Stepper.h>
const int buttonFor = A4;
const int buttonBack = A5;

int led = 3;
int led2 = 2;
int pot = A0; //Light control
int Yout = A3;
int Xout = A2;

int delayval = 500; // delay for half a second

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 4 through 7:
Stepper myStepper1(stepsPerRevolution, 4, 5, 6, 7);
Stepper myStepper2(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper(stepsPerRevolution, 22, 23, 21, 20);


int buttonState1 = 0;
int buttonState2 = 0;
int potValue = 0;
int Xvalue = 0;
int Yvalue = 0;
int Xwrite;
int Ywrite;
int writeValue;
int stepCount = 0;         // number of steps the motor has taken



void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(buttonFor, INPUT);
  pinMode(buttonBack, INPUT);
  pinMode(pot, INPUT);
  pinMode(Yout, INPUT);
  pinMode(Xout, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);

  myStepper.setSpeed(30);
  myStepper1.setSpeed(60);
  myStepper2.setSpeed(60);
}

void loop() {

//_____________xy control

Xvalue = analogRead(Xout);
Yvalue = analogRead(Yout);

//____________ led brightness
potValue = analogRead(pot);
writeValue = (255./1023) *potValue;

analogWrite(led, writeValue);
analogWrite(led2, writeValue);


//---- x control

if (Xvalue > 770 && Xvalue < 850) {
  myStepper1.step(0);
  myStepper2.step(0);
Serial.println("myStepper1: stop");

}


if (Xvalue > 850 && Xvalue < 1023) {
   myStepper1.step(1);
   myStepper2.step(1);
       Serial.println(stepCount);
       stepCount++;
 }

else {
 myStepper1.step(0);
 myStepper2.step(0);
Serial.println("myStepper1: stop");
}


if (Xvalue < 400 && Xvalue < 600) {
  myStepper1.step(-1);
  myStepper2.step(-1);
       Serial.print("myStepper1: atras");
       stepCount++;
}


else {
 myStepper1.step(0);
  myStepper2.step(0);
Serial.println("myStepper1: stop");
}


 if (Xvalue > 770   && Xvalue < 850 ){
  myStepper1.step(0);
  myStepper2.step(0);
  Serial.println("myStepper1: stop");
}

/////// ------- Y control


if (Yvalue > 740 && Yvalue < 850) {
  myStepper2.step(0);
  myStepper1.step(0);
Serial.println("myStepper2: stop");

}


if (Yvalue > 850 && Yvalue < 1023) {
   myStepper2.step(1);
   myStepper1.step(-1);
       Serial.println(stepCount);
       stepCount++;
 }

else {
 myStepper2.step(0);
 myStepper1.step(0);
Serial.println("myStepper2: stop");
}


if (Yvalue < 400 && Xvalue < 600) {
  myStepper2.step(-1);
  myStepper1.step(1);
       Serial.print("myStepper2: atras");
       stepCount++;
}


else {
 myStepper2.step(0);
 myStepper1.step(0);
Serial.println("myStepper2: stop");
}


 if (Yvalue > 740   && Xvalue < 850 ){
  myStepper2.step(0);
   myStepper1.step(0);
  Serial.println("myStepper2: stop");
}


    buttonState1 = digitalRead(buttonFor);
    buttonState2 = digitalRead(buttonBack);

//_____________controller for number of stpes ( 400 steps per click )


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
        myStepper.step(0);
        Serial.println("stop");
      }


//___________controller for number of stpes ( 1 step per click )


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
