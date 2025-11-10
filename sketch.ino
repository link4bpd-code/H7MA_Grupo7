//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 131 bytes
  { 255,1,0,8,0,124,0,17,0,0,0,31,1,106,200,1,1,7,0,130,
  5,120,98,63,0,23,130,5,47,96,70,0,23,2,24,21,65,19,1,216,
  23,31,31,79,78,0,79,70,70,0,71,20,66,65,65,56,0,216,1,135,
  0,0,0,0,0,0,96,64,0,0,128,63,0,0,0,63,205,204,204,61,
  215,0,68,6,142,97,40,49,23,215,86,111,108,116,97,106,101,0,129,15,
  6,80,12,216,69,110,99,101,110,100,101,114,32,76,69,68,0,129,38,52,
  31,9,215,86,111,108,116,97,106,101,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t led; // =1 if switch ON and =0 if OFF

    // output variables
  float Gauge; // from 0 to 3.5
  float Grafica;

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

// Pines
const int ledPin = 2;  // pin del Led
const int potPin = 23; // pin del potenciómetro


void setup() 
{
  RemoteXY_Init (); 
  
  // Configuramos el pin del LED como salida
  pinMode(ledPin, OUTPUT);

  // configuramos el pin del potenciómetro como entrada
  pinMode(potPin, INPUT);

  // Apagamos el led
  digitalWrite(ledPin, LOW);
  
}


void loop() 
{ 
  RemoteXY_Handler ();
  
  // Control del LED
  if (RemoteXY.led==0) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
  
  // Leer el valor del potenciómetro
  int potValue  = analogRead(potPin);
  float voltage = (potValue / 4095.0)* 3.3;
  
  // Asignar el valor leído a los componentes de RemoteXY
  RemoteXY.Gauge = voltage;
  RemoteXY.Grafica = voltage;
}
