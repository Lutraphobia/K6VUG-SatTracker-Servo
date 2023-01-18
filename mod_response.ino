/* ==========================================================================

Amateur Radio Satellite Tracking System using Arduino
by Umesh Ghodke
https://sites.google.com/site/k6vugdiary/

Copyright (C) 2012 Umesh Ghodke, Amateur Call Sign K6VUG

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software 
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
MA 02110-1301, USA.

The content is covered under the Creative Commons Attribution-ShareAlike 3.0 
License (http://creativecommons.org/licenses/by-sa/3.0/)

========================================================================== */


// ===================== COMMON TEXT RESPONSE FUNCTIONS =====================

// Sends the version string back to the PC
void printVersionInfo()
{
  Serial.println(VersionString);
}


// Sends the current azimuth angle back to the PC
void printCurrentAzimuth()
{
    Serial.print("AZ");
    if (FlipAz == true)
      Serial.print((180 - curAz) + 180); // compensate for the 180 degree flip mode
    else
      Serial.print(180 - curAz);
      lcd.setCursor(10,2); lcd.print("  "); // Clear the Old Az Characters
      lcd.setCursor(9,2); lcd.print(curAz); // Displays current Az on LCD and updates while other text stays static
      lcd.setCursor(12,2); lcd.print((char)223); // Print Special Character for Degree

// Compass Functionality for Az
  if (curAz > 0 && curAz < 15) // North
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(0); lcd.print(" N");
  }
  
  if (curAz > 15 && curAz < 75) // Degree from north towards east direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(1); lcd.print(" NE");
  }
  
  if (curAz > 75 && curAz < 115) // East
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(2); lcd.print(" E");
  }
  
  if (curAz > 115 && curAz < 165) // Degree from south towards east direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(3); lcd.print(" SE");
  }
  
  if (curAz > 165 && curAz < 195) // South
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(4); lcd.print(" S");
  }
  
  if (curAz > 195 && curAz < 235) // Degree from south towards west direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(5); lcd.print(" SW");
  }
  
  if (curAz > 235 && curAz < 285) // West
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(6); lcd.print(" W");
  }
  
  if (curAz > 285 && curAz < 345)    // Degree from North towards west direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(7); lcd.print(" NW");
  }
  
  if (curAz > 345 && curAz < 360)    // Degree from North towards west direction
  {
   lcd.setCursor(14,2); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,2); lcd.write(0); lcd.print(" N");
  }
}


// Sends the current elevation angle back to the PC
void printCurrentElevation()
{
  Serial.print("EL");
  if (FlipAz == true)
    Serial.print(180 - curEl);   // compensate for the 180 degree flip mode
  else
    Serial.print(curEl);
    lcd.setCursor(10,3); lcd.print("  "); // Clear the Old Az Characters
    lcd.setCursor(9,3); lcd.print(curEl); // Displays current El on LCD and updates while other text stays static
    lcd.setCursor(12,3); lcd.print((char)223); // Print Special Character for Degree

// Compass Functionality for El
  if (curEl > 180 && curAz < 360) // Below Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(4); lcd.print(" BH");
  }
  
  if (curEl > 0 && curEl < 30) // From Horizon to 45 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(6); lcd.print(" H");
  }
  
  if (curEl > 30 && curEl < 65) // From 45 to 90 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(7); lcd.print(" AH");
  }
  
  if (curEl > 65 && curEl < 115) // From Horizon to 45 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(0); lcd.print(" OH");
  }
    
  if (curEl > 115 && curEl < 150) // From Horizon to 45 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(1); lcd.print(" AH");
  }
    
  if (curEl > 150 && curEl < 180) // From Horizon to 45 Degrees Elevation Above Horizon
  {
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
   lcd.setCursor(14,3); lcd.write(2); lcd.print(" H");
   lcd.setCursor(14,3); lcd.print("    "); // Clears the Buffer
  }
}


// Sends the current values of the system parameters back to the PC
void printSetParameters()
{
  Serial.println("System Parameters:");
  printAZServoParameters();
  Serial.println();
  printELServoParameters();
  Serial.println();
  printSpeedRPM();
  Serial.println();
  printTimeout();
  Serial.println();
}


// Sends the current parameters of the azimuth servo back to the PC
void printAZServoParameters()
{
  Serial.print("AZ Servo Min/Max Pulse Widths (microseconds):");
  Serial.print(AzServoMin);
  Serial.print("/");
  Serial.print(AzServoMax);
}


// Sends the current parameters of the elevation servo back to the PC
void printELServoParameters()
{
  Serial.print("EL Servo Min/Max Pulse Widths (microseconds):");
  Serial.print(ElServoMin);
  Serial.print("/");
  Serial.print(ElServoMax);
}


// Sends the current speed in rpm back to the PC
void printSpeedRPM()
{
  Serial.print("Rotational Speed (rpm):");
  Serial.print(curSpeed);
}


// Sends the power timeout parameter in seconds, back to the PC
void printTimeout()
{
  Serial.print("Servo Timeout (sec):");
  Serial.print(servoTimeout);
}



// ================== END OF TEXT RESPONSE FUNCTIONS ========================

//////////////////////////////////////////////////////////////////////////////////////
