#include "HX711.h"
#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

#define CLK_PIN          2
#define DOUT_PIN         3
#define TARE_PIN         4
#define TARE_DELETE_PIN  5
#define METER_PIN        A0
#define WATER_HEIGHT_PIN A1

bool Tare_State = HIGH;

float offsetValue = 0.0;
float cumulativeOffset = 0.0;
float previousWeight = 0.0;
float meter_Value = 0.0;
float meter_Speed = 0.0;
float ultrasonic_Value = 0.0;
float water_Height = 0.0;

HX711 scale;
LiquidCrystal_I2C lcd(0x27, 20, 4); // Correct I2C address 0x27

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT_PIN, CLK_PIN);
  scale.set_scale(340); // Set calibration factor to 340

  pinMode(TARE_PIN, INPUT_PULLUP); // Use internal pull-up resistor
  pinMode(TARE_DELETE_PIN, INPUT_PULLUP);
  pinMode(METER_PIN, INPUT);
  pinMode(WATER_HEIGHT_PIN, INPUT);

  initialize_LCD_DISPLAY();

  EEPROM.get(0, cumulativeOffset);
  scale.set_offset(0);//-1 * cumulativeOffset
}

void loop() {
  if (scale.is_ready()) {

    float weight = scale.get_units(); // Get instantaneous weight
    Serial.print("Weight: ");
    Serial.print(weight - 90);
    Serial.println(" lbs");

    bool Tare_State = digitalRead(TARE_PIN);
    if (Tare_State == LOW) { // If the button is pressed
      Serial.println("Tare Activated");
      lcd.setCursor(0, 1);
      lcd.print("                "); // Clear previous value
      lcd.setCursor(0, 1);
      lcd.print("Tare Activated");

      scale.tare();
      
      delay(1500); // Delay to display "Tare Activated" message
      lcd.setCursor(0, 1);
      lcd.print("                ");
    }

    lcd.setCursor(8, 0); // Set the cursor to column 0, line 1
    lcd.print(weight - 90); // Print the instantaneous weight
    lcd.print(" lbs"); // Print the unit

    display_METER_SPEED();

    display_WATER_HEIGHT();

  } else {
    Serial.println("HX711 not found.");
  }

  delay(500); // Delay for 0.5 seconds
}

void initialize_LCD_DISPLAY(){
    lcd.init(); // Initialize the LCD
    lcd.backlight(); // Turn on the backlight
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Weight: ");
    lcd.setCursor(0, 2);
    lcd.print("Water Height: ");
    lcd.setCursor(0, 3);
    lcd.print("MeterSpeed: ");
  }

void display_METER_SPEED(){
    meter_Value = analogRead(METER_PIN);
    meter_Speed = (float)(meter_Value - 155) * 100.0 / 25;
    lcd.setCursor(12, 3);
    lcd.print("       ");
    lcd.setCursor(12, 3);
    lcd.print(meter_Speed);
    // lcd.print(meter_Value);
    lcd.print("%");
  }

void display_WATER_HEIGHT(){
    ultrasonic_Value = analogRead(WATER_HEIGHT_PIN);
    water_Height = ultrasonic_Value;
    lcd.setCursor(15,2);
    lcd.print("     ");
    lcd.setCursor(15,2);
    lcd.print(water_Height);
    lcd.print("\"");
  }
