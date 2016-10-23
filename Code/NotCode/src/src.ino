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

int SRV_CENTER = 43;
int SRV_MAX_OFFSET = 20;
int SRV_ERR = 3; // Error tolerance.
int ERR_LAST = 42;

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

  // Throttle
  int LB_1 = ps2x.Button(PSB_L1);
  int LB_2 = ps2x.Button(PSB_L2);
  int RB_1 = ps2x.Button(PSB_R1);
  int RB_2 = ps2x.Button(PSB_R2);

  // Steering
  int L_X = ps2x.Analog(PSS_LX);
  int R_X = ps2x.Analog(PSS_RX);

  // Modify raw throttle values.
  double mod_throt = 0.00;

  if (LB_1) mod_throt = 0.25;
  if (LB_2) mod_throt = 0.50;
  if (RB_1) mod_throt = 0.75;
  if (RB_2) mod_throt = 1.00;

  // modify raw steering values.
  int avg_steer = (L_X + R_X) / 2;
  double mod_steer = SRV_CENTER + SRV_MAX_OFFSET - (avg_steer * (2.0 * SRV_MAX_OFFSET) / 255);

  // Readjust raw steering values to compensate for offset.
  if (abs(mod_steer - SRV_CENTER) < SRV_ERR) {
    if (ERR_LAST != 42) {
      mod_steer = 42;
      ERR_LAST = 42;
    } else {
      mod_steer = 43;
      ERR_LAST = 43;
    }
  }

  Serial.print(mod_throt);
  Serial.print(" | ");
  Serial.println(mod_steer);

  analogWrite(MTR_PIN, mod_throt * 255);
  delay(25);
  servo.write(mod_steer);
  delay(25);
}
