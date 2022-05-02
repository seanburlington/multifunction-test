

const int onButtonPin = 3;     // the number of the pushbutton pin
const int offButtonPin = 2;     // the number of the pushbutton pin

const int ledPin =  4;      // the number of the LED pin
const int servoPin = 13 ;
const int PIRpin = 7;

const int firePosition = 180;
const int armPosition = 100;


int movementDetected = 0;
int fireButtonState = 0;
int armButtonState = 0;

#include <Servo.h>



bool armed = false;
Servo myservo;  // create servo object to control a servo


void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP); // detect movement via pin 7
    

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  // ensure LED is off
  digitalWrite(ledPin, HIGH);
  
  // initialize the pushbutton pin as an input:
  pinMode(onButtonPin, INPUT);
  pinMode(offButtonPin, INPUT);
  
  arm();
}

void loop() {

    movementDetected = digitalRead(PIRpin);
    fireButtonState = digitalRead(onButtonPin);
    armButtonState = digitalRead(offButtonPin);
 

  if (armed && (movementDetected == HIGH || fireButtonState == LOW) ) {
    
    fire();
  } else {
    if (!armed && (armButtonState == LOW)) {
      arm();
    }
  }

}

void fire(){
   armed = false;
   Serial.println("FIRE");
   // turn LED off:
   digitalWrite(ledPin, HIGH); 
   myservo.attach(servoPin);
   myservo.write(firePosition);
   delay(1000);
   myservo.detach();
 
}

void arm(){
    Serial.println("ARM");

    myservo.attach(servoPin);  
    myservo.write(armPosition);
    armed=true;
    delay(100);
    myservo.detach();
    delay(5000); // 5 seconds to get out of range
   //    turn LED on:
    digitalWrite(ledPin, LOW);
}
