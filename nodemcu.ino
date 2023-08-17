#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd; // Initialize the LCD object

void setup() {
  lcd.begin(16, 2);      // Initialize the LCD dimensions (16 columns, 2 rows)
  lcd.backlight();       // Turn on the backlight
  Serial.begin(9600);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PC Data to LCD");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    data.trim(); // Remove leading/trailing whitespace

    if (data.startsWith("CPU:") && data.indexOf(" RAM:") != -1) {
      int cpu_usage = data.substring(4, data.indexOf(" RAM:")).toInt();
      float used_ram_gb = data.substring(data.indexOf("RAM:") + 4).toFloat();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CPU: " + String(cpu_usage) + "%");
      lcd.setCursor(0, 1);
      lcd.print("RAM: " + String(used_ram_gb, 2) + " GB");

      Serial.print("Received CPU Usage: ");
      Serial.print(cpu_usage);
      Serial.print("%, Used RAM: ");
      Serial.print(used_ram_gb);
      Serial.println(" GB");
    }
  }
}
