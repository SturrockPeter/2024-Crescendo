#include "LED.h"

#include <iostream>

LED::LED(frc::AddressableLED *ledStrip) : _ledStrip(ledStrip) {}


void LED::SectionColor(int LEDsection, RGBpreset LEDcolor){
  if (_testDisable) {return;}
  int r,g,b = 0;
  switch(LEDcolor){

    case RGBpreset::kIdle:
    std::cout << "LEDoff" << std::endl;
    break;

    case RGBpreset::kBlank:
    r = 0;
    g = 0;
    b = 0;
    std::cout << "LEDblank" << std::endl;
    break;

    case RGBpreset::kRed:
    r = 255;
    g = 0;
    b = 0;
    std::cout << "LEDred" << std::endl;
    break;

    case RGBpreset::kGreen:
    r = 0;
    g = 255;
    b = 0;
    std::cout << "LEDgreen" << std::endl;
    break;

    case RGBpreset::kBlue:
    r = 0;
    g = 0;
    b = 255;
    std::cout << "LEDblue" << std::endl;
    break;
    
    case RGBpreset::kMagenta:
    r = 255;
    g = 0;
    b = 255;
    std::cout << "LEDmagenta" << std::endl;
    break;

    case RGBpreset::kYellow:
    r = 255;
    g = 255;
    b = 0;
    std::cout << "LEDyellow" << std::endl;
    break;

    default:
    r = 0;
    g = 0;
    b = 0;
    std::cout << "LEDdefault(error)" << std::endl;
  
  }

    int sectionid = (LEDsection * 20);
    
    for (int i = sectionid; i < 20 + sectionid; i++){
      ledBuffer[i].SetRGB(r, g, b);
    };
    _ledStrip->SetData(ledBuffer);


}

void LED::DisplayBatteryStatus(int LEDsection){
  if (_testDisable) {return;}

  /*
  each time this function is called, recalculate average battery voltages, and use that for display
  */

  recentVoltages.push_back(frc::RobotController::GetBatteryVoltage().value());
  if (recentVoltages.size() > 5) {
    recentVoltages.erase(recentVoltages.begin());
  }
  double voltagesSum = 0;
  for(double voltage : recentVoltages)
  {
    voltagesSum += voltage;
  }

  double averageVoltage = voltagesSum / recentVoltages.size();

  if (averageVoltage < 12.3) {
    SectionColor(LEDsection, RGBpreset::kGreen);
  } else {
    SectionColor(LEDsection, RGBpreset::kBlue);
  }
};
void LED::DisableAll(){
  for (int i = 0; i < 120; i++){
      ledBuffer[i].SetRGB(0, 0, 0);
    };
    _ledStrip->SetData(ledBuffer);
    _testDisable = true;
}
