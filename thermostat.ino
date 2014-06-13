// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_MPL115A.h"

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_LEDBackpack.h"

//PIR Sensor

int LEDPin = D7;
int InputPin = D2;
int PIRState = LOW;
int val = 0;

bool remote = false;

Adafruit_8x8matrix matrix1;
Adafruit_MPL115A2 sensor1;

double temp = 0;
char* message = "Hello";

static const uint8_t smile[] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10100101,
  0b10011001,
  0b01000010,
  0b00111100
};

static const uint8_t frown[] = {
    0b00111100,
    0b01000010,
    0b10100101,
    0b10000001,
    0b10011001,
    0b10100101,
    0b01000010,
    0b00111100
};

void setup() {

    Wire.begin();
    matrix1.begin(0x70);
    pinMode(LEDPin, OUTPUT);
    pinMode(InputPin, INPUT);
    Spark.function("screen", writeToPack);
    Spark.variable("temp", &temp, DOUBLE);
    sensor1.begin();

}

int writeToPack(String command) {
    remote = true;
    if (command == "smile") {
        matrix1.clear();
        matrix1.drawBitmap(0, 0, smile, 8, 8, LED_ON);
        matrix1.writeDisplay();
        return 1;
    } else if (command == "frown") {
        matrix1.clear();
        matrix1.drawBitmap(0, 0, frown, 8, 8, LED_ON);
        matrix1.writeDisplay();
        return 1;
    } else {
        remote = false;
        return -1;
    }
}

void loop() {

    val = digitalRead(InputPin);
    if(!remote) {
        if (val == HIGH) {
            matrix1.clear();
            matrix1.drawBitmap(0, 0, frown, 8, 8, LED_ON);
            matrix1.writeDisplay();
        } else {
            matrix1.clear();
            matrix1.drawBitmap(0, 0, smile, 8, 8, LED_ON);
            matrix1.writeDisplay();
        }
    }

    temp = sensor1.getTemperature();
}
