
/*modes:
 * Autopilot - Green -> 0x80BF20DF
 * ManualDrive - Red -> 0x80BF916E
 * DriverAssist - Blue -> 0x156561C7
*/


/*DIRECTIONAL CONTROLS
 * LEFT  || 0x27D869D
 * RIGHT || 0xB8301249
 * FORWARD || 0x2EE908BF
 * BACK  ||  0x80C88747
*/

#include <IRremote.h>
const int RECEIVE_PIN = 4;

int AUTO_PILOT_PIN = 9;
int MANUAL_DRIVE_PIN = 8;
int DRIVER_ASSIST_PIN = 10;

int trigPin = 40;
int echoPin = 36;

int buzzer = 28;

int In1 = 6;
int In2 = 7;
int In3 = 5;
int In4 = 3;

int toggleState = 0;

IRrecv irrecv(RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(AUTO_PILOT_PIN, OUTPUT);
  pinMode(MANUAL_DRIVE_PIN, OUTPUT);
  pinMode(DRIVER_ASSIST_PIN, OUTPUT);
  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  pinMode(buzzer, OUTPUT);

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

}



void loop() {
  if(irrecv.decode(&results)){
    if (results.value == 0x80BF837C){
      if (toggleState == 0){
          digitalWrite(MANUAL_DRIVE_PIN, HIGH);
          toggleState = 1;
          
          //forward
          if(results.value == 0x80BF53AC){
                digitalWrite(MANUAL_DRIVE_PIN, HIGH);
                toggleState = 1;
                  digitalWrite(In1, LOW);
                  digitalWrite(In2, HIGH);
                  digitalWrite(In3, LOW);
                  digitalWrite(In4, HIGH);
          }  
          //back
          else if(results.value == 0x80BF4BB4){
              if (toggleState == 0){
                digitalWrite(MANUAL_DRIVE_PIN, HIGH);
                toggleState = 1;
                  digitalWrite(In1, LOW);
                  digitalWrite(In2, HIGH);
                  digitalWrite(In3, LOW);
                  digitalWrite(In4, HIGH);
              }else{
                digitalWrite(MANUAL_DRIVE_PIN, LOW);
                toggleState = 0;
                digitalWrite(In1, LOW);
                digitalWrite(In2, LOW);
                digitalWrite(In3, LOW);
                digitalWrite(In4, LOW);
            }
            }
          //left
           else if(results.value == 0x80BF9966){
              if (toggleState == 0){
                digitalWrite(MANUAL_DRIVE_PIN, HIGH);
                toggleState = 1;
                digitalWrite(In1, LOW);
                digitalWrite(In2, LOW);
                digitalWrite(In3, HIGH);
                digitalWrite(In4, LOW);
              }else{
                digitalWrite(MANUAL_DRIVE_PIN, LOW);
                toggleState = 0;
                digitalWrite(In1, LOW);
                digitalWrite(In2, LOW);
                digitalWrite(In3, LOW);
                digitalWrite(In4, LOW);
            }
            }
          //right
           else if(results.value == 0x80BF837C){
             if (toggleState == 0){
              digitalWrite(MANUAL_DRIVE_PIN, HIGH);
              toggleState = 1;
              digitalWrite(In1, HIGH);
              digitalWrite(In2, LOW);
              digitalWrite(In3, LOW);
              digitalWrite(In4, LOW);
            }else{
              digitalWrite(MANUAL_DRIVE_PIN, LOW);
              toggleState = 0;
              digitalWrite(In1, LOW);
              digitalWrite(In2, LOW);
              digitalWrite(In3, LOW);
              digitalWrite(In4, LOW);
            }
        }
      else{
        digitalWrite(MANUAL_DRIVE_PIN, LOW);
        toggleState = 0;
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
      }
      
      }}

    else if(results.value == 0x80BF20DF){
      if (toggleState == 0){
          digitalWrite(AUTO_PILOT_PIN, HIGH);
          toggleState = 1;
          digitalWrite(trigPin,LOW);
          delay(2);
          digitalWrite(trigPin,HIGH);
          delay(10);
          digitalWrite(trigPin,LOW);
  
          int duration=pulseIn(echoPin,HIGH);
          int distance= duration*0.017;
  
            if(distance > 20){
               digitalWrite(In1, HIGH);
               digitalWrite(In2, LOW);
               digitalWrite(In3, HIGH);
               digitalWrite(In4, LOW);
            }
            else {
              digitalWrite(In1, LOW);
              digitalWrite(In2, LOW);
              digitalWrite(In3, LOW);
              digitalWrite(In4, LOW);
  
              digitalWrite(buzzer, HIGH);
              delay(90);
              digitalWrite(buzzer, LOW);
              delay(90);
              delay(1000);
              digitalWrite(In1, LOW);
              digitalWrite(In2, HIGH);
              digitalWrite(In3, LOW);
              digitalWrite(In4, HIGH);
              delay(300);
              digitalWrite(In1, LOW);
              digitalWrite(In2, LOW);
              digitalWrite(In3, LOW);
              digitalWrite(In4, LOW);
              delay(1000);
              
              if(random(0, 2) == 0) {
                digitalWrite(In1, LOW);
                digitalWrite(In2, LOW);
                digitalWrite(In3, HIGH);
                digitalWrite(In4, LOW);
              } else {
                digitalWrite(In1, HIGH);
                digitalWrite(In2, LOW);
                digitalWrite(In3, LOW);
                digitalWrite(In4, LOW);
              }
                delay(500);
                digitalWrite(In1, LOW);
                digitalWrite(In2, LOW);
                digitalWrite(In3, LOW);
                digitalWrite(In4, LOW);
                delay(700);
            }
            }
        else{
          digitalWrite(AUTO_PILOT_PIN, LOW);
          toggleState = 0;
          digitalWrite(In1, LOW);
          digitalWrite(In2, LOW);
          digitalWrite(In3, LOW);
          digitalWrite(In4, LOW);
        }
        }
        else{
        digitalWrite(In1, LOW);
        digitalWrite(In2, LOW);
        digitalWrite(In3, LOW);
        digitalWrite(In4, LOW);
        }

  }
}
  
