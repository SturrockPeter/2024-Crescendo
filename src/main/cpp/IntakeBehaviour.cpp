#include "IntakeBehaviour.h"

IntakeManualControl::IntakeManualControl(Intake *intake, frc::XboxController &codriver) : _intake(intake), _codriver(codriver) {
	Controls(intake);	
};


void IntakeManualControl::OnTick(units::second_t dt) {
	if (_codriver.GetPOV() == -1){
    _intake->setState(IntakeState::kHold);
  } else if (_codriver.GetPOV() == 0){
    _intake->setState(IntakeState::kIntaking);
  } else if (_codriver.GetPOV() == 180){
    _intake->setState(IntakeState::kOutaking);
  } else if (_codriver.GetPOV() == 270){
    _intake->setState(IntakeState::kShift);
  }
}
