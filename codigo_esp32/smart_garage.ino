#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define IR_ENTRADA  34
#define IR_SALIDA   35
#define SERVO_PIN   13
#define LED_ROJO    14
#define LED_VERDE   27

Servo talanquera;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ESPACIOS_TOTALES = 8;
int espacios_ocupados = 0;
bool garaje_lleno = false;

void setup() {
  Serial.begin(115200);
  pinMode(IR_ENTRADA, INPUT_PULLUP);
  pinMode(IR_SALIDA, INPUT_PULLUP);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_VERDE, HIGH);
  
  talanquera.attach(SERVO_PIN);
  talanquera.write(0);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GARAJE SMART");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(2000);
  
  actualizarDisplay();
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    if (comando.startsWith("LIBRE:")) {
      int libres = comando.substring(6).toInt();
      if (libres >= 0 && libres <= ESPACIOS_TOTALES) {
        espacios_ocupados = ESPACIOS_TOTALES - libres;
        actualizarDisplay();
        controlarLEDs();
      }
    }
  }
  
  if (digitalRead(IR_ENTRADA) == LOW && !garaje_lleno) {
    if (espacios_ocupados < ESPACIOS_TOTALES) {
      abrirTalanquera();
      delay(500);
      espacios_ocupados++;
      actualizarDisplay();
      controlarLEDs();
      delay(1000);
    }
  }
  
  if (digitalRead(IR_SALIDA) == LOW) {
    if (espacios_ocupados > 0) {
      abrirTalanquera();
      delay(500);
      espacios_ocupados--;
      actualizarDisplay();
      controlarLEDs();
      delay(1000);
    }
  }
  
  delay(50);
}

void abrirTalanquera() {
  talanquera.write(90);
  delay(3000);
  talanquera.write(0);
}

void actualizarDisplay() {
  int espacios_libres = ESPACIOS_TOTALES - espacios_ocupados;
  garaje_lleno = (espacios_ocupados >= ESPACIOS_TOTALES);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GARAJE SMART");
  lcd.setCursor(0, 1);
  lcd.print("L:");
  lcd.print(espacios_libres);
  lcd.print("/");
  lcd.print(ESPACIOS_TOTALES);
  lcd.print(" O:");
  lcd.print(espacios_ocupados);
  
  if (garaje_lleno) {
    lcd.setCursor(12, 1);
    lcd.print("LLENO");
  }
}

void controlarLEDs() {
  if (espacios_ocupados >= ESPACIOS_TOTALES) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, HIGH);
  } else {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ROJO, LOW);
  }
}
