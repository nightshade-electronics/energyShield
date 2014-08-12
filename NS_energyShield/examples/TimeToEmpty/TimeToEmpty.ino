/**********************************************************/
/*  TimeToEmpty V1.0                                      */
/*  for the energyShield by NightShade Electronics        */
/*                                                        */
/*  This sketch calculates the time until the battery     */
/*  will be empty and the current rate of discharge.      */
/*                                                        */ 
/*  Created by Aaron D. Liebold                           */
/*  on August 11, 2014                                    */
/*                                                        */
/*  This code is released into the public domain.         */
/**********************************************************/

#include <NS_energyShield.h>
#include <Wire.h>

#define BATTERY_CAPACITY 1200 // mAh

NS_energyShield eS; // Create NS-energyShield object called "eS"

// Global variables
long lastTime = millis(); 
unsigned long TimeToEmpty;
int Current[10], AvgCurrent;
boolean charging;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (millis() > lastTime + 100) TTE(); // Run TTE every 100 ms

  if (millis()%5000 == 0) // Print results every 5 seconds
  {
    if (!charging) 
    {
      Serial.print("Time to Empty: ");      
      Serial.print(TimeToEmpty/60); // Hours
      Serial.print(" hr ");
      Serial.print(TimeToEmpty%60); // Minutes
      Serial.println(" min");
    }
    else Serial.print("Charging!");

    delay(1); // Ensure that a ms passes, so it does not double print
  }
}

void TTE()
{
  for(int i=9;i>0;i--) Current[i] = Current [i-1];
  Current[0] = eS.current();

  for (int i=9;i>=0;i--)
  {
    if (Current[i] < 0)
    {
      Current[i] = -Current[i];
      charging = 0;
    }
    else
    {
      charging = 1;
    }
  }

  // Check that energyShield is not charging
  for(int i=0;i<10;i++) AvgCurrent += Current[i];
  AvgCurrent /= 10;

  TimeToEmpty = (unsigned long) BATTERY_CAPACITY*eS.percent()*60/AvgCurrent/200; // Minutes until empty

  lastTime = millis();
}


