#pragma once 

#include "Wombat.h"

#include <frc/RobotController.h>
#include <frc/AddressableLED.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Intake.h"
#include "Shooter.h"
#include "AlphaArm.h"
#include <frc/Timer.h>


struct LEDstrip {
  int kLength;
  frc::AddressableLED m_led;
    // Reuse the buffer

};

struct RGBvalues {
  int r, g, b;
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
  void SectionColor(int LEDsection, RGBpreset LEDcolor, int sectionQty);
  void SectionColor(int LEDsection, RGBpreset LEDcolor, int sectionQty, bool loop);
  void SectionColor(int LEDsection, RGBpreset LEDcolor, int sectionQty, bool loop, bool inverse);

  void Pain();

  RGBvalues GetRGBValues (RGBpreset LEDcolor);

  void StoreIntakeState(IntakeState intakeState);
  void StoreShooterState(ShooterState shooterState);
  void StoreArmState(AlphaArmState alphaArmState);

  void DisplayBatteryStatus(int LEDsection);

  void DisplayIntakeStatus(int LEDsection);

  void DisplayShooterStatus(int LEDsection);

  void DisplayArmStatus(int LEDsection);




  void DisableAll();

  private:
  RGBpreset _RGBpreset = RGBpreset::kIdle;
  static constexpr int kLength = 220;
  std::array<frc::AddressableLED::LEDData, kLength> ledBuffer;
  
  frc::AddressableLED *_ledStrip;

  bool _testDisable = false;

  int _bufferPriority = 0;
  int _priorityLevel = 0;

  IntakeState _intakeState = IntakeState::kIdle;

  ShooterState _shooterState = ShooterState::kRaw;

  AlphaArmState _alphaArmState = AlphaArmState::kIdle;

  std::vector<double> recentVoltages;
};