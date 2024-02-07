#include "LED.h"



LED::LED(frc::AddressableLED *ledStrip) : _ledStrip(ledStrip) {}

RGBvalues LED::GetRGBValues (RGBpreset LEDcolor) {
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
  RGBvalues values {
    r, g, b
  };
  return values;
}

void LED::Pain(){ 

    _ledStrip->SetData(ledBuffer);

}

void LED::SectionColor(int LEDsection, RGBpreset LEDcolor){
  	if (_testDisable) {return;}

    		int r,g,b = 0;
    		bool RemoveEnd = false;
    		int j = 0;
   		int k = 1;
    		int sectionid = (LEDsection * 10);

    		RGBvalues values = GetRGBValues (LEDcolor);

	      for (int i = sectionid; i < 10 + sectionid; i++){
          ledBuffer[i].SetRGB(values.r, values.g, values.b);
        };
        // _ledStrip->SetData(ledBuffer);

    
}
 
void LED::SectionColor(int LEDsection, RGBpreset LEDcolor, int sectionQty){
  if (_testDisable) {return;}

    int r,g,b = 0;

    int sectionid = (LEDsection * 10);
    int sections = (sectionQty * 10);
    
    RGBvalues values = GetRGBValues (LEDcolor);

    for (int i = sectionid; i < sections + sectionid; i++){
      ledBuffer[i].SetRGB(values.r, values.g, values.b);
    };
    // _ledStrip->SetData(ledBuffer);

   
}
 
void LED::SectionColor(int LEDsection, RGBpreset LEDcolor, int sectionQty, bool loop){
  if (_testDisable) {return;}
    int r,g,b = 0;

    int sectionid = (LEDsection * 10);
    int sections = (sectionQty * 10);
    
    RGBvalues values = GetRGBValues (LEDcolor);
    
    int previous = 0;
    		for (int i = sectionid; i < sections + sectionid; i++){

          int sectionid = (LEDsection * 10);
          int sections = (sectionQty * 10);
     			if (i > sectionid + 2) {
				ledBuffer[previous].SetRGB(0, 0, 0);
			} 
      if (i < sectionid + 2) {
      ledBuffer[i + (sections - 2)].SetRGB(0, 0, 0);
      }

			ledBuffer[i].SetRGB(values.r, values.g, values.b);
    			_ledStrip->SetData(ledBuffer);
			previous = i - 2;

      std::this_thread::sleep_for (std::chrono::milliseconds(35));
		}
		ledBuffer[previous].SetRGB(0, 0, 0);
    
    
		// _ledStrip->SetData(ledBuffer);
    }

void LED::SectionColor(int LEDsection, RGBpreset LEDcolor, int sectionQty, bool loop, bool inverse){
  if (_testDisable) {return;}
    int r,g,b = 0;
 
    int sectionid = (LEDsection * 10);
    int sections = (sectionQty * 10);
    
    RGBvalues values = GetRGBValues (LEDcolor);
    
    int previous = 0;
    		for (int i = sectionid + sections; i > sectionid - 1; i--){
          int sectionid = (LEDsection * 10);
          int sections = (sectionQty * 10);

     			if (i < (sectionid + sections) - 2) {
				ledBuffer[previous].SetRGB(0, 0, 0);
			} 
      if (i > (sectionid + sections) - 2) {
      ledBuffer[i - (sections - 1)].SetRGB(0, 0, 0);
      }

			ledBuffer[i].SetRGB(values.r, values.g, values.b);
    			// _ledStrip->SetData(ledBuffer);
			previous = i + 2;

      std::this_thread::sleep_for (std::chrono::milliseconds(35));
		  }
		ledBuffer[previous].SetRGB(0, 0, 0);
		// _ledStrip->SetData(ledBuffer);
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

  if (averageVoltage > 10) {
    SectionColor(LEDsection, RGBpreset::kMagenta, 6);
  } else {
    SectionColor(LEDsection, RGBpreset::kBlue, 6);
  }
};

void LED::StoreIntakeState(IntakeState intakeState) {
  _intakeState = intakeState;
};

void LED::DisplayIntakeStatus(int LEDsection) {
  switch (_intakeState) {
    case IntakeState::kIdle: {
      SectionColor(LEDsection, RGBpreset::kMagenta);
    } break;
    case IntakeState::kEject: {
      SectionColor(LEDsection, RGBpreset::kRed, 2);
    } break;
    case IntakeState::kHold: {
      SectionColor(LEDsection, RGBpreset::kMagenta, 2);
    } break;
    case IntakeState::kIntake: {
      SectionColor(LEDsection, RGBpreset::kMagenta, 2);
    } break;

    default:
      SectionColor(LEDsection, RGBpreset::kIdle);
      break;
  }
  
  /*
  
  set the LEDs based on the Intake state
  if intake state is idle, set the leds to magenta

  if intake is intaking, set leds to moving magenta forewards

  if outtaking set to moving magenta backwards

  if none, set to blank
  
  */
};

void LED::StoreShooterState(ShooterState shooterState) {
  _shooterState = shooterState;
};

void LED::DisplayShooterStatus(int LEDsection) {
  switch (_shooterState) {
    case ShooterState::kIdle: {
      SectionColor(LEDsection, RGBpreset::kMagenta);
    } break;
    case ShooterState::kSpinUp: {
      SectionColor(LEDsection, RGBpreset::kMagenta, 2);
    } break;
    case ShooterState::kShooting: {
      SectionColor(LEDsection, RGBpreset::kRed, 2);
    } break;

    case ShooterState::kReverse: {
      SectionColor(LEDsection, RGBpreset::kGreen);
    } break;
    case ShooterState::kRaw: {
      SectionColor(LEDsection, RGBpreset::kMagenta);
    } break;
    default:
      SectionColor(LEDsection, RGBpreset::kIdle);
      break;
  }
 
};

void LED::StoreArmState(AlphaArmState alphaArmState) {
  _alphaArmState = alphaArmState;
};


void LED::DisplayArmStatus(int LEDsection) {
  switch (_alphaArmState) {
    case AlphaArmState::kIdle: {
      SectionColor(LEDsection, RGBpreset::kMagenta, 2);
    } break;
    case AlphaArmState::kRaw:{

    }break;
    case AlphaArmState::kForwardWrist:{
    SectionColor(LEDsection, RGBpreset::kBlue, 2);
    }break;
    case AlphaArmState::kReverseWrist:{
      SectionColor(LEDsection, RGBpreset::kBlue, 2);
    }break;
    default:
      SectionColor(LEDsection, RGBpreset::kIdle);
      break;
  }
 
};


void LED::DisableAll(){
  for (int i = 0; i < 220; i++){
      ledBuffer[i].SetRGB(0, 0, 0);
    };
    _ledStrip->SetData(ledBuffer);
    _testDisable = true;
}
 