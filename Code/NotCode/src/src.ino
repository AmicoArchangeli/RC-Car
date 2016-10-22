#include <PS2X_lib.h>
#include <Servo.h>

// PS2 PIN SETTINGS
int CLK_PIN = 13;
int CMD_PIN = 11;
int ATN_PIN = 10;
int DAT_PIN = 12;
bool PRESS_ON = true;
bool RMBLE_ON = true;

// MOTOR + SERVO PIN MAPPINGS
int MTR_PIN = 3;
int SRV_PIN = 9;

int SRV_CENTER = 90;
int SRV_MAX_OFFSET = 80;

// Communication details
int SERIAL_RATE = 9600;
int PS2X_TYPE = 0;

// PS2X controller instances
PS2X ps2x;

// Servo instance
Servo servo;

void setup() {
  // Rate at which serial will monitor
  Serial.begin(SERIAL_RATE);

  // Attempt configuration and shit
  int error = ps2x.config_gamepad(CLK_PIN, CMD_PIN, ATN_PIN, DAT_PIN, PRESS_ON, RMBLE_ON);

  if (error == 1 || error == 2) {
    Serial.println("BITCH YOU FUCKING BRICKED THE CONTROLLER");
    exit(0);
  }

  if (PS2X_TYPE == 1) {
    Serial.println("DualShock controller found");
  } else if (PS2X_TYPE == 2) {
    Serial.println("Bitch this ain't Guitar Hero");
    exit(0);
  } else {
    Serial.println("Unknown contorller type");
  }

  // Setup the motors.
  pinMode(MTR_PIN, OUTPUT);

  // Attach the servo
  servo.attach(SRV_PIN);
}

void loop() {
  // Some, uh, vibrating and shit.
  ps2x.read_gamepad(false, RMBLE_ON);

  // Driving
  int L_X = ps2x.Analog(PSS_LX);
  int L_Y = ps2x.Analog(PSS_LY);

  // Steering
  int R_X = ps2x.Analog(PSS_RX);
  int R_Y = ps2x.Analog(PSS_RY);

  // double throt = max(0, (127.0 - L_Y) / 127);
  // double steer = 
  
  // Serial.println(L_Y);
  // Serial.println(throt);
  // Serial.println((127.0 - L_Y) / 127);



  /*
  Serial.print("LX: [");
  Serial.print(L_X);
  Serial.print("] L_Y: [");
  Serial.print(L_Y);
  Serial.print("] RX: [");
  Serial.print(R_X);
  Serial.print("] R_Y: [");
  Serial.print(R_Y);
  Serial.println("]");
  */

  // Do some things with these
  analogWrite(MTR_PIN, 128);
  
}
