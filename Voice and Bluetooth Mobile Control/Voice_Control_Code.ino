String voice; 
const int LeftMotorForward = 7; 
const int LeftMotorBackward = 6; 
const int RightMotorForward = 5; 
const int RightMotorBackward = 4; 
void backward() { 
digitalWrite(LeftMotorBackward, HIGH); 
digitalWrite(RightMotorBackward, HIGH); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorForward, LOW); 
delay(2000); 
digitalWrite(RightMotorForward, LOW); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
digitalWrite(LeftMotorBackward, LOW); 
} 
void forward() { 
digitalWrite(LeftMotorForward, HIGH); 
digitalWrite(RightMotorForward, HIGH); 
digitalWrite(LeftMotorBackward, LOW); 
digitalWrite(RightMotorBackward, LOW);  
delay(2000); 
digitalWrite(RightMotorForward, LOW); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
digitalWrite(LeftMotorBackward, LOW); 
} 
void right() { 
digitalWrite(LeftMotorBackward, LOW); 
digitalWrite(RightMotorForward, HIGH); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
delay(2000); 
digitalWrite(RightMotorForward, LOW); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
digitalWrite(LeftMotorBackward, LOW); 
} 
void left() { 
digitalWrite(LeftMotorBackward, HIGH); 
digitalWrite(RightMotorBackward, LOW);   
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorForward, LOW); 
delay(2000); 
digitalWrite(RightMotorForward, LOW); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
digitalWrite(LeftMotorBackward, LOW); 
} 
void stop() { 
digitalWrite(RightMotorForward, LOW); 
digitalWrite(LeftMotorForward, LOW); 
digitalWrite(RightMotorBackward, LOW); 
digitalWrite(LeftMotorBackward, LOW); 
} 
void setup() { 
Serial.begin(9600); 
pinMode(RightMotorForward, OUTPUT); 
pinMode(LeftMotorForward, OUTPUT); 
pinMode(LeftMotorBackward, OUTPUT); 
pinMode(RightMotorBackward, OUTPUT); 
} 
void loop() { 
while(Serial.available()) { 
delay(10); 
char c=Serial.read(); 
if(c=='#') 
{break; } 
voice += c; 
} 
if (voice.length() > 0) { 
Serial.println(voice); 
if (voice == "*forward") 
{forward() ; } 
else if (voice == "*backward") 
{backward() ; } 
else if (voice == "*left") 
{left() ; } 
else if (voice == "*right") 
{right() ; } 
else if (voice == "*stop") 
{stop() ; } 
voice=""; 
} 
} 