#include <LiquidCrystal.h>

#include <IRremote.h>
const int RECEIVE_PIN = 4;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int AUTO_PILOT_PIN = 9;
int MANUAL_DRIVE_PIN = 8;
int DRIVER_ASSIST_PIN = 10;


int In1 = 6;
int In2 = 7;
int In3 = 5;
int In4 = 3;

int ENA=11;
int ENB=12;

/*modes:
 * Autopilot - Green -> 0x873F3D2
 * ManualDrive - Red -> 0xDF2CA3D1
 * DriverAssist - Blue -> 0x156561C7
*/


/*DIRECTIONAL CONTROLS
 * LEFT  || 0x27D869D
 * RIGHT || 0xB8301249
 * FORWARD || 0x2EE908BF
 * BACK  ||  0x80C88747
*/

int toggleState = 0;

IRrecv irrecv(RECEIVE_PIN);
decode_results results;

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, Darion !");
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(AUTO_PILOT_PIN, OUTPUT);
  pinMode(MANUAL_DRIVE_PIN, OUTPUT);
  pinMode(DRIVER_ASSIST_PIN, OUTPUT);

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  pinMode(ENA,OUTPUT); //pwm
  pinMode(ENB,OUTPUT); //pwm
}

void loop() {
  if(irrecv.decode(&results)){
    switch(results.value){
      case 0x80BF53AC: //Forward
         if (toggleState == 0){
          digitalWrite(AUTO_PILOT_PIN, HIGH);
          toggleState = 1;
          goForward(100,80);
        }else{
          digitalWrite(AUTO_PILOT_PIN, LOW);
          toggleState = 0;
          justStop(100,77);
        }
        break;
        

      case 0x80BF4BB4: //Backward
        if (toggleState == 0){
          digitalWrite(MANUAL_DRIVE_PIN, HIGH);
          toggleState = 1;
          goBackward(100,77);
        }else{
          digitalWrite(MANUAL_DRIVE_PIN, LOW);
          toggleState = 0;
          justStop(100,77);
        }
        break;
        
      case 0x80BF9966://Left
        if (toggleState == 0){
          digitalWrite(DRIVER_ASSIST_PIN, HIGH);
          toggleState = 1;
          goLeft(100,120);
        }else{
          digitalWrite(DRIVER_ASSIST_PIN, LOW);
          toggleState = 0;
          justStop(100,77);
        }
        break;

        case 0x80BF837C://Right
        if (toggleState == 0){
          digitalWrite(DRIVER_ASSIST_PIN, HIGH);
          toggleState = 1;
          goRight(100,120);
        }else{
          digitalWrite(DRIVER_ASSIST_PIN, LOW);
          toggleState = 0;
          justStop(100,77);
        }
        break;
      
      }
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}

  
//Drive Controls
void goForward(int duration, int Speed) {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(ENA,Speed);
    
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(ENB,Speed);
  
  delay(duration);
}
void goBackward(int duration, int Speed) {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(ENA,Speed);
    
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  analogWrite(ENB,Speed);
  
  delay(duration);
}
void justStop(int duration, int Speed) {
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  analogWrite(ENA,Speed);
  
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  analogWrite(ENB,Speed);
  
  delay(duration);
}
void goRight(int duration, int Speed) {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  analogWrite(ENA,Speed);
    
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  analogWrite(ENB,Speed);
  
  delay(duration);
}
void goLeft(int duration, int Speed) {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  analogWrite(ENA,Speed);
  
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(ENB,Speed);
  
  delay(duration);
}
