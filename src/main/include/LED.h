#pragma once 

#include "Wombat.h"

#include <frc/RobotController.h>
#include <frc/AddressableLED.h>
#include <vector>

struct LEDstrip {
  int kLength;
  frc::AddressableLED m_led;
    // Reuse the buffer

};

enum class RGBpreset {
  kRed,
  kGreen,
  kBlue,
  kYellow,
  kMagenta,
  kBlank,
  kIdle,
};

class LED {
  public:
  LED(frc::AddressableLED *ledStrip);
  // type functionName (parameterType parameterName, parameterType parameterName = parameterDefaultValue);
  void SectionColor(int LEDsection, RGBpreset LEDcolor);
  
  void DisplayBatteryStatus(int LEDsection);

  void DisableAll();

  private:
  RGBpreset _RGBpreset = RGBpreset::kIdle;
  static constexpr int kLength = 120;
  std::array<frc::AddressableLED::LEDData, kLength> ledBuffer;
  frc::AddressableLED *_ledStrip;

  bool _testDisable = false;

  std::vector<double> recentVoltages;
};