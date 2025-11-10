#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Configuración de Sensores ---

// Acelerómetro
Adafruit_MPU6050 mpu;

// Pantalla OLED
#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64 // Alto de la pantalla OLED en píxeles
#define OLED_RESET -1    // Pin de Reset (-1 si se comparte el reset de Arduino)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- CAMBIO ---
// Definición de pines compatible con Arduino Uno y XIAO
// En XIAO ESP32-S3: 3=D2, 4=D3, 2=D1
// En Arduino Uno:   3, 4, 2 son pines digitales estándar.
const int RED_LED_PIN = 3;   // Rojo (Estaba en D2)
const int GREEN_LED_PIN = 4; // Verde (Estaba en D3)
const int BLUE_LED_PIN = 2;  // Azul (Estaba en D1, y ya no D4 porque D4 ahora es usado por I2C (SCL))


void setup() {
  Serial.begin(115200);

  // --- CAMBIO ---
  // Usar las constantes de pin universales
  pinMode(RED_LED_PIN, OUTPUT);   // Rojo
  pinMode(GREEN_LED_PIN, OUTPUT); // Verde
  pinMode(BLUE_LED_PIN, OUTPUT);  // Azul

  Serial.println("");
  Serial.println("Hello, Hardware!");
  Serial.println("Welcome to Wokwi :-)");

  // --- CAMBIO MANTENIDO ---
  // Inicializar el bus I2C con los pines por defecto (D4/D5 en XIAO, A4/A5 en Uno)
  Wire.begin();

  // --- Inicializar el Acelerómetro (MPU-6050) ---
  if (!mpu.begin()) {
    Serial.println("Error al encontrar el sensor MPU-6050. Revisa las conexiones.");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU-6050 encontrado!");

  // Configurar el rango del acelerómetro
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // --- Inicializar la Pantalla OLED (SSD1306) ---
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error al inicializar la pantalla SSD1306."));
    while (1) {
      delay(10);
    }
  }
  Serial.println("Pantalla OLED inicializada.");

  // Limpiar la pantalla al inicio
  display.clearDisplay();
  display.display();
}

void loop() {
  // --- CAMBIO ---
  // Usar las constantes de pin universales
  Serial.println("Red");
  digitalWrite(RED_LED_PIN, HIGH);
  delay(500);
  digitalWrite(RED_LED_PIN, LOW);

  Serial.println("Green");
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(500);
  digitalWrite(GREEN_LED_PIN, LOW);

  Serial.println("Blue");
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(500);
  digitalWrite(BLUE_LED_PIN, LOW);

  // Obtener nuevos eventos (datos) de los sensores
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // --- Actualizar la Pantalla OLED ---
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Aceleracion (m/s^2):");
  display.println(""); 

  display.setCursor(0, 24);
  display.print("X: ");
  display.print(a.acceleration.x);

  display.setCursor(0, 34);
  display.print("Y: ");
  display.print(a.acceleration.y);

  display.setCursor(0, 44);
  display.print("Z: ");
  display.print(a.acceleration.z);

  display.display();

  delay(100);
}
