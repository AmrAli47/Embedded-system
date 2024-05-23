const int LeftMotorForward = 7; 
const int LeftMotorBackward = 6; 
const int RightMotorForward = 5; 
const int RightMotorBackward = 4; 
#define LED 13 
int command; //Int to store app command state. 
int Speed = 204; // 0 - 255. 
int Speedsec; 
int buttonState = 0; 
int lastButtonState = 0; 
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will 
malfunction if this is higher than int Speed. 
int brakeTime = 45; 
int brkonoff = 1; //1 for the electronic braking system, 0 for normal. 
void setup() { 
pinMode(RightMotorForward, OUTPUT); 
pinMode(LeftMotorForward, OUTPUT); 
pinMode(LeftMotorBackward, OUTPUT); 
pinMode(RightMotorBackward, OUTPUT); 
//Set the LED pin. 
Serial.begin(9600);  //Set the baud rate to your Bluetooth module. 
} 
void loop() { 
if (Serial.available() > 0) { 
command = Serial.read(); 
Stop(); //Initialize with motors stoped. 
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
void forward() { 
digitalWrite(LeftMotorForward, HIGH); 
digitalWrite(RightMotorForward, HIGH); 
digitalWrite(LeftMotorBackward, LOW); 
digitalWrite(RightMotorBackward, LOW);  
} 
void back() { 
digitalWrite(LeftMotorBackward, HIGH); 
digitalWrite(RightMotorBackward, HIGH); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorForward, LOW); 
} 
void left() { 
digitalWrite(LeftMotorBackward, HIGH); 
digitalWrite(RightMotorBackward, LOW);   
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorForward, LOW); 
} 
void right() { 
digitalWrite(LeftMotorBackward, LOW); 
digitalWrite(RightMotorForward, HIGH); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
} 
void forwardleft() { 
digitalWrite(LeftMotorBackward, HIGH); 
digitalWrite(RightMotorForward, HIGH); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
} 
void forwardright() { 
digitalWrite(LeftMotorBackward, LOW); 
digitalWrite(RightMotorForward, LOW); 
digitalWrite(LeftMotorForward, HIGH); 
digitalWrite(RightMotorBackward, HIGH); 
} 
void backright() { 
digitalWrite(LeftMotorBackward, HIGH); 
digitalWrite(RightMotorForward, HIGH); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
} 
void backleft() { 
digitalWrite(LeftMotorBackward, LOW); 
digitalWrite(RightMotorForward, LOW); 
digitalWrite(LeftMotorForward, HIGH); 
digitalWrite(RightMotorBackward, HIGH); 
} 
void Stop() { 
digitalWrite(RightMotorForward, LOW); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
digitalWrite(LeftMotorBackward, LOW); 
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
digitalWrite(LeftMotorForward, HIGH); 
digitalWrite(RightMotorForward, HIGH); 
digitalWrite(LeftMotorBackward, HIGH); 
digitalWrite(RightMotorBackward, HIGH);  
delay(brakeTime); 
} 
Stop(); 
} 
// save the current state as the last state, 
//for next time through the loop 
lastButtonState = buttonState; 
} 
} 
void brakeOff() { 
}