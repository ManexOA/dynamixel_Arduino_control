#include <DynamixelShield.h>
#include <SoftwareSerial.h>

// USB-to-Serial communication
SoftwareSerial debugSerial(7, 8);

// Dynamixel configuration
const uint8_t DXL_ID = 9;
const float DXL_PROTOCOL_VERSION = 1.0;

DynamixelShield dxl;

unsigned long previousReadTime = 0;
const unsigned long READ_INTERVAL = 100;

void setup()
{
  // Start USB-to-Serial communication
  debugSerial.begin(115200);

  // Initialise Dynamixel
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  // Check motor connection
  if (dxl.ping(DXL_ID))
  {
    debugSerial.println("AX-12A connected!");
  }
  else
  {
    debugSerial.println("ERROR: Motor not detected!");
    while (1);
  }

  // Configure motor
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_POSITION);
  dxl.torqueOn(DXL_ID);

  // Set motor velocity
  dxl.setGoalVelocity(DXL_ID, 50);

  // Move to centre
  dxl.setGoalPosition(DXL_ID, 180, UNIT_DEGREE);

  delay(3000);

  // Print data headings
  debugSerial.println("Time(ms),Position(deg),Load");
}

void loop()
{
  // Move slightly left
  dxl.setGoalPosition(DXL_ID, 170, UNIT_DEGREE);

  readPositionAndLoadForInterval(1000);

    // Return to centre
  dxl.setGoalPosition(DXL_ID, 150, UNIT_DEGREE);

  readPositionAndLoadForInterval(1000);

  // Move slightly right
  dxl.setGoalPosition(DXL_ID, 130, UNIT_DEGREE);

  readPositionAndLoadForInterval(1000);

  // Return to centre
  dxl.setGoalPosition(DXL_ID, 150, UNIT_DEGREE);

  readPositionAndLoadForInterval(1000);
}


// Function to continuously read motor position and load
void readPositionAndLoadForInterval(unsigned long duration)
{
  unsigned long startTime = millis();

  while (millis() - startTime < duration)
  {
    unsigned long currentTime = millis();

    if (currentTime - previousReadTime >= READ_INTERVAL)
    {
      previousReadTime = currentTime;

      // Read present motor position
      float position =
        dxl.getPresentPosition(DXL_ID, UNIT_DEGREE);

      // Read present motor load
      int load =
        dxl.readControlTableItem(ControlTableItem::PRESENT_LOAD, DXL_ID);

      // Send data to computer
      debugSerial.print(currentTime);
      debugSerial.print(",");
      debugSerial.print(position);
      debugSerial.print(",");
      debugSerial.println(load);
    }
  }
}
