//AGV Robot 
// Motor A pins (enableA = enable motor, pinA1 = forward, pinA2 = backward)
int IN3 = 26;
int IN4 = 27;
//Motor B pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int IN1 = 14;
int IN2 = 12;
int enableA =21;
int enableB =22;
int sensorPin[5] = {34, 35, 32, 33, 25};  //ESP32 sensor Pin
int sensor[5] = {0, 0, 0, 0, 0}; 
int speed =45;
int distance =0;
const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2 = 1;
const int ledChannel3 = 2;
const int ledChannel4 = 3;
const int resolution = 8;
int dutyCycleA=255;
int dutyCycleB=200;

void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); //motorA left
  pinMode(IN2, OUTPUT);  
  pinMode(IN3, OUTPUT); // motor B  right
  pinMode(IN4, OUTPUT); // motor B
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(IN1, ledChannel1);
  ledcAttachPin(IN2, ledChannel2);
  ledcAttachPin(IN3, ledChannel3);
  ledcAttachPin(IN4, ledChannel4);

}

void loop()
{

//  enableMotors();
 // analogWrite(enableA, 120);  // ปรับค่าความเร็วของหุ่นยนต์
 // analogWrite(enableB, 120);  // ปรับค่าความเร็วของหุ่นยนต์a
  for (int j=0;j<5;j++){
  sensor[j] = analogRead(sensorPin[j]);
  }
  for(int i=0;i<5;i++){
     Serial.print(sensor[i]); Serial.print(" ");
  }Serial.println("");
  if ((sensor[0] > 3000) && (sensor[1] > 3000) && (sensor[2] < 3000) && (sensor[3] > 3000) && (sensor[4] > 3000))
    {forward(speed,dutyCycleA);}
  else if ((sensor[0] > 3000) && (sensor[1] > 3000) && (sensor[2] > 3000) && (sensor[3] < 3000) && (sensor[4] > 3000))
    {distance =30;  turnRight(speed-distance,dutyCycleB); }
  else if ((sensor[0] > 3000) && (sensor[1] > 3000) && (sensor[2] > 3000) && (sensor[3] < 3000) && (sensor[4] < 3000))
    {distance =25;  turnRight(speed-distance,dutyCycleB); }
  else if ((sensor[0] > 3000) && (sensor[1] > 3000) && (sensor[2] > 3000) && (sensor[3] > 3000) && (sensor[4] < 3000))
    {distance = 20; turnRight(speed-distance,dutyCycleB);}
  else if ((sensor[0] > 3000) && (sensor[1] > 3000) && (sensor[2] < 3000) && (sensor[3] < 3000) && (sensor[4] < 3000))
    {distance = 20; turnRight(speed-distance,dutyCycleB);}
  else if ((sensor[0] > 3000) && (sensor[1] < 3000) && (sensor[2] > 3000) && (sensor[3] > 3000) && (sensor[4] > 3000))
    {distance =30;  turnLeft(speed-distance,dutyCycleB);}
  else if ((sensor[0] < 3000) && (sensor[1] < 3000) && (sensor[2] > 3000) && (sensor[3] > 3000) && (sensor[4] > 3000))
    {distance =25; turnLeft(speed-distance,dutyCycleB);}
  else if ((sensor[0] < 3000) && (sensor[1] > 3000) && (sensor[2] > 3000) && (sensor[3] > 3000) && (sensor[4] > 3000))
    {distance =20;  turnLeft(speed-distance,dutyCycleB);}
  else if ((sensor[0] < 3000) && (sensor[1] < 3000) && (sensor[2] < 3000) && (sensor[3] > 3000) && (sensor[4] > 3000))
    {distance =20;  turnLeft(speed-distance,dutyCycleB);}
  else 
     if ((sensor[0] < 3000) || (sensor[1] < 3000) || (sensor[2] < 3000) || (sensor[3] < 3000)|| (sensor[4] < 3000))
    {distance =40;  turnRight(speed-distance,dutyCycleB);
    //coast(30);
    }
    
    coast(5);
    //brake(20);

}

//Define high-level H-bridge commands



void forward(int time, int dutyCycleA)
{
  motorAForward( dutyCycleA);
  motorBForward( dutyCycleA);
   Serial.println(" Forward");
  delay(time);
}

void backward(int time, int dutyCycleA)
{
  motorABackward(dutyCycleA);
  motorBBackward(dutyCycleA);
   Serial.println(" Backward");
  delay(time);
}

void turnLeft(int time,int dutyCycleB)
{
  //motorABackward();
  motorBForward(dutyCycleB);
   Serial.println(" Left");
  delay(time);
}

void turnRight(int time, int dutyCycleB)
{
  motorAForward(dutyCycleB);
  //motorBBackward();
   Serial.println(" Right");
  delay(time);
}

void coast(int time)
{
  motorACoast();
  motorBCoast();
   Serial.println(" Coast");
  delay(time);
}

void brake(int time)
{
  motorABrake();
  motorBBrake();
   Serial.println(" Break");
  delay(time);
}
//Define low-level H-bridge commands



//motor A controls
void motorAForward(int dutyCycleA)
{
  //digitalWrite(IN2, LOW);
   ledcWrite(ledChannel2, dutyCycleA);
  //digitalWrite(IN1, HIGH);
  ledcWrite(ledChannel1, 0);
  //analogWrite(IN1,pwma);

  Serial.print(" A Forward");
}

void motorABackward(int dutyCycleA)
{
  //digitalWrite(IN1, LOW);
  ledcWrite(ledChannel2, 0);
  ledcWrite(ledChannel1, dutyCycleA);

  //digitalWrite(IN2, HIGH);
  //analogWrite(IN2,pwma);
  Serial.print(" A Backward");
}

//motor B controls
void motorBForward(int dutyCycleB)
{
  //digitalWrite(IN3, LOW);
  ledcWrite(ledChannel3, 0);
  ledcWrite(ledChannel4, dutyCycleB);
  //analogWrite(IN3,pwmb);
  //digitalWrite(IN4, HIGH);
   Serial.print(" B Forward");
}

void motorBBackward(int dutyCycleB)
{
  //digitalWrite(IN3, HIGH);
  ledcWrite(ledChannel3, dutyCycleB);
  ledcWrite(ledChannel4, 0);
  //digitalWrite(IN4, LOW);
  //analogWrite(IN4,pwmb);
   Serial.print(" B Backward");
}

//coasting and braking
void motorACoast()
{
 // digitalWrite(IN1, LOW);
  //digitalWrite(IN2, LOW);
  ledcWrite(ledChannel1, 255);
  ledcWrite(ledChannel2, 255);
   Serial.print(" A coast");
}

void motorABrake()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
   Serial.print(" A Break");
}

void motorBCoast()
{
  //digitalWrite(IN3, LOW);
  ledcWrite(ledChannel4, 255);
  //digitalWrite(IN4, LOW);
  ledcWrite(ledChannel3, 255);
   Serial.print(" B Coast");
}

void motorBBrake()
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

   Serial.print(" B Break");
}