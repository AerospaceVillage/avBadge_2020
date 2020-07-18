/**
 *
 * Aerospace Badge 2020
 * 
 * This is the code for the Aerospace Village Badge DEF CON 2020.
 * 
 * The code for the badge provides an I2C interface to the following 
 * 3 lighting packages: 
 *  1. Navigation Lights (Red and Green)
 *  2. Flightdeck Lights (Yellow)
 *  3. Anti-Collision Lights (White)
 *  
 *  This code is targeting the Attiny85 MCU and uses the TinyWire package
 *  https://github.com/rambo/TinyWire
 *  
 *  
 *  I2C Slave Address 0x44
 *  
 * Author: Dan Allen
 * Date: 14 June 2020
 * Version: 1.0
 *
 **/
 
 #define I2C_SLAVE_ADDRESS 0x44 // the 7-bit address
// Get this from https://github.com/rambo/TinyWire

#include <TinyWireS.h>

// The default buffer size
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif
 
#define NAV_PIN 3
#define FLIGHTDECK_PIN 1
#define ANTI_COLLISION_PIN 4
 
// Allow the user to change the lights being on/off
volatile boolean nav_lights = true;
volatile int flightdeck_lights = 50;
volatile boolean anti_collision_lights = true;

unsigned long previousMillis = 0;  // stores last state time for anti-collision lights


const int anti_collision_ON_TIME = 40;
const int anti_collision_OFF_TIME = 1800;
boolean anti_collision_ON_STATE = true;

char msg[154] = "Aerospace Village\n\nBUILD - INSPIRE - PROMOTE\n\n Send us an email at village@aerospacevillage.org with the subject badge and tell us what you thought!";
int msg_len = 154;
int msg_index = 0;


void requestEvent()
{
    TinyWireS.send(byte(msg[msg_index]));
  msg_index++;
  if(msg_index > msg_len){
    msg_index = 0;
  }
}

void receiveEvent(uint8_t howMany)
{
  //Sanity check, only looking for 1 byte of passed in data
  if( howMany != 1){
    return;
  }
  
  int value = TinyWireS.receive();
  if( value == 1){
    nav_lights = !nav_lights;
  }else if ( value == 2){
    anti_collision_lights = !anti_collision_lights;    
  }else if ( value == 3){
    flightdeck_lights = 0;
  }else{
    flightdeck_lights = value;
  }
}


void setup()
{
  pinMode(NAV_PIN, OUTPUT);
  pinMode(FLIGHTDECK_PIN, OUTPUT);
  pinMode(ANTI_COLLISION_PIN, OUTPUT);

  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);
}

/*
* Helper function to handle the aysmmetric timing of the anti-collision lights.
* To create the desired timing the lights are pulsed in a quick burst.
*/
void antiCollisionLights()
{
  unsigned long currentMillis = millis();
  
  if(anti_collision_ON_STATE){
    if(currentMillis >= previousMillis + anti_collision_ON_TIME){
      anti_collision_ON_STATE = !anti_collision_ON_STATE;
      previousMillis = currentMillis;
      if(anti_collision_lights){
        digitalWrite(ANTI_COLLISION_PIN, LOW);
      }
    }
  }else{
    if(currentMillis >= previousMillis + anti_collision_OFF_TIME){
      anti_collision_ON_STATE = !anti_collision_ON_STATE;
      previousMillis = currentMillis;
      if(anti_collision_lights){
        digitalWrite(ANTI_COLLISION_PIN, HIGH);
      }
    }
  }   
 }
 
void loop()
{
  digitalWrite(NAV_PIN, nav_lights);
  analogWrite(FLIGHTDECK_PIN, flightdeck_lights);
  antiCollisionLights();

  TinyWireS_stop_check();
}
   
