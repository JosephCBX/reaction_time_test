#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define SDA_PIN 8
#define SCL_PIN 9

#define P1_BUTTON 7
#define P2_BUTTON 10
#define LED 3

unsigned long startTime;

bool p1Ready = false;
bool p2Ready = false;

void showText(String a, String b = "", String c = "") {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 18); // avoids yellow top area
  display.println(a);
  display.println(b);
  display.println(c);
  display.display();
}

void showReadyScreen() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 18);

  display.println("Get Ready");
  display.print("P1: ");
  display.println(p1Ready ? "Ready" : "Not Ready");
  display.print("P2: ");
  display.println(p2Ready ? "Ready" : "Not Ready");

  display.display();
}

void waitReleaseBoth() {
  while (digitalRead(P1_BUTTON) == LOW || digitalRead(P2_BUTTON) == LOW) {
    delay(10);
  }
  delay(200);
}

void waitForBothPlayersReady() {
  p1Ready = false;
  p2Ready = false;
  showReadyScreen();

  while (!p1Ready || !p2Ready) {
    if (digitalRead(P1_BUTTON) == LOW && !p1Ready) {
      p1Ready = true;
      showReadyScreen();
      waitReleaseBoth();
    }

    if (digitalRead(P2_BUTTON) == LOW && !p2Ready) {
      p2Ready = true;
      showReadyScreen();
      waitReleaseBoth();
    }

    delay(10);
  }

  delay(700);
}

void showResults(unsigned long p1Time, unsigned long p2Time) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 18);

  if (p1Time < p2Time) {
    display.println("P1 WINS!");
    display.print("> P1: ");
    display.print(p1Time);
    display.println(" ms");
    display.print("x P2: ");
    display.print(p2Time);
    display.println(" ms");
  } else if (p2Time < p1Time) {
    display.println("P2 WINS!");
    display.print("x P1: ");
    display.print(p1Time);
    display.println(" ms");
    display.print("> P2: ");
    display.print(p2Time);
    display.println(" ms");
  } else {
    display.println("TIE!");
    display.print("P1: ");
    display.print(p1Time);
    display.println(" ms");
    display.print("P2: ");
    display.print(p2Time);
    display.println(" ms");
  }

  display.display();
}

void setup() {
  Serial.begin(115200);

  pinMode(P1_BUTTON, INPUT_PULLUP);
  pinMode(P2_BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, LOW);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (1);
  }

  randomSeed(esp_random());
}

void loop() {
  digitalWrite(LED, LOW);

  waitForBothPlayersReady();

  showText("Both Ready", "Wait for light...");
  delay(1000);

  unsigned long waitStart = millis();
  unsigned long waitTime = random(2000, 6000);

  while (millis() - waitStart < waitTime) {
    if (digitalRead(P1_BUTTON) == LOW) {
      showText("P1 TOO SOON", "P2 WINS");
      delay(3000);
      waitReleaseBoth();
      return;
    }

    if (digitalRead(P2_BUTTON) == LOW) {
      showText("P2 TOO SOON", "P1 WINS");
      delay(3000);
      waitReleaseBoth();
      return;
    }

    delay(5);
  }

  digitalWrite(LED, HIGH);
  startTime = millis();

  bool p1Pressed = false;
  bool p2Pressed = false;
  unsigned long p1Time = 0;
  unsigned long p2Time = 0;

  while (!p1Pressed || !p2Pressed) {
    if (!p1Pressed && digitalRead(P1_BUTTON) == LOW) {
      p1Pressed = true;
      p1Time = millis() - startTime;
    }

    if (!p2Pressed && digitalRead(P2_BUTTON) == LOW) {
      p2Pressed = true;
      p2Time = millis() - startTime;
    }

    delay(1);
  }

  digitalWrite(LED, LOW);

  showResults(p1Time, p2Time);

  delay(4000);
}
