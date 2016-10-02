#include <PS2X_lib.h>

// PS2 PIN SETTINGS
int CLK_PIN = 13;
int CMD_PIN = 11;
int ATN_PIN = 10;
int DAT_PIN = 12;
bool PRESS_ON = true;
bool RMBLE_ON = true;

// MOTOR + SERVO PIN MAPPINGS
int MTR_PIN = 3;
int SRV_PIN = 5;

// Communication details
int SERIAL_RATE = 9600;
int PS2X_TYPE = 0;

// PS2X controller instances
PS2X ps2x;

void setup() {
  // Rate at which serial will monitor
  Serial.begin(SERIAL_RATE);

  // Attempt configuration and shit
  int error = ps2x.config_gamepad(13, 11, 10, 12, PRESS_ON, RMBLE_ON);

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
  pinMode(SRV_PIN, OUTPUT);
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

  Serial.print("LX: [");
  Serial.print(L_X);
  Serial.print("] L_Y: [");
  Serial.print(L_Y);
  Serial.print("] RX: [");
  Serial.print(R_X);
  Serial.print("] R_Y: [");
  Serial.print(R_Y);
  Serial.println("]");

  // Do some things with these
  
}
