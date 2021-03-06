#include "Robot.h"

#include <math.h>

Robot :: Robot ():
	WheelConfig ( CANTalon :: kSpeed, CANTalonConfiguration :: kFeedbackType_QuadratureEncoder ),
	VelocityDriveBase ( 40, 14, 42, 1, 44, 15, 43, 0, WheelConfig, 40.0, 120.0 ),
	PositionDriveBase ( 40, 14, 42, 1, 44, 15, 43, 0, CANTalon :: QuadEncoder, 40.0, 120.0 ),
	
	Nav6Port ( Nav6 :: GetDefaultBaudRate () ),
	Nav6Com ( & Nav6Port ),
	Nav ( & Nav6Com, 100 ),
	Nav6YawInput ( & Nav ),
	OrientationOffset ( & Nav6YawInput ),
	VProfile ( 2.0 ),
	StrafeTVP ( 4.0 ),

	Drive ( & VelocityDriveBase ),

	WinchServo ( 41, CANTalon :: QuadEncoder, 2 ),
	Winch ( & WinchServo, NULL, 10000.0, 0.0, 0.0, 100000.0 ),
	
	BallastServo ( 45, CANTalon :: QuadEncoder, 13 ),
	BallastLowLimit ( 0 ),
	BallastLimits ( & BallastLowLimit, NULL ),
	Ballast ( & BallastServo, & BallastLimits, - 7000.0, 0.0 ),

	StrafeStick ( 0 ),
	RotateStick ( 1 ),
	DSButtons ( 5 ),
	
	StrafeInput ( & StrafeStick ),
	RotateInput ( & RotateStick ),

	WinchUpButton ( & RotateStick, 3 ),
	WinchDownButton ( & RotateStick, 2 ),

	TurboButton ( & StrafeStick, 2 ),
	
	WinchButton0 ( & RotateStick, 1 ),
	WinchButton1 ( & RotateStick, 7 ),
	WinchButton2 ( & RotateStick, 8 ),
	WinchButton3 ( & RotateStick, 9 ),
	WinchButton4 ( & RotateStick, 10 ),
	
	BallastButton0 ( & RotateStick, 4 ),
	BallastButton1 ( & RotateStick, 5 ),
	
	WinchLight0 ( & DSButtons, 1 ),
	WinchLight1 ( & DSButtons, 2 ),
	WinchLight2 ( & DSButtons, 3 ),
	WinchLight3 ( & DSButtons, 4 ),
	WinchLight4 ( & DSButtons, 5 ),

	Behaviors (),
	
	WinchPosition0 ( & WinchButton0, & WinchLight0, 0.0 ),
	WinchPosition1 ( & WinchButton1, & WinchLight1, 31200.0 ),
	WinchPosition2 ( & WinchButton2, & WinchLight2, 51322.0 ),
	WinchPosition3 ( & WinchButton3, & WinchLight3, 71007.0 ),
	WinchPosition4 ( & WinchButton4, & WinchLight4, 90800.0 ),
	
	BallastPosition0 ( & BallastButton0, NULL, 0.0 ),
	BallastPosition1 ( & BallastButton1, NULL, - 12000.0 ),
	
	DriveBehavior ( & Drive, & StrafeInput, & RotateInput, & TurboButton, 30000.0, 7000.0, & PositionDriveBase, & VelocityDriveBase ),
	HomingBehavior ( & Winch, & Ballast ),
	WinchBehavior ( & Winch, & Ballast, & WinchUpButton, & WinchDownButton, 24000.0 ),
	AutoBehavior ( & Drive, & Winch, & Ballast, & Nav6YawInput, 30000.0, & PositionDriveBase ),
	YawCalibrationBehavior ( & OrientationOffset, M_PI )
{
	
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition0 );
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition1 );
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition2 );
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition3 );
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition4 );
	
	WinchBehavior.AddBallastPositionTargetButton ( & BallastPosition0 );
	WinchBehavior.AddBallastPositionTargetButton ( & BallastPosition1 );
	
	WinchServo.SetProfileSlot ( 0 );
	WinchServo.SetPIDF ( 0.5, 0.0, 0.9, 0.0 );
	WinchServo.SetSensorInverted ( true );
	
	Winch.SetVRamp ( 70000.0 );
	
	BallastServo.SetProfileSlot ( 0 );
	BallastServo.SetSensorInverted ( true );
	BallastServo.SetPIDF ( 0.7, 0.0, 0.3, 0.0 );
	
	WheelConfig.SetPIDF ( 0.5, 0.0, 2.0, 0.0 );
	WheelConfig.SetControlSlot ( 0 );
	WheelConfig.SetRampRates ( 25.0, 0.0 );
	WheelConfig.SetNeutralMode ( CANTalon :: kNeutralMode_Brake );
	
	VelocityDriveBase.SetWheelConfig ( WheelConfig );
	VelocityDriveBase.SetInversion ( false, true, false, true );
	VelocityDriveBase.SetSensorInversion ( false, true, false, true );
	
	PositionDriveBase.SetPIDF ( 0.7, 0.0, 0.3, 0.0 );
	PositionDriveBase.SetProfileSlot ( 0 );
	PositionDriveBase.SetInversion ( false, true, false, true );
	PositionDriveBase.SetSensorInversion ( false, true, false, true );
	
	Drive.SetMotorScale ( 7000.0 );
	Drive.AddMagDirFilter ( & VProfile );
	Drive.AddMagDirFilter ( & OrientationOffset );
	Drive.AddXYFilter ( & StrafeTVP ),

	StrafeInput.SetDeadband ( 0.09 );
	RotateInput.SetDeadband ( 0.09 );
	
	StrafeInput.SetInversion ( false, true );
	
	Behaviors.AddBehavior ( & DriveBehavior, JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	Behaviors.AddBehavior ( & HomingBehavior, WinchHomingBehavior :: GetDefaultBehaviorID () );
	Behaviors.AddBehavior ( & WinchBehavior, WinchControlBehavior :: GetDefaultBehaviorID () );
	Behaviors.AddBehavior ( & AutoBehavior, AutonomousBehavior :: GetDefaultBehaviorID () );
	Behaviors.AddBehavior ( & YawCalibrationBehavior, Nav6CalibrationBehavior :: GetDefaultBehaviorID () );
	
	Behaviors.StartBehavior ( Nav6CalibrationBehavior :: GetDefaultBehaviorID () );
	Behaviors.StartBehavior ( WinchHomingBehavior :: GetDefaultBehaviorID () );
	
	Nav.Start ();
	
};

Robot :: ~Robot ()
{
};

void Robot :: TeleopInit ()
{
	
	Behaviors.StartBehavior ( JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	Behaviors.StartBehavior ( WinchControlBehavior :: GetDefaultBehaviorID () );
	
};

void Robot :: TestInit ()
{
	
	HomingBehavior.ResetHomed ();
	
	Behaviors.StartBehavior ( WinchHomingBehavior :: GetDefaultBehaviorID () );
	
};

void Robot :: AutonomousInit ()
{
	
	Behaviors.StopBehavior ( Nav6CalibrationBehavior :: GetDefaultBehaviorID () );
	
	Behaviors.StartBehavior ( AutonomousBehavior :: GetDefaultBehaviorID () );
	
};

void Robot :: DisabledInit ()
{
	
	Behaviors.StopBehavior ( JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	Behaviors.StopBehavior ( WinchHomingBehavior :: GetDefaultBehaviorID () );
	Behaviors.StopBehavior ( WinchControlBehavior :: GetDefaultBehaviorID () );
	Behaviors.StopBehavior ( AutonomousBehavior :: GetDefaultBehaviorID () );
	
};

void Robot :: TeleopPeriodic ()
{
	
	Behaviors.Update ();
	
};

void Robot :: TestPeriodic ()
{
	
	Behaviors.Update ();
	
};

void Robot :: AutonomousPeriodic ()
{
	
	Behaviors.Update ();
	
};

void Robot :: DisabledPeriodic ()
{
	
	Behaviors.Update ();
	
};


START_ROBOT_CLASS ( ROBOT_CLASS )
