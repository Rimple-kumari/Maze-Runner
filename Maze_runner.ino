#include<SoftwareSerial.h>
SoftwareSerial BTSerial(0,1);
#define D0 11 //ZK5AD Motor Driver pins.
#define D1 10
#define D2 6
#define D3 5
int command; //Int to store app command state.
int Speed = 255; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.
void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT); 
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  BTSerial.begin(9600);
}
void loop() {
  if (BTSerial.available() > 0) {
    
    command = BTSerial.read();
    Stop(); //Initialize with motors stoped.
    Serial.println(command);
    
    switch (command) {
      case 'F':
       
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
    }
    Speedsec = Turnradius;
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  }
}
void right() 
{

  analogWrite(D3, Speed);
  analogWrite(D1, Speed);
  analogWrite(D0, 0);
  analogWrite(D2, 0);
  
}
void left() {
  analogWrite(D2, Speed);
  analogWrite(D0, Speed);
  analogWrite(D3,  0);
  analogWrite(D1, 0);
}
void forward() {
    analogWrite(D0, Speed);
  analogWrite(D3, Speed);
  analogWrite(D1, 0);
  analogWrite(D2, 0);
  
  
}
void back() {
    analogWrite(D1, Speed);
  analogWrite(D2, Speed);
  analogWrite(D3, 0);
  analogWrite(D0, 0);
  


}
void forwardright() {
  analogWrite(D1, Speedsec);
  analogWrite(D3, Speed);
  analogWrite(D2, 0);
  analogWrite(D0, 0);
}
void backleft() {
  analogWrite(D1, Speed);
  analogWrite(D3, Speedsec);
  analogWrite(D2, 0);
  analogWrite(D0, 0);
}
void forwardleft() {
  analogWrite(D0, Speed);
  analogWrite(D3, Speedsec);
  analogWrite(D1,0);
  analogWrite(D2, 0);
}
void backright() {
  analogWrite(D0, Speedsec);
  analogWrite(D2, Speed);
  analogWrite(D1, 0);
  analogWrite(D3, 0);
}
void Stop() {
  analogWrite(D0, 0);
  analogWrite(D1, 0);
  analogWrite(D2, 0);
  analogWrite(D3, 0);
}
void brakeOn() {
  //Here's the future use: an electronic braking system!
  // read the pushbutton input pin:
  buttonState = command;
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == 'S') {
      if (lastButtonState != buttonState) {
        digitalWrite(D0, HIGH);
        digitalWrite(D1, HIGH);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, HIGH);
        delay(brakeTime);
        Stop();
      }
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
  }
}
void brakeOff() {
}