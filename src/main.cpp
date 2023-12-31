// https://github.com/wholybee/esp32-smartBMSdisplay
#include <Arduino.h>
#include <BleSerialClient.h>

BleSerialClient SerialBT;

uint8_t unitMACAddress[6]; // Use MAC address in BT broadcast and display
char deviceName[20];       // The serial string that is broadcast.

unsigned long RestartTimer = 0;
void startBluetooth()
{
  // Get unit MAC address
  esp_read_mac(unitMACAddress, ESP_MAC_WIFI_STA);

  unitMACAddress[5] += 2;
  // Create device name
  sprintf(deviceName, "Monitor-%02X%02X", unitMACAddress[4], unitMACAddress[5]);

  // Init BLE Serial
  SerialBT.begin(deviceName);
  SerialBT.setTimeout(10);
}

void setup()
{
  // Start BLE
  startBluetooth();
  // Start Serial
  Serial.begin(115200);
}

void loop()
{
  SerialBT.bleLoop();
  if (millis() >= (RestartTimer + 1000))
  {
    SerialBT.write(0x00);
    RestartTimer = millis();
  }
}
