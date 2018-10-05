#include <Stepper.h>

int Yout = A3;
int Xout = A2;

// change this to the number of steps on your motor
#define STEPS 200
const int stepsPerRevolution = 200;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper myStepper1(stepsPerRevolution, 4, 5, 6, 7);
Stepper myStepper2(stepsPerRevolution, 8, 9, 10, 11);

int Xvalue = 0;
int Yvalue = 0;
int Xwrite;
int Ywrite;
int stepCount = 0;         // number of steps the motor has taken



void setup()
{
  pinMode(Yout, INPUT);
  pinMode(Xout, INPUT);
  Serial.begin(9600);
  Serial.println("Stepper test!");
  // set the speed of the motor to 30 RPMs
  myStepper1.setSpeed(60);
  myStepper2.setSpeed(60);
}

void loop()
{

  Xvalue = analogRead(Xout);
  Yvalue = analogRead(Yout);

 
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

}

