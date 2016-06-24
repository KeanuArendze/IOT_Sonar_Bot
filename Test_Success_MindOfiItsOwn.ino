#define FULL_SPEED 255
#define LEFT_WHEELS 1
#define RIGHT_WHEELS 2

#define trigPin 7
#define echoPin 6
//motor A connected between A01 and A02
//motor B connected between B01 and B02

const int BACKWARD = 0;
const int FORWARD = 1 ; 

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

void setup() {
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int getDistance() {

  long duration, distance;

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) / 29.1;

  Serial.println(distance); 

  return distance;

  

//  if (distance >= 200 || distance <= 0) {
//    Serial.println("Out of range");
//    Serial.println(distance);
//  }
//  else {
//    Serial.print(distance);
//    Serial.println(" cm");
//    return distance;
//  }

  //return -1;
}

//////////////////////////////////////////////////////

void loop() {

  check();

}

//////////////////////////////////////////////////////

void check() {

  objectCheck();

}

//////////////////////////////////////////////////////

void objectCheck() {

  delay(100);

  int dist = getDistance();

  if (dist > 50) {

    Drive();

  } else {

    move(1, 0, BACKWARD); // stop motors
    move(2, 0, BACKWARD);

    delay(100);// 5 second delay 

    int distLeft = checkLeft();

    origin('L');

    delay(500);

    int distRight = checkRight();

    delay(500);

    origin('R');

    delay(500);

    char direction = distanceCalculation(distRight, distLeft);

    switch (direction) {

      case 'L':

        moveLeft();

        break;

      case 'R':

        moveRight();

        break;

      default:

        reverse();

        break;


    }
  }

}

//////////////////////////////////////////////////////

int checkLeft() {

  delay(500);

  reverse();

  move(2, 0, FORWARD);

  delay(500);
  
  move(1, 0, BACKWARD);
  move(2, 0, BACKWARD);

  int distLeft = getDistance();

  return distLeft;

}

//////////////////////////////////////////////////////

int checkRight() {

  delay(500);

  move(1, 0, BACKWARD);
  move(2, 0, BACKWARD);

  delay(1000);

  move(1, 175, FORWARD);

  //move(2, 0, BACKWARD);

  delay(800);
  
  move(1, 0, BACKWARD);
  move(2, 0, BACKWARD);

  int distRight = getDistance();

  return distRight;

}

//////////////////////////////////////////////////////

void origin(char direction) {

  delay(500);

  // check which way it turns first to determine which way to reverse.

  switch (direction) {

    case 'L':

      // if checkLeft() is called

      move(2, 175, BACKWARD);

      delay(500);
    
    move(1, 0, BACKWARD);
      move(2, 0, BACKWARD);

      break;

    case 'R':

      // if checkRight is to be called

      move(1, 175, BACKWARD);

      delay(500);
    
      move(1, 0, BACKWARD);
      move(2, 0, BACKWARD);
      
      break;

  }

}

//////////////////////////////////////////////////////

char distanceCalculation(int distLeft, int distRight) {

  delay(500);

  if (distLeft > distRight) {

    return 'L';

  } else {

    return 'R';

  }

  //else if(distLeft == distRight){

  //return 'B';

  // }


}

//////////////////////////////////////////////////////

void moveLeft() {

  delay(500);

  move(2, 255, FORWARD);//CHANGED IT NOW

  delay(500);

  move(1, 0,BACKWARD);
  move(1, 0,BACKWARD);

  move(2, 255, FORWARD);
  
  Drive();

  

}

//////////////////////////////////////////////////////

void moveRight() {

 delay(500);

  move(1, 255, FORWARD);

  delay(500);

  move(2, 0,BACKWARD);
  move(2, 0,BACKWARD);

  move(1, 255, FORWARD);
  
  Drive();

}

////////////////////////////////////////////////////// :)

void Drive() {

  move(1, 255, FORWARD);
  move(2, 255, FORWARD);


}

/////////////////////////////////////////////////////

void reverse() {

    delay(500);

    move(1, 175, BACKWARD);
    move(2, 175, BACKWARD);

    delay(500);

  //check();

}

//////////////////////////////////////////////////////

void move(int motor, int speed, int direction) {
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if (motor == 1) {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  } else {
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop() {
  //enable standby
  digitalWrite(STBY, LOW);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Test 1.0










