#include <DynamixelShield.h>
#include <SoftwareSerial.h>

// USB-to-Serial communication
SoftwareSerial debugSerial(7, 8);

// Dynamixel configuration
const uint8_t DXL_ID = 3;
const float DXL_PROTOCOL_VERSION = 1.0;

DynamixelShield dxl;

// Required for Control Table items
using namespace ControlTableItem;

// Data reading interval
const unsigned long READ_INTERVAL = 100;

unsigned long previousReadTime = 0;

void setup()
{
  // Initialize USB-to-Serial communication
  debugSerial.begin(115200);

  // Initialize Dynamixel communication
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

  // Print data headings
  debugSerial.println("Time(ms),Position(deg),Load");
}

void loop()
{
  unsigned long currentTime = millis();

  // Read data every 100 ms
  if (currentTime - previousReadTime >= READ_INTERVAL)
  {
    previousReadTime = currentTime;

    // Read present motor position
    float position =
        dxl.getPresentPosition(DXL_ID, UNIT_DEGREE);

    // Read present motor load
    int load =
        dxl.readControlTableItem(PRESENT_LOAD, DXL_ID);

    // Transmit data through USB-to-Serial adapter
    debugSerial.print(currentTime);
    debugSerial.print(",");

    debugSerial.print(position);
    debugSerial.print(",");

    debugSerial.println(load);
  }
}
