# GARAJE-SMART
GARAJE INTELIGENTE DETECTION POR MEDIO DE YOLO DE DISPONIBILIDAD 
# 🚗 GARAJE-SMART - Estacionamiento Inteligente para HotWheels

## 📌 Descripción del Proyecto
Sistema embebido que controla un garaje inteligente en miniatura para autos HotWheels de 8 espacios. Desarrollado con ESP32, sensores infrarrojos, servomotor (talanquera), pantalla LCD y visión por computadora con YOLO.

## 🛠️ Componentes de Hardware
| Componente | Cantidad | Especificaciones |
|------------|----------|------------------|
| ESP32 | 1 | Cualquier modelo |
| Sensor Infrarrojo (IR) | 2 | TCRT5000 |
| Servomotor | 1 | SG90 o MG90S |
| LCD 16x2 con I2C | 1 | Dirección 0x27 |
| LED Rojo | 1 | 5mm |
| LED Verde | 1 | 5mm |
| Resistencias 220Ω | 2 | Para LEDs |
| Cámara | 1 | USB o ESP32-CAM |

## 🔌 Conexiones Eléctricas
| Componente | Pin ESP32 |
|------------|-----------|
| Sensor IR Entrada | GPIO 34 |
| Sensor IR Salida | GPIO 35 |
| Servomotor | GPIO 13 |
| LCD I2C SDA | GPIO 21 |
| LCD I2C SCL | GPIO 22 |
| LED Rojo | GPIO 14 |
| LED Verde | GPIO 27 |

## 🚀 Instalación

### 1. Configurar Arduino IDE
```bash
# Agregar ESP32 en Arduino IDE
Archivo -> Preferencias -> URLs adicionales:
https://dl.espressif.com/dl/package_esp32_index.json

# Instalar librerías
LiquidCrystal I2C by Frank de Brabander
ESP32Servo by John K. Bennett
