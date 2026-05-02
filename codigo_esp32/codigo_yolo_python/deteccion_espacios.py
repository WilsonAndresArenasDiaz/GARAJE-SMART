import cv2
import serial
import time
from ultralytics import YOLO

ESPACIOS_TOTALES = 8
PUERTO_SERIAL = 'COM3'
BAUDRATE = 115200

class DetectorEstacionamiento:
    def __init__(self):
        print("Cargando YOLO...")
        self.modelo = YOLO('yolov8n.pt')
        self.conexion = None
        
    def conectar_esp32(self):
        try:
            self.conexion = serial.Serial(PUERTO_SERIAL, BAUDRATE, timeout=1)
            print(f"Conectado a ESP32 en {PUERTO_SERIAL}")
            time.sleep(2)
            return True
        except:
            print("No se pudo conectar al ESP32")
            return False
    
    def detectar_autos(self, frame):
        resultados = self.modelo(frame, verbose=False)[0]
        autos = 0
        for box in resultados.boxes:
            if int(box.cls[0]) == 2:
                autos += 1
        return min(autos, ESPACIOS_TOTALES)
    
    def ejecutar(self):
        cap = cv2.VideoCapture(0)
        if not cap.isOpened():
            print("Error: No se detectó cámara")
            return
        
        ultimo_envio = 0
        
        while True:
            ret, frame = cap.read()
            if not ret:
                break
            
            autos_detectados = self.detectar_autos(frame)
            libres = ESPACIOS_TOTALES - autos_detectados
            
            if time.time() - ultimo_envio > 1:
                if self.conexion:
                    self.conexion.write(f"LIBRE:{libres}\n".encode())
                    print(f"Espacios libres: {libres}")
                ultimo_envio = time.time()
            
            cv2.putText(frame, f"Libres: {libres}", (10, 30),
                       cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
            cv2.imshow("Garaje - YOLO", frame)
            
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
        
        cap.release()
        cv2.destroyAllWindows()

if __name__ == "__main__":
    detector = DetectorEstacionamiento()
    detector.conectar_esp32()
    detector.ejecutar()
