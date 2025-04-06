#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(32, 16, 2);

const int TEMP = A0;
const int analogInPin = A2;
const int analogOutPin = 8;
const int SOIL = A1;

int valTemp = 0, valSoil = 0;
int celsius = 0;
int umidade = 0;

int sensorValue = 0;
int outputValue = 0;
bool ledState = false;

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    
    Serial.begin(9600);
  
    pinMode(analogOutPin, OUTPUT);
    pinMode(analogInPin, INPUT);
}

void loop() {
    // Leitura da temperatura
    valTemp = analogRead(TEMP);
    celsius = map(((valTemp - 20) * 3.04), 0, 1023, -40, 125);

    // Leitura da luminosidade
    sensorValue = analogRead(analogInPin);
    outputValue = map(sensorValue, 0, 1023, 0, 255);
    
    if (sensorValue > 500) {
        analogWrite(analogOutPin, outputValue);
        ledState = true;  // LED aceso
    } else {
        analogWrite(analogOutPin, 0);
        ledState = false; // LED apagado
    }

    // Leitura da umidade do solo
    valSoil = analogRead(SOIL);
    umidade = map(valSoil, 880, 0, 100, 0);

    // Exibir no LCD
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("TEMP: "); lcd.print(celsius); lcd.print("C ");
    
    lcd.setCursor(10, 0);
    lcd.print("U: "); lcd.print(umidade); lcd.print("%");
    
    lcd.setCursor(0, 1);
    lcd.print("LED: "); lcd.print(ledState ? "ON " : "OFF");
  
    // Exibir no Serial Monitor
    Serial.print("Temperatura: ");
    Serial.print(celsius);
    Serial.print("C | Umidade: ");
    Serial.print(umidade);
    Serial.print("% | LED: ");
    Serial.println(ledState ? "ON" : "OFF");

    delay(1000);
}
