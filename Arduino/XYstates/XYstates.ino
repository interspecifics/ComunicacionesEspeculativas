  int analogValue = A3;   
  int analogValue1 = A2; 

void setup() {

  Serial.begin(9600);
}

void loop() {

  analogValue = analogRead(3);
  analogValue1 = analogRead(2);
 
  


  Serial.print(analogValue, DEC);         
  Serial.print("\t A:");              
  Serial.print(analogValue1, DEC);    
  Serial.print("\t B:");                 
  Serial.println();                 

  // delay 10 milliseconds before the next reading:
  delay(10);
}
