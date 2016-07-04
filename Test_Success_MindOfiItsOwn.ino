#define FULL_SPEED 255
#define LEFT_WHEELS 1
#define RIGHT_WHEELS 2

#define trigPin 7
#define echoPin 6
//motor A connected between A01 and A02
//motor B connected between B01 and B02

const int BACKWARD = 1;
const int FORWARD = 0 ;

const int Indicator_Left = 2;
const int Indicator_Right = 4;


const int Buzz_Pin_13 = 13;

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

  pinMode(Indicator_Left, OUTPUT);
  pinMode(Indicator_Right, OUTPUT);
  pinMode(Buzz_Pin_13, OUTPUT);

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

    stop();

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

  for (int counter = 0; counter < 3; counter++) {

    digitalWrite(Indicator_Left, true);
    delay(500);
    digitalWrite(Indicator_Left, false);
    delay(800);
  }

  move(RIGHT_WHEELS, FULL_SPEED, FORWARD);
  move(LEFT_WHEELS, FULL_SPEED, BACKWARD);

  delay(500);

  stop();

  int distLeft = getDistance();

  return distLeft;

}

//////////////////////////////////////////////////////

int checkRight() {

  delay(500);

  stop();

  delay(1000);


  for (int counter = 0; counter < 3; counter++) {

    digitalWrite(Indicator_Right, true);
    delay(500);
    digitalWrite(Indicator_Right, false);
    delay(800);
  }

  move(LEFT_WHEELS, FULL_SPEED, FORWARD);
  move(RIGHT_WHEELS, FULL_SPEED, BACKWARD);

  //move(2, 0, BACKWARD);

  delay(800);

  stop();

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

      move(RIGHT_WHEELS, FULL_SPEED, BACKWARD);
      move(LEFT_WHEELS, FULL_SPEED, FORWARD);

      delay(500);

      stop();

      break;

    case 'R':

      // if checkRight is to be called

      move(LEFT_WHEELS, FULL_SPEED, BACKWARD);
      move(RIGHT_WHEELS, FULL_SPEED, FORWARD);

      delay(500);

      stop();


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




}

//////////////////////////////////////////////////////

void moveLeft() {

  delay(500);

  move(RIGHT_WHEELS, FULL_SPEED, FORWARD);
  move(LEFT_WHEELS, FULL_SPEED, BACKWARD);


  delay(500);

  stop();

  move(RIGHT_WHEELS, FULL_SPEED, FORWARD);
  move(LEFT_WHEELS, FULL_SPEED, BACKWARD);

  Drive();



}

//////////////////////////////////////////////////////

void moveRight() {

  delay(500);

  move(LEFT_WHEELS, FULL_SPEED, FORWARD);
  move(RIGHT_WHEELS, FULL_SPEED, BACKWARD);


  delay(500);

  stop();

  move(LEFT_WHEELS, FULL_SPEED, FORWARD);
  move(RIGHT_WHEELS, FULL_SPEED, BACKWARD);

  Drive();

}

////////////////////////////////////////////////////// :)

void Drive() {

  move(LEFT_WHEELS, FULL_SPEED, FORWARD);
  move(RIGHT_WHEELS, FULL_SPEED, FORWARD);


}

/////////////////////////////////////////////////////

void reverse() {

  delay(500);

  move(LEFT_WHEELS, FULL_SPEED, BACKWARD);
  move(RIGHT_WHEELS, FULL_SPEED, BACKWARD);

  for (int counter = 0; counter < 3; counter++) {

    tone(Buzz_Pin_13, 1500, 500);
    delay(200);
    tone(Buzz_Pin_13, 800, 500);
    delay(500);

  }

  delay(500);

  stop();

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










