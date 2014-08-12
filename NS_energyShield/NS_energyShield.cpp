/*
   NS_energyShield - Library for interfacing with NightShade Electronic's energyShield, rev 8.
   Created by Aaron D. Liebold on August 8, 2014.
   Released into the public domain.
   
   v1.0
*/

#include "Arduino.h"
#include "NS_energyShield.h"
#include "Wire.h"


NS_energyShield::NS_energyShield()
{
  Wire.begin();	//Begins TwoWire interface
  _address = B00110110;
}

// Tell library if fuel gauge has non-default address
void NS_energyShield::address(char address)
{
  _address = address;
}

int NS_energyShield::voltage()
{
	byte voltageHB,voltageLB;
	int V;
	
	Wire.beginTransmission(_address);
	Wire.write(0x0C);
	Wire.endTransmission(false);
	Wire.requestFrom(_address,2);
	voltageHB = Wire.read();
	voltageLB = Wire.read();
	
	V = (unsigned long) ((voltageHB << 5) + (voltageLB >> 3))*122/100;
	
	return V; // Returns voltage in mV
}

int NS_energyShield::current()
{
	int Iraw;
	byte currentHB,currentLB;
	
	// Reads high and low chars of the register
	Wire.beginTransmission(_address);
	Wire.write(0x0E);
	Wire.endTransmission(false);
	Wire.requestFrom(_address,2);
	currentHB = Wire.read();
	currentLB = Wire.read();
	
	Iraw = (long) (((currentHB << 8) + currentLB) >> 4)*5/4; // Merges high and low bytes and applies 1.25 mA/unit conversion
	
	return Iraw; // Returns current in mA
}

int NS_energyShield::percent()
{
	byte stateOfCharge;
	
	Wire.beginTransmission(_address);
	Wire.write(0x02);
	Wire.endTransmission(false);
	Wire.requestFrom(_address,1);
	stateOfCharge = Wire.read();
	
	return stateOfCharge; // Returns percent of battery charge in 0.5% increments (1/200)
}


int NS_energyShield::temperature()
{
	int T;
	byte tempHB, tempLB;
	
	// Reads high and low chars of the register
	Wire.beginTransmission(_address);
	Wire.write(0x0A);
	Wire.endTransmission(false);
	Wire.requestFrom(_address,2);
	tempHB = Wire.read();
	tempLB = Wire.read();
	
	T = tempHB*8 + tempLB/32; // Combines high and low bytes
	
	return T; // Returns temperature in increments of 0.125 degrees C
}

int NS_energyShield::Vadp(int pin)
{
	int V = (unsigned long) analogRead(pin)*25000/1023;
	return V;
}


