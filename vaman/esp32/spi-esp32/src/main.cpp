#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <Arduino.h>
#include <DabbleESP32.h>
#include "esp32_eoss3_spi.h"

#define MISC_BASE_ADDR 0x40005000
#define SW_MB_1 MISC_BASE_ADDR + 0x110
#define SW_MB_2 MISC_BASE_ADDR + 0x114

uint8_t val;

void setup() {
  Serial.begin(115200);
  val = -1;
  Dabble.begin("MyEsp32");
  esp32_eoss3_spi_init();  
}

void loop() {
  Dabble.processInput();
  if (Terminal.available()) {
    val = Terminal.readNumber();
    Serial.print("Read ");
    Serial.println(val);
    esp32_eoss3_spi_ahb_write(SW_MB_1, &val, 4);
  }
  delay(1000);
}
