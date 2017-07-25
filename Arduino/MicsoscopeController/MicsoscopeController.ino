#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


#include <Stepper.h>
const int buttonFor = 9;
const int buttonBack = 10;
int led = 3;
int pot = 0;
#define PIN            3
#define NUMPIXELS      1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 4, 5, 6, 7);

int stepCount = 0;         // number of steps the motor has taken
int buttonState1 = 0; 
int buttonState2 = 0; 
int potvalue = 0;


void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(buttonFor, INPUT);
  pinMode(buttonBack, INPUT);
  pinMode(pot, INPUT);
  pinMode(led, OUTPUT);

  myStepper.setSpeed(15);

  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(33,33,33)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
  
    delay(delayval); // Delay for a period of time (in milliseconds).
 //-------------------------------------------------------------------------
    
  buttonState1 = digitalRead(buttonFor);
  buttonState2 = digitalRead(buttonBack);

   if (buttonState1 == LOW) {     
       
     // step one step:
 myStepper.step(stepsPerRevolution);
  Serial.print("adelante:");
  Serial.println(stepCount);
  stepCount++;
  } 
  
  else {
    // turn LED off:
   myStepper.step(0);
   Serial.println("stop");
   
  }

if (buttonState2 == LOW) {     
       
     // step one step:
  myStepper.step(-stepsPerRevolution);
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

