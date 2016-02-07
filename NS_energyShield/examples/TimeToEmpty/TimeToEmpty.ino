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
#define CURRENTS_LEN 10 // array size

NS_energyShield eS; // Create NS-energyShield object called "eS"

// Global variables
long lastTime;
unsigned long TimeToEmpty;
int Currents[CURRENTS_LEN];
boolean charging;

void setup()
{
  Serial.begin(9600);

  // Initialize Currents array with initial value
  const int latestCurrent = eS.current();
  Currents[0] = (latestCurrent < 0) ? -latestCurrent : 0;
  for (int i=1; i < CURRENTS_LEN; ++i) Currents[i] = Currents[i-1];

  lastTime = millis(); 
}

void loop()
{
  const unsigned long ts = millis();

  // Note: if lastTime < ts this means it wrapped, and
  //       in such case, we treat it as if 100ms went by
  if (ts > lastTime + 100 || lastTime < ts) {
    TTE(); // Run TTE every 100 ms
    lastTime = ts;
  }

  if (ts%5000 == 0) // Print results every 5 seconds
  {
    if (!charging) 
    {
      Serial.print("Time to Empty: ");      
      Serial.print(TimeToEmpty/60); // Hours
      Serial.print(" hr ");
      Serial.print(TimeToEmpty%60); // Minutes
      Serial.println(" min");
    }
    else Serial.println("Charging!");

    delay(1); // Ensure that a ms passes, so it does not double print
  }
}

void TTE()
{
  const int latestCurrent = eS.current();
  int AvgCurrent = 0;

  // Update charging state
  charging = (latestCurrent > 0);

  // If we are currently charging or not drawing any
  // current, then there is nothing to do in regards to
  // TimeToEmpty calculation
  if (charging || latestCurrent == 0) return;

  // Shift Currents array by 1 and add new current value to index 0
  for (int i=1; i < CURRENTS_LEN; ++i) Currents[i] = Currents[i-1];
  Currents[0] = -latestCurrent;

  // Calculate AvgCurrent
  for (int i=0; i < CURRENTS_LEN; ++i) AvgCurrent += Current[i];
  AvgCurrent /= CURRENTS_LEN;

  // Minutes until empty
  TimeToEmpty = (unsigned long) BATTERY_CAPACITY*eS.percent()*60/AvgCurrent/200;
}
