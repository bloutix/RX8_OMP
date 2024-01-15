
#include <Arduino.h>
#include <Stepper.h>

const int stepsPerRevolution = 32;  // change this to fit the number of steps per revolution
const int rolePerMinute = 22;         // Adjustable range of stepper is ?rpm?
int StepCount = 0;

// initialize the stepper library on pins:
Stepper myStepper(stepsPerRevolution, 33, 26, 25, 27);

const int OMPSensorSwitch = 12;

void setup(void) 
{
  myStepper.setSpeed(rolePerMinute);
  // initialize the serial port:
  Serial.begin(9600);
  // initialize the sensor pin as an input:
  pinMode(OMPSensorSwitch, INPUT); 
}  

void loop(void) 
{
 
  // 60 steps anticlockwise to set minimum oil output reference point:
    Serial.println("TESTING");
    Serial.println("go to minimum point -63step");
    myStepper.step(-63);
 
    Serial.println("Min Point OK");
  // One step at a time, increasing oil output setting:
  StepCount = 0;
 {
  //step motor a max of 60 steps clockwise, or until sensor goes HIGH
  while (digitalRead(OMPSensorSwitch) == LOW && StepCount < 61)
    {
    myStepper.step(1);
    StepCount = StepCount+1;
    Serial.println(StepCount);
    }
       
    //check for correct step range and that sensor switch has operated
    
    if (StepCount >= 53 && StepCount <= 61 && digitalRead(OMPSensorSwitch) == HIGH) 
    //PASS: stepcount within spec
      {
      //decrement StepCount by one as it has not been around the loop again yet
      StepCount = StepCount -1;

      Serial.println("PASS");         
      } 
    else  
    //FAIL: stepcount out of spec
      { 

      Serial.println("FAIL");        
      }
     
   //display step count
   Serial.print(StepCount); 
   Serial.println("Steps"); 

   //set all outputs low to stop current flow into coils
   digitalWrite(32, LOW);
   digitalWrite(33, LOW);
   digitalWrite(26, LOW);
   digitalWrite(27, LOW);
   //allow reult to display for 4 seconds
   delay(4000);
 } 
}
