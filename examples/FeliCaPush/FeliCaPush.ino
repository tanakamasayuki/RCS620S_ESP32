#include "RCS620S_ESP32.h"

RCS620S rcs620s(Serial1);

#define COMMAND_TIMEOUT  400
#define PUSH_TIMEOUT     2100
#define POLLING_INTERVAL 500

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 32, 33);
  delay(1000);

  int ret = rcs620s.initDevice();
  Serial.print("RCS620S Init = ");
  Serial.println(ret);
}

void loop() {
  // Polling
  rcs620s.timeout = COMMAND_TIMEOUT;
  int ret = rcs620s.polling();
  Serial.print("RCS620S polling = ");
  Serial.println(ret);
  if (ret) {
    Serial.print("idm = ");
    for (int i = 0; i < 8; i++) {
      Serial.print(rcs620s.idm[i], HEX);
    }
    Serial.println();

    Serial.print("pmm = ");
    for (int i = 0; i < 8; i++) {
      Serial.print(rcs620s.pmm[i], HEX);
    }
    Serial.println();
  }

  rcs620s.rfOff();
  delay(POLLING_INTERVAL);
}
