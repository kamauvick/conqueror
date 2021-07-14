#include <IRremote.h>
const int RECEIVE_PIN = 4;

int AUTO_PILOT_PIN = 9;
int MANUAL_DRIVE_PIN = 8;
int DRIVER_ASSIST_PIN = 10;


int In1 = 6;
int In2 = 7;
int In3 = 5;
int In4 = 3;

int enA = 30;
int enB = 32;


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
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(AUTO_PILOT_PIN, OUTPUT);
  pinMode(MANUAL_DRIVE_PIN, OUTPUT);
  pinMode(DRIVER_ASSIST_PIN, OUTPUT);

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

     pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    digitalWrite(enA,HIGH);
    digitalWrite(enB,HIGH);
}

void loop() {
  if(irrecv.decode(&results)){
    switch(results.value){
      case 0xFFE01F: //Forward
         if (toggleState == 0){
          digitalWrite(AUTO_PILOT_PIN, HIGH);
          toggleState = 1;
          goForward();
        }else{
          digitalWrite(AUTO_PILOT_PIN, LOW);
          toggleState = 0;
          justStop();
        }
        break;
        

      case 0xFFA857: //Backward
        if (toggleState == 0){
          digitalWrite(MANUAL_DRIVE_PIN, HIGH);
          toggleState = 1;
          goBackward();
        }else{
          digitalWrite(MANUAL_DRIVE_PIN, LOW);
          toggleState = 0;
          justStop();
        }
        break;
        
      case 0xFF6897://Left
        if (toggleState == 0){
          digitalWrite(DRIVER_ASSIST_PIN, HIGH);
          toggleState = 1;
          goLeft();
        }else{
          digitalWrite(DRIVER_ASSIST_PIN, LOW);
          toggleState = 0;
          justStop();
        }
        break;

        case 0xFF9867://Right
        if (toggleState == 0){
          digitalWrite(DRIVER_ASSIST_PIN, HIGH);
          toggleState = 1;
          goRight();
        }else{
          digitalWrite(DRIVER_ASSIST_PIN, LOW);
          toggleState = 0;
          justStop();
        }
        break;
      
      }
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}

  
//Drive Controls
void goForward() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}
void goBackward() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void justStop() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void goRight() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void goLeft() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}
