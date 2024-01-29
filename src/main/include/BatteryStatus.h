#pragma once

#include "LED.h" 
#include "Wombat.h"
#include <frc/RobotController.h>

class Battery {
  public:
  void DisplayBatteryStatus (int LEDsection, RGBpreset LEDcolor);

  private:
  LED *_LED;
};
