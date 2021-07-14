#include <LiquidCrystal_I2C.h>

/*modes:
 * Autopilot - Green -> 0x873F3D2
*/

//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27, 16, 2);

int trigPin = 40;
int echoPin = 36;

int buzzer = 28;

int RS = 42;
int LS = 8;

int In1 = 6;
int In2 = 7;
int In3 = 5;
int In4 = 3;

int enA = 30;
int enB = 32;

boolean right_sensor_value;
boolean left_sensor_value;

String RS_VAL = "RIGHT IR SENSOR";
String LS_VAL = "LEFT IR SENSOR";


void setup() {
    Serial.begin(9600);
//    lcd.begin(16,2);

//    lcd.setCursor(0,0);
  
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
  
    pinMode(buzzer, OUTPUT);
  
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    pinMode(RS, INPUT);
    pinMode(LS, INPUT);

    digitalWrite(enA,HIGH);
    digitalWrite(enB,HIGH);

}

void loop() {  
  right_sensor_value = digitalRead(RS);
  left_sensor_value = digitalRead(LS);
  
  Serial.println(RS_VAL);
  Serial.println(right_sensor_value);
  Serial.println(LS_VAL);
  Serial.println(left_sensor_value);

  
  autoPilotMode(trigPin, echoPin);
}

int autoPilotMode(int trigPin, int echoPin){
  digitalWrite(trigPin,LOW);
  delay(2);
  digitalWrite(trigPin,HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);
  
  int duration=pulseIn(echoPin,HIGH);
  int distance= duration*0.017;



  if(distance > 50 && right_sensor_value == 0 &&  left_sensor_value == 0){
   goForward();
  } else {
//    lcd.print("Object detected.....");
    justStop();
    beep();
//    lcd.clear();
//    delay(200);
//    lcd.print("Slowing down..."); 
//    delay(300);
//    lcd.print("Auto Braking..."); 
//    delay(200);
//    lcd.clear();
    delay(1000);
//    lcd.clear();
//    lcd.print("Re-routing..."); 
    goBackward();
    
//    delay(1000);
//    lcd.clear();
    delay(300);
    justStop();
    delay(300);
    
    if(random(0, 2) == 0) {
      goLeft();
    } else {
      goRight();
    }
//    lcd.clear();
//    lcd.print("Re-routing..."); 
    delay(500);
//    lcd.clear();
    justStop();
    delay(1000);
  }
  
  delay(100);
  String indicator="Distance:";
  Serial.println(indicator);
  Serial.println(distance);
  
//  lcd.print(indicator);
//  lcd.print(distance);
  delay(500);
//  lcd.clear();
  
  return distance;
  }
 
/* Wheel Drive Functions */
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

//Object Detection Warning beeps
void beep(){
    digitalWrite(buzzer, HIGH);
    delay(90);
    digitalWrite(buzzer, LOW);
    delay(90);
    digitalWrite(buzzer, HIGH);
    delay(90);
    digitalWrite(buzzer, LOW);
    delay(90);
    digitalWrite(buzzer, HIGH);
    delay(90);
    digitalWrite(buzzer, LOW);
    delay(90);
}
