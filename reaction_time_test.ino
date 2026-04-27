#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define SDA_PIN 8
#define SCL_PIN 9
#define BUTTON 7
#define LED 3

unsigned long startTime;

void waitForButtonPress() {
  while (digitalRead(BUTTON) == HIGH);
  delay(200); // debounce
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  randomSeed(esp_random());
}

void loop() {

  // ---- START SCREEN ----
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Press button");
  display.println("to start");
  display.display();

  waitForButtonPress();

  // ---- READY ----
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println("GET READY");
  display.display();

  delay(1000);

  // ---- RANDOM WAIT ----
  unsigned long waitStart = millis();
  unsigned long waitTime = random(2000, 5000);

  while (millis() - waitStart < waitTime) {
    if (digitalRead(BUTTON) == LOW) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.println("TOO SOON!");
      display.display();
      delay(2000);
      return;
    }
  }

  // ---- GO ----
  digitalWrite(LED, HIGH);
  startTime = millis();

  while (true) {
    if (digitalRead(BUTTON) == LOW) {
      unsigned long reaction = millis() - startTime;
      digitalWrite(LED, LOW);

      // ---- RESULT ----
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 20);
      display.print("Reaction: ");
      display.print(reaction);
      display.println(" ms");
      display.display();

      delay(2500);
      break;
    }
  }

  // ---- TRY AGAIN SCREEN ----
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Press button");
  display.println("to try again");
  display.display();

  waitForButtonPress();
}
