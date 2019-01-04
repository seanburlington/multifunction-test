/*
  Based on     8x8 LED Matrix MAX7219 Example 01

   by Dejan Nedelkovski, www.HowToMechatronics.com

   Based on the following library:
   GitHub | riyas-org/max7219  https://github.com/riyas-org/max7219

   Modified to use timers instead fo delays, and merde with the arduino button example

   This means that the display updates and buttons still work.
*/

#include <MaxMatrix.h>

int DIN = 12;   // DIN pin of MAX7219 module
int CLK = 10;   // CLK pin of MAX7219 module
int CS = 11;    // CS pin of MAX7219 module
int maxInUse = 1;


MaxMatrix m(DIN, CS, CLK, maxInUse); 

char A[] = {8, 8,
            B00000000,
            B00000000,
            B01111110,
            B00010001,
            B00010001,
            B01111110,
            B00000000,
            B00000000
           };

char B[] = {8, 8,
            B00000000,
            B00000000,
            B01111111,
            B01001001,
            B01001001,
            B00110110,
            B00000000,
            B00000000
           };

char O[] = {8, 8, B00000000, B00000000, B00111110, B01000001, B01000001, B00111110, B00000000, B00000000};           

char smile01[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10010101,
                  B10100001,
                  B10100001,
                  B10010101,
                  B01000010,
                  B00111100
                 };
char smile02[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10010101,
                  B10010001,
                  B10010001,
                  B10010101,
                  B01000010,
                  B00111100
                 };
char smile03[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10100101,
                  B10010001,
                  B10010001,
                  B10100101,
                  B01000010,
                  B00111100
                 };





char *message[] = {B, O, B, smile01};

                 // constants won't change. They're used here to set pin numbers:
const int onButtonPin = 2;     // the number of the pushbutton pin
const int offButtonPin = 3;     // the number of the pushbutton pin

const int ledPin =  9;      // the number of the LED pin
int onButtonState = 0;
int offButtonState = 0;
int lightState =0;

unsigned long timer = 0;
int count = 0;

// servo 

#include <Servo.h>

const int servoPin = 13 ;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position



void setup() {

  Serial.begin(9600); 

  // led matrix
  m.init(); // MAX7219 initialization
  m.setIntensity(8); // initial led matrix intensity, 0-15




    

  // LED on/off
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  // initialize the pushbutton pin as an input:
  pinMode(onButtonPin, INPUT);
  pinMode(offButtonPin, INPUT);


}

void loop() {
  doDisplay();
  actOnButton();
  if (lightState == 1) {
    move();
  }

}


void doDisplay(){
  // only update once per second
  if (millis() - timer < 1000){
    return;
  }

  m.writeSprite(0, 0, message[count]);  
  Serial.print(count);
  Serial.print("\t");
  Serial.print(timer);
  Serial.print("\n");

  timer = millis();
  count ++;
  if (count > 4){
    count = 0;
  }
  
}

void move(){
 
myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

void actOnButton() {
  onButtonState = digitalRead(onButtonPin);
  offButtonState = digitalRead(offButtonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (onButtonState == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    lightState = 1;
  } else if(offButtonState == LOW) {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    lightState = 0;
  }
}


  /*
  // Seting the LEDs On or Off at x,y or row,column position
  m.setDot(6,2,true); 
  delay(1000);
  m.setDot(6,3,true);
  delay(1000);
  m.clear(); // Clears the display
  for (int i=0; i<8; i++){
    m.setDot(i,i,true);
    delay(300);
  }
  m.clear();
  // Displaying the character at x,y (upper left corner of the character)  
  m.writeSprite(2, 0, A);
  delay(1000);

  m.writeSprite(2, 0, B);
  delay(1000);

  m.writeSprite(0, 0, smile01);
  delay(1000);
  
  m.writeSprite(0, 0, smile02);
  delay(1000);
  
  m.writeSprite(0, 0, smile03);
  delay(1000);
  
  for (int i=0; i<8; i++){
    m.shiftLeft(false,false);
    delay(300);
  }
  m.clear();
  */
