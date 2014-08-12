energyShield Library
============

This is the main library for the energyShield. It allows Arduino users to easily access some of the energyShield's fuel
gauge functionality. It uses the Arduino Wire Library to communicate the the fuel gauge and the caculates current battery information.

Buy the energyShield here: http://www.ns-electric.com/products/energyshield/ 

Written by Aaron Liebold for NightShade Electronics.

Copyright (c) 2014, NightShade Electronics

All rights reserved.

Revised BSD License

		Redistribution and use in source and binary forms, with or without
		modification, are permitted provided that the following conditions are met:
		    * Redistributions of source code must retain the above copyright
		      notice, this list of conditions and the following disclaimer.
		    * Redistributions in binary form must reproduce the above copyright
		      notice, this list of conditions and the following disclaimer in the
		      documentation and/or other materials provided with the distribution.
		    * Neither the name NightShade Electronics nor the
		      names of its contributors may be used to endorse or promote products
		      derived from this software without specific prior written permission.
		
		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
		ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
		WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
		DISCLAIMED. IN NO EVENT SHALL NIGHTSHADE ELECTRONICS BE LIABLE FOR ANY
		DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
		(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
		LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
		(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



This Library implements the following commands.

NS_energyShield <object>

	Function: Defines NS_energyShield object <object>
	Returns: nothing
	
<object>.address()

	Function: Changes the target address used by the library
	Returns: nothing
	
<object>.voltage()

	Function: Reads the battery voltage from the fuel gauge
	Returns: [int] Voltage in mV
	
<object>.current()

	Funtion: Reads current charging (positive) or discharging (negative) the battery
	Returns: [int] Current in mA
	
<object>.percent()

	Function: Reads the percent of charge remaining in the battery
	Returns: [int] Percent of charge in 0.5% increments (2 * Percent Charge)
	
<object>.temperature()

	Function: Reads the temperature from the fuel gauge
	Returns: [int] Temperature in 0.125 oC increments (8 * Temperature)

