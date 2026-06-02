# Reaction Time Test
A reaction time game where an LED lights up randomly and your response time is shown on a display.

## Components

<ul>
  <li>
    <a href="https://www.amazon.com/dp/B0FFLXM9KL/" target="_blank">ESP32-S3 Dev Board</a>
  </li>
  <li>
    <a href="https://www.amazon.com/dp/B072Q2X2LL" target="_blank">0.9in OLED Display</a>
  </li>
  <li>
    <a href="https://www.amazon.com/dp/B08JHVLK84?th=1" target="_blank">Buttons</a>
  </li>
  <li>
    LED - generic LED from arduino kit
  </li>
</ul>

## Prerequisites

* Arduino IDE
* Libraries
  * Adafruit SSD1306
  * Adafruit GFX

## Wiring

| **Component** | **Pin/Side**  | **Connects to ESP32-S3** |
|---------------|---------------|--------------------------|
| LED           | Long Leg (+)  | GPIO 3                   |
| LED           | Short Leg (-) | GND                      |
| Button        | Red Wire      | GPIO 7                   |
| Button        | Black Wire    | GND                      |
| OLED          | GND           | GND                      |
| OLED          | VCC           | 3.3v                     |
| OLED          | SCL           | GPIO 9                   |
| OLED          | SDA           | GPIO 8                   |

<img width="255" height="300" alt="IMG_6247-compressed" src="https://github.com/user-attachments/assets/0199f4e7-40f1-4032-ad71-e3575ae198c1" />

## Demo
[demo.webm](https://github.com/user-attachments/assets/6fa2b545-615e-40ed-a427-6b5981bf2f3d)

## Future Updates
