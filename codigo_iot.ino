// Librerias
#include <WiFi.h> // Para conectarse al wifi del ESP32
#include <HTTPClient.h> // Para enviar datos mediante HTTP
// Protocolo y libreria para el sensor de temperatura
#include <OneWire.h> 
#include <DallasTemperature.h>

// Configuracion wifi
const char* ssid = "PelayitosUTD"; // Nombre de la red
const char* password = "24446666"; // Contrasena de la red
const char* serverUrl = "http://10.72.86.217:5000/api/measurements"; // Endpoint del servidor

// Pines
#define ONE_WIRE_BUS 4 // Pin digital para el sensor temperatura
#define PH_PIN 32 // Pin analogico para el sensor de pH
#define TDS_PIN 35 // Pin analogico para el sensor de conductividad

// Objetos para el sensor de temperatura
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

void setup() {
  Serial.begin(115200);
  tempSensor.begin(); // Inicia el sensor de temperatura
  
// reconecion wifi
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  
  connectWiFi(); // Coneccion wifi
}

void loop() {
  static unsigned long lastSendTime = 0;
  const long interval = 30000;
  //const long interval = 900000; // Envio de datos cada 15 minutos

  if (millis() - lastSendTime >= interval) {
    lastSendTime = millis(); 
    
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WIFI] Reconectando...");
      connectWiFi();
      return;
    }

// Lectura de sensores
    Serial.println("\n=== Leyendo sensores ===");
    float temperature = readTemperature(); // Leer temperatura
    float phValue = readPH(); // Leer pH
    float tdsValue = readTDS(); // Leer conductividad
    
//Muestra los datos enviados en el monitor serial
    Serial.printf("Temp: %.1f°C | pH: %.1f | TDS: %.0f ppm\n", 
                 temperature, phValue, tdsValue);
    sendToServer(temperature, phValue, tdsValue);
  }
}

// Leer temperatura
float readTemperature() {
  tempSensor.requestTemperatures();
  float temp = tempSensor.getTempCByIndex(0); // Obtiene temperatura en °C

  if(temp == DEVICE_DISCONNECTED_C) {
    Serial.println("[SENSOR] Error leyendo temperatura");
    return -127.0;
  }
  return temp;
}

// Leer pH
float readPH() {
  int analogValue = analogRead(PH_PIN);
  if(analogValue < 100 || analogValue > 4095) {
    Serial.println("[SENSOR] Valor de pH fuera de rango");
    return 0.0; // Retorna 0 en caso de error
  }
  
// Convierte el valor analógico a voltaje (0-3.3V)
  float phVoltage = analogValue * 3.3 / 4095.0;
  
//convertir voltaje a valor de pH
//2.5V corresponde a 7pH, cada 0.18V de cambio representa 1pH
  return 7.0 + ((2.5 - phVoltage) / 0.18);
}

//Leer conductividad
float readTDS() {
  int analogValue = analogRead(TDS_PIN);
  if(analogValue == 0 || analogValue > 4095) {
    Serial.println("[SENSOR] Error leyendo TDS");
    return 0.0; // Regresa 0 en caso de error
  }
  
  float tdsVoltage = analogValue * 3.3 / 4095.0;
  
// Multiplica por 1000 para obtener un valor en ppm
  return tdsVoltage * 1000;
}

// Funcion para mandar los datos a la BD
void sendToServer(float temp, float ph, float tds) {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("[HTTP] Error: WiFi desconectado");
    return;
  }
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  
// Registro de mediciones
  String payload = StringFormat(
    "{\"tankId\":\"6877c2afb6a3505873a75d2b\"," 
    "\"temperature\":%.1f,"                 
    "\"ph\":%.1f,"                        
    "\"conductivity\":%.0f}",                   
    temp, ph, tds
  );

  Serial.println("[HTTP] Enviando datos: " + payload);
  
// Envia POST al servidor
  int httpCode = http.POST(payload);
  
  if(httpCode > 0) {
    Serial.printf("[HTTP] Código de respuesta: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      Serial.println("[HTTP] Respuesta: " + response);
    }
  } else {
    Serial.printf("[HTTP] Error en la solicitud: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

// Conectar al wifi
void connectWiFi() {
  Serial.println("\nConectando a WiFi...");
  WiFi.disconnect(); 
  WiFi.begin(ssid, password);

  unsigned long startTime = millis();
  
  while(WiFi.status() != WL_CONNECTED && millis() - startTime < 20000) {
    delay(500);
    Serial.print(".");
  }

  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado a WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP()); // Muestra IP
  } else {
    Serial.println("\nFalló la conexión WiFi");
  }
}

String StringFormat(const char* format, ...) {
  char buffer[256]; 
  va_list args; 
  va_start(args, format); 
  vsnprintf(buffer, sizeof(buffer), format, args); 
  va_end(args); 
  return String(buffer); 
}