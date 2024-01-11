#include "Intake.h"

Intake::Intake(IntakeConfig config) : _config(config) {}

void Intake::OnUpdate(units::second_t dt){
	switch(_state){
		case IntakeState::kIntaking:
			_config.intakeGearbox.motorController->SetVoltage(5_V);
			break;
		case IntakeState::kOutaking:
			_config.intakeGearbox.motorController->SetVoltage(-5_V);
			break;
		case IntakeState::kIdle:
			_config.intakeGearbox.motorController->SetVoltage(0_V);
			break;
		case IntakeState::kShift:
			_config.intakeGearbox.motorController->SetVoltage(3_V);
			break;
		case IntakeState::kHold:
			_config.intakeGearbox.motorController->SetVoltage(0_V);
			break;
		default:
			std::cout <<"Error intake in invalid state!" << std::endl;
			break;
	}
}

void Intake::setState(IntakeState state) {
	_state = state;
};
void Intake::setRaw(units::volt_t voltage) {
	_voltage = voltage;
};