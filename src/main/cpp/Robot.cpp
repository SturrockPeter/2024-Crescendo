// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "Robot.h"

// include units
#include <units/velocity.h>
#include <units/acceleration.h>
#include <units/length.h>
#include <units/angle.h>
#include <units/time.h>
#include <units/voltage.h>

#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/controller/RamseteController.h>
#include <frc/Timer.h>

static units::second_t lastPeriodic;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption("Default Auto", "Default Auto");

  frc::SmartDashboard::PutData("Auto Selector", &m_chooser);

  m_path_chooser.SetDefaultOption("Path1", "paths/output/Path1.wpilib.json");

  m_path_chooser.AddOption("Path1", "paths/output/Path1.wpilib.json");
  m_path_chooser.AddOption("Path2", "paths/output/Path2.wpilib.json");

  frc::SmartDashboard::PutData("Path Selector", &m_path_chooser);

  frc::SmartDashboard::PutData("Field", &m_field);

  simulation_timer = frc::Timer();

  robotmap.swerveBase.gyro->Reset();

  // _swerveDrive = new wom::SwerveDrive(robotmap.swerveBase.config, frc::Pose2d());
  // wom::BehaviourScheduler::GetInstance()->Register(_swerveDrive);
  // _swerveDrive->SetDefaultBehaviour(
  //     [this]() { return wom::make<wom::ManualDrivebase>(_swerveDrive, &robotmap.controllers.driver); });
  
  
  
  
  

  m_led.SetLength(120);
  m_led.Start();
  led = new LED(&m_led);
  // m_driveSim = new wom::TempSimSwerveDrive(&simulation_timer, &m_field);
  // m_driveSim = wom::TempSimSwerveDrive();

   // Default to a length of 60, start empty output
  // Length is expensive to set, so only set it once, then just update data
// m_ledBuffer[0].SetRGB(0, 255, 0);

 //   m_led.SetLength(kLength);
// m_led.SetData(m_ledBuffer);
//   m_led.Start();
}

void Robot::RobotPeriodic() {
  auto dt = wom::now() - lastPeriodic;
  lastPeriodic = wom::now();

  loop.Poll();
  wom::BehaviourScheduler::GetInstance()->Tick();

  led->DisplayBatteryStatus(5);
  // _swerveDrive->OnUpdate(dt);

  // std::cout << "Voltage: " << frc::RobotController::GetBatteryVoltage().value() << std::endl;
  }

void Robot::AutonomousInit() {
  // m_driveSim->SetPath(m_path_chooser.GetSelected());

  loop.Clear();
  sched->InterruptAll();
  // _swerveDrive->OnStart();
}
void Robot::AutonomousPeriodic() {
  // m_driveSim->OnUpdate();
}

void Robot::TeleopInit() {

  led->SectionColor(0, RGBpreset::kMagenta);
  // _swerveDrive->OnStart();
  // sched->InterruptAll();
}
void Robot::TeleopPeriodic() {
  // for (int i = 0; i < 200; i++){
  
  //   m_ledBuffer[i].SetRGB(255, 0, 0);

  // };
  // m_led.SetData(m_ledBuffer);
  
//   for (int i = 2; i < kLength; i++) {
//    m_ledBuffer[i].SetRGB(0, 255, 0);
// }

//m_led.SetData(m_ledBuffer);
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {
  led->DisableAll();
}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}




