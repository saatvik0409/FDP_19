/*Obstacle avoidance robot with three ultrasonic sensors
 * https://srituhobby.com
 */
//Include the motor driver library
//Define the sensor pins

//Set the speed of the motors
/*Obstacle avoidance robot with three ultrasonic sensors
 * https://srituhobby.com
 */
#define S1Trig A4
#define S2Trig A2
#define S3Trig A0
#define S1Echo A5
#define S2Echo A3
#define S3Echo A1
//Set the speed of the motors
#define Speed 160

#define ena 5
#define in1 6
#define in2 7
#define in3 8
#define in4 9
#define enb 10

bool var1m1 = true;
bool var2m1 = false ;

bool var1m2 = true;
bool var2m2= false;

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
  int leftSensor = sensorOne();
  int rightSensor = sensorThree();
  
// Check the distance using the IF condition
//  while (leftSensor <=20 && rightSensor<=20){
//    leftSensor = sensorOne();
//    rightSensor = sensorThree();
//    left();
//  }
  while (25 >= centerSensor) {
    centerSensor = sensorTwo();
    leftSensor = sensorOne();
    rightSensor = sensorThree();
    if (leftSensor > rightSensor) {
      left();
      Serial.println("Left");
    } 
    if (leftSensor <= rightSensor) {
      right();
      Serial.println("Right");
    }
  }
  while (leftSensor <= 20 ){
    leftSensor = sensorOne();
    right();
    Serial.println("Right Only");
  }

  while (rightSensor <= 20 ){
    rightSensor = sensorThree();
    left();
    Serial.println("Left Only");
  }
  Serial.println("Forward");
  forward();
  delay(50);
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
void right() {
  digitalWrite(in1,var1m1);
  digitalWrite(in2,var2m1);
  digitalWrite(in3,var2m2);
  digitalWrite(in4,var1m2);
}
void left() {
  digitalWrite(in1,var2m1);
  digitalWrite(in2,var1m1);
  digitalWrite(in3,var1m2);
  digitalWrite(in4,var2m2);
}
