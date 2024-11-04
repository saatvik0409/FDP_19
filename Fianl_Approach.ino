
#define S1Trig A0
#define S2Trig A2
#define S3Trig A4
#define S1Echo A1
#define S2Echo A3
#define S3Echo A5
//Set the speed of the motors
#define Speed 160

#define ena 5
#define in1 6
#define in2 7
#define in3 8
#define in4 9
#define enb 10

float mul_factor = 1.10;
bool var1m1 = true;
bool var2m1 = false ;

bool var1m2 = true;
bool var2m2= false;

int left_count = 0;
int right_count = 0;

void setup(){
  Serial.begin(9600);
  //Set the Trig pins as output pins
  pinMode(S1Trig, OUTPUT);
  pinMode(S2Trig, OUTPUT);
  pinMode(S3Trig, OUTPUT);
  //Set the Echo pins as input pins
  pinMode(S1Echo, INPUT);
  pinMode(S2Echo, INPUT);
  pinMode(S3Echo, INPUT);
  //Set the speed of the motors

  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enb,OUTPUT);
  digitalWrite(ena,HIGH);
  digitalWrite(enb,HIGH);

}
void loop() {

  int centerSensor = sensorTwo();
  int rightSensor = sensorThree();
  int leftSensor = sensorOne();
  Serial.println("Here");
  Serial.print("Center Sensor : ");
  Serial.println(centerSensor);
  Serial.print("Right Sensor : ");
  Serial.println(rightSensor);
  Serial.print("Left Sensor : ");
  Serial.println(leftSensor);
  
  if (25 >= centerSensor) {

    if (left_count < right_count) {
      left(false);
      Serial.println("Left");
      forward();
      delay(mul_factor*500);
      rightSensor = sensorThree();
      while (rightSensor < 60){
        forward();
        rightSensor = sensorThree();
        delay(mul_factor*400);
      }
      forward();
      delay(mul_factor*500);
      right(true);
      forward();
      delay(mul_factor*1000);
    } 
    else if (right_count <= left_count) {
      right(false);
      forward();
      Serial.println("Right");
      delay(mul_factor*500);
      leftSensor = sensorOne();
      Serial.print("LEFT SENSOR READING : ");
      Serial.println(leftSensor);
      int checker = 20;
      while (leftSensor < 60){
        forward();
        leftSensor = sensorOne();
        delay(mul_factor*400);

      }
      forward();
      delay(mul_factor*500);
      left(true);
      forward();
      delay(mul_factor*1000);
    }
  }
  Serial.println("Forward");
  forward();
  
}

//Get the sensor values
int sensorOne() {
  //pulse output
  digitalWrite(S1Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(S1Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S1Trig, LOW);

  long t = pulseIn(S1Echo, HIGH);//Get the pulse
  int cm = t / 29 / 2; //Convert time to the distance
  return cm; // Return the values from the sensor
}

//Get the sensor values
int sensorTwo() {
  //pulse output
  digitalWrite(S2Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(S2Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S2Trig, LOW);

  long t = pulseIn(S2Echo, HIGH);//Get the pulse
  int cm = t / 29 / 2; //Convert time to the distance
  return cm; // Return the values from the sensor
}

//Get the sensor values
int sensorThree() {
  //pulse output
  digitalWrite(S3Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(S3Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S3Trig, LOW);

  long t = pulseIn(S3Echo, HIGH);//Get the pulse
  int cm = t / 29 / 2; //Convert time to the distance
  return cm; // Return the values from the sensor
}

/***Motor functions**/
void forward() {
  digitalWrite(in1,var1m1);
  digitalWrite(in2,var2m1); 
  digitalWrite(in3,var1m1);
  digitalWrite(in4,var2m2);
}



void right(bool counter) {
  int delay_var = 0;
  if (counter== false){
    right_count+=1;
    delay_var = 680;
  } else{
    delay_var = 650;
  }
  digitalWrite(in1,var2m1);
  digitalWrite(in2,var1m1);
  digitalWrite(in3,var1m2);
  digitalWrite(in4,var2m2);
  delay(mul_factor*delay_var);
}
void left(bool counter) {
  int delay_var = 0;
  if (counter== false){
    left_count+=1;
    delay_var = 550;
  } else{
    delay_var = 640;
  }
  digitalWrite(in1,var1m1);
  digitalWrite(in2,var2m1);
  digitalWrite(in3,var2m2);
  digitalWrite(in4,var1m2);
  delay(mul_factor*delay_var);
}
