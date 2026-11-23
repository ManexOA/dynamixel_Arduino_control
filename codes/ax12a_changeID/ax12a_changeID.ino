#include <DynamixelShield.h>
#include <SoftwareSerial.h>

// USB-to-Serial communication
SoftwareSerial debugSerial(7, 8);

// Dynamixel configuration
const float DXL_PROTOCOL_VERSION = 1.0;

DynamixelShield dxl;

// Desired new ID
const uint8_t NEW_ID = 7;

void setup()
{
  // Initialise serial communication
  debugSerial.begin(115200);

  // Initialise Dynamixel communication
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  debugSerial.println("Starting Dynamixel ID change...");
  debugSerial.println("-------------------------");

  bool motorFound = false;

  // Scan Dynamixel IDs from 0 to 10
  for (uint8_t id = 0; id <= 10; id++)
  {
    if (dxl.ping(id))
    {
      motorFound = true;

      debugSerial.print("Dynamixel detected! Current ID: ");
      debugSerial.println(id);

      // Check if new ID is already occupied
      if (dxl.ping(NEW_ID))
      {
        debugSerial.println("Error: New ID is already occupied!");
        return;
      }

      // Change Dynamixel ID
      dxl.setID(id, NEW_ID);

      delay(200);

      // Verify new ID
      if (dxl.ping(NEW_ID))
      {
        debugSerial.println("ID successfully changed!");

        debugSerial.print("New ID: ");
        debugSerial.println(NEW_ID);
      }
      else
      {
        debugSerial.println("Failed to change ID!");
      }

      break;
    }
  }

  if (!motorFound)
  {
    debugSerial.println("No Dynamixel detected!");
  }

  debugSerial.println("-------------------------");
}

void loop()
{
  // Nothing required here
}
