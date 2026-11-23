#include <DynamixelShield.h>

// Motor configuration
const uint8_t DXL_ID = 12;
const float DXL_PROTOCOL_VERSION = 1.0;

DynamixelShield dxl;

void setup()
{
  // Initialize Dynamixel
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  // Check motor connection
  dxl.ping(DXL_ID);

  // Configure motor
  dxl.torqueOff(DXL_ID);

  dxl.setOperatingMode(DXL_ID, OP_POSITION);

  dxl.torqueOn(DXL_ID);

  // Set motor velocity
  dxl.setGoalVelocity(DXL_ID, 50);

  // Move to centre position
  dxl.setGoalPosition(DXL_ID, 150, UNIT_DEGREE);

  delay(3000);
}

void loop()
{
  // Move slightly left
  dxl.setGoalPosition(DXL_ID, 170, UNIT_DEGREE);
  delay(1000);

   // Return to centre
  dxl.setGoalPosition(DXL_ID, 150, UNIT_DEGREE);
  delay(1000);

  // Move slightly right
  dxl.setGoalPosition(DXL_ID, 130, UNIT_DEGREE);
  delay(1000);

  // Return to centre
  dxl.setGoalPosition(DXL_ID, 150, UNIT_DEGREE);
  delay(1000);
}
