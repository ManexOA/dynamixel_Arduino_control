#include <DynamixelShield.h>
#include <SoftwareSerial.h>

// USB-to-Serial communication
SoftwareSerial debugSerial(7, 8);

// Dynamixel configuration
const float DXL_PROTOCOL_VERSION = 1.0;

DynamixelShield dxl;

void setup()
{
  // Initialise USB-to-Serial communication
  debugSerial.begin(115200);

  // Initialise Dynamixel communication
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  debugSerial.println("Starting Dynamixel scan...");
  debugSerial.println("-------------------------");

  int motorCount = 0;

  // Scan IDs from 0 to 10
  for (uint8_t id = 0; id <= 10; id++)
  {
    if (dxl.ping(id))
    {
      debugSerial.print("Dynamixel detected! ID: ");
      debugSerial.println(id);

      motorCount++;
    }
  }

  debugSerial.println("-------------------------");

  debugSerial.print("Total motors detected: ");
  debugSerial.println(motorCount);

  if (motorCount == 0)
  {
    debugSerial.println("No Dynamixels detected!");
  }
}

void loop()
{
  // Nothing required here
}
