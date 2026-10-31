// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device

#include <Arduino.h>
#include "BluetoothSerial.h"
//Declaras las variables para la activar las polaridades de los motores , es decir 2 variables por motor
//
const int m_atrasizq = 18; //MOTOR 4
const int m_atrasizq1=21; //MOTOR 4

//Variable de pwm ambos motores de atras comparte el mismo pwm que regula la velocidad de los motores
const int pwmtras = 19;

const int m_atrasder = 33; //MOTOR 2
const int m_atrasder1 = 32; //MOTOR 2

const int m_adelanteder = 25; //MOTOR 3
const int m_adelanteder1 = 26;//MOTOR 3

const int m_adelanteizq = 13; //MOTOR 1 
const int m_adelanteizq1= 27; //MOTOR 1  

//Variable de pwm ambos motores de adelanten comparte el mismo pwm que regula la velocidad de los motores
const int pwmdelante= 23;
//Nombre del dispositivo Bluetooth
String device_name = "ESP32Vane";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;





void setup() {
 
  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  
  // Cada variable se declara como salida , tanto la polaridad de los motores como los pwm
pinMode(pwmtras, OUTPUT);
pinMode(m_atrasizq1, OUTPUT);
pinMode(m_atrasizq,OUTPUT);
pinMode(m_atrasder1, OUTPUT);
pinMode(m_atrasder, OUTPUT);
pinMode(m_adelanteder, OUTPUT);
pinMode(m_adelanteder1, OUTPUT);
pinMode(m_adelanteizq ,OUTPUT);
pinMode(m_adelanteizq1, OUTPUT);
pinMode(pwmdelante, OUTPUT);

}

void loop() {
  // Reenvía datos del Monitor Serie al Bluetooth
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  // Comprueba si hay un dato recibido vía Bluetooth
  if (SerialBT.available()) {
    char message = SerialBT.read(); // Lee el carácter enviado por App Inventor

     //Lee los datos q manda la aplicacion y manda la señal del esp32 al integrado
     //Presionar boton, IR ATRAS
    if (message == 'S') {
      Serial.print("Recibido: ");
      Serial.println(message);
      digitalWrite(m_atrasder1 ,HIGH);
       digitalWrite(m_atrasizq1 ,HIGH);
       digitalWrite(m_adelanteder ,HIGH);
       digitalWrite(m_adelanteizq ,HIGH);
       analogWrite(pwmtras,255);
       analogWrite(pwmdelante,255);
    } 
    //Al soltar el boton se apagan todos los motores encendidos 
    else if (message == 's') {
      Serial.print("Recibido: ");
       Serial.println(message);
       digitalWrite(m_atrasder1 ,LOW);
       digitalWrite(m_atrasizq1 ,LOW);
       digitalWrite(m_adelanteder,LOW);
       digitalWrite(m_adelanteizq ,LOW);
       analogWrite(pwmtras,0);
       analogWrite(pwmdelante,0);    
       }

      //Lee el dato que manda la app y el esp32 manda la señal al integrado
      //IR ADELANTE
     else if (message == 'C') {
       Serial.print("Recibido: ");
       Serial.println(message);
       digitalWrite(m_atrasder, HIGH);
       digitalWrite(m_atrasizq ,HIGH);
       digitalWrite(m_adelanteder1,HIGH);
       digitalWrite(m_adelanteizq1,HIGH);
       analogWrite(pwmtras,255);
       analogWrite(pwmdelante,255);

    }
      //Al soltar el boton se apagan todos los motores encendidos 

       else if (message == 'c') {
       Serial.print("Recibido: ");
       Serial.println(message);
       digitalWrite(m_atrasder, LOW);
       digitalWrite(m_atrasizq ,LOW);
       digitalWrite(m_adelanteder1,LOW);
       digitalWrite(m_adelanteizq1,LOW);
       analogWrite(pwmtras,0);
       analogWrite(pwmdelante,0);    

     }

     //GIRO A LA DERECHO
     else if (message == 'G') {
      Serial.print("Recibido: ");
      Serial.println(message);
       digitalWrite(m_atrasder1, HIGH);
       digitalWrite(m_atrasizq ,HIGH);
      digitalWrite(m_adelanteder,HIGH); //MOTOR 3
      digitalWrite(m_adelanteizq1 ,HIGH); //MOTOR 1
      analogWrite(pwmdelante,255);
         analogWrite(pwmtras,200);

     }
     //Al soltar el boton se apagan todos los motores encendidos 
     else if (message == 'g') {
       Serial.print("Recibido: ");
       Serial.println(message);
      Serial.print("Recibido: ");
      Serial.println(message);
      digitalWrite(m_atrasder1 ,LOW);
      digitalWrite(m_atrasizq ,LOW);
      digitalWrite(m_adelanteder,LOW);
      digitalWrite(m_adelanteizq1 ,LOW);
      analogWrite(pwmtras,0);
      analogWrite(pwmdelante,0);
     }
     //GIRO A LA IZQUIERDA
    else if (message == 'V') {
      Serial.print("Recibido: ");
       Serial.println(message);
       digitalWrite(m_atrasder, HIGH);
       digitalWrite(m_atrasizq1 ,HIGH);
      digitalWrite(m_adelanteder1,HIGH); //MOTOR 3
      digitalWrite(m_adelanteizq ,HIGH); //MOTOR 1
      analogWrite(pwmdelante,255);
         analogWrite(pwmtras,200);
     }
     //Al soltar el boton se apagan todos los motores encendidos 
     else if (message == 'v') {
       Serial.print("Recibido: ");
       Serial.println(message);
        digitalWrite(m_atrasder ,LOW);
      digitalWrite(m_atrasizq1 ,LOW);
      digitalWrite(m_adelanteder1,LOW);
      digitalWrite(m_adelanteizq ,LOW);
      analogWrite(pwmtras,0);
      analogWrite(pwmdelante,0);
     }
    
  }
}