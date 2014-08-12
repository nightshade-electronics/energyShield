/*
   NS_energyShield - Library for interfacing with NightShade Electronic's energyShield, rev 8.
   Created by Aaron D. Liebold on August 8, 2014.
   Released into the public domain.
   
   v1.0
*/

#ifndef NS_energyShield_h
#define NS_energyShield_h

#include "Arduino.h"

class NS_energyShield
{
	public:
		NS_energyShield();
		void address(char address);
		int voltage();
		int temperature();
		int current();
		int percent();
		int Vadp(int pin);
	private:
		char _address;
};

#endif