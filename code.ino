#include <AFMotor.h>
#include <PPMReader.h>

// Define motor objects for each motor
AF_DCMotor motor1(1); // Motor 1 connected to M1 on the motor shield    
AF_DCMotor motor2(2); // Motor 2 connected to M2 on the motor shield
AF_DCMotor motor3(3); // Motor 3 connected to M3 on the motor shield
AF_DCMotor motor4(4); // Motor 4 connected to M4 on the motor shield

// Define PPM reader settings
byte interruptPin = 2;  // Pin used for interrupt
byte channelAmount = 6; // Number of channels in PPM signal
PPMReader ppm(interruptPin, channelAmount);

void setup() {
  // Set initial speed of the motors and stop
  motor1.setSpeed(0);
  motor1.run(RELEASE);

  motor2.setSpeed(0);
  motor2.run(RELEASE);

  motor3.setSpeed(0);
  motor3.run(RELEASE);

  motor4.setSpeed(0);
  motor4.run(RELEASE);

  Serial.begin(115200);
}

void loop() {
  // Read PPM signals
  unsigned int ppmValues[channelAmount];
  for (byte channel = 1; channel <= channelAmount; ++channel) {
    ppmValues[channel - 1] = ppm.latestValidChannelValue(channel, 0);
  }

  // Map PPM values to motor speeds
  // Assuming ppmValues[0] to ppmValues[3] correspond to motor speeds
  int motorSpeeds[4];
  for (int i = 0; i < 4; ++i) {
    motorSpeeds[i] = map(ppmValues[i], 1000, 2000, 0, 255); // Map PPM range to motor speed range
  }

  // Extract control values from PPM signals
  int throttle = motorSpeeds[2]; // Channel 3 for throttle control
  int direction = ppmValues[1]; // Channel 1 for direction control
  int turn = ppmValues[0]; // Channel 2 for turning control


  

  // Determine movement based on PPM values
  if (direction > 1500 && turn<1800 && turn > 1200) { // Forward
    forward(throttle);
  } else if(turn<1800 && turn > 1200) { // Backward
    backward(throttle);
  }else{
     if (turn > 1500) { // Turn right
    move_right();
  } else { // Turn left
    move_left();
  }
    
  }

 
}

void forward(int throttle) {
  // All motors move forward
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  // Set motor speeds
  motor1.setSpeed(throttle);
  motor2.setSpeed(throttle);
  motor3.setSpeed(throttle);
  motor4.setSpeed(throttle);
}

void backward(int throttle) {
  // All motors move backward
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

  // Set motor speeds
  motor1.setSpeed(throttle);
  motor2.setSpeed(throttle);
  motor3.setSpeed(throttle);
  motor4.setSpeed(throttle);
}

void move_left() {
  // Left motors move forward, right motors stop
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  // Set motor speeds
  motor1.setSpeed(255);
  motor2.setSpeed(255);
}

void move_right() {
  // Right motors move forward, left motors stop
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  // Set motor speeds
  motor3.setSpeed(255);
  motor4.setSpeed(255);
}
