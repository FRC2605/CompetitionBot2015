#include "Robot.h"

Robot :: Robot ():
	WheelConfig ( CANTalon :: kSpeed, CANTalonConfiguration :: kFeedbackType_QuadratureEncoder ),
	DriveBase ( 40, 14, 42, 1, 44, 15, 43, 0, WheelConfig, 40.0, 120.0 ),

	Nav6Port ( Nav6 :: GetDefaultBaudRate () ),
	Nav6Com ( & Nav6Port ),
	Nav ( & Nav6Com, 100 ),
	Nav6YawInput ( & Nav ),
	OrientationOffset ( & Nav6YawInput ),

	VProfile ( 2.0 ),
	Drive ( & DriveBase ),

	WinchServo ( 41, CANTalon :: QuadEncoder, 2 ),
	Winch ( & WinchServo, NULL, 10000.0, 0.0, 0.0, 100000 ),
	
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

	FinePositioningButton ( & StrafeStick, 2 ),
	
	WinchButton0 ( & DSButtons, 10 ),
	WinchButton1 ( & DSButtons, 1 ),
	WinchButton2 ( & DSButtons, 2 ),
	WinchButton3 ( & DSButtons, 3 ),
	WinchButton4 ( & DSButtons, 4 ),
	
	BallastButton0 ( & DSButtons, 8 ),
	BallastButton1 ( & DSButtons, 9 ),
	
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
	
	DriveBehavior ( & Drive, & StrafeInput, & RotateInput, & FinePositioningButton ),
	HomingBehavior ( & Winch, & Ballast, WinchControlBehavior :: GetDefaultBehaviorID (), false ),
	WinchBehavior ( & Winch, & Ballast, & WinchUpButton, & WinchDownButton, 15000.0 )
{
	
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition0 );
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition1 );
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition2 );
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition3 );
	WinchBehavior.AddWinchPositionTargetButton ( & WinchPosition4 );
	
	WinchBehavior.AddBallastPositionTargetButton ( & BallastPosition0 );
	WinchBehavior.AddBallastPositionTargetButton ( & BallastPosition1 );
	
	WinchServo.SetProfileSlot ( 0 );
	WinchServo.SetPIDF ( 0.7, 0.0, 0.3, 0.0 );
	WinchServo.SetSensorInverted ( true );
	
	BallastServo.SetProfileSlot ( 0 );
	BallastServo.SetSensorInverted ( true );
	BallastServo.SetPIDF ( 0.7, 0.0, 0.3, 0.0 );
	
	WheelConfig.SetPIDF ( 0.5, 0.0, 2.0, 0.0 );
	WheelConfig.SetControlSlot ( 0 );
	WheelConfig.SetRampRates ( 25.0, 0.0 );
	WheelConfig.SetNeutralMode ( CANTalon :: kNeutralMode_Brake );
	
	DriveBase.SetWheelConfig ( WheelConfig );
	DriveBase.SetInversion ( false, true, false, true );
	DriveBase.SetSensorInversion ( true, false, false, true );
	
	Drive.SetMotorScale ( 7000 );
	Drive.AddMagDirFilter ( & VProfile );
	Drive.AddMagDirFilter ( & OrientationOffset );
	
	StrafeInput.SetDeadband ( 0.09 );
	RotateInput.SetDeadband ( 0.09 );
	
	StrafeInput.SetInversion ( false, true );
	
	Behaviors.AddBehavior ( & DriveBehavior, JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	Behaviors.AddBehavior ( & HomingBehavior, WinchHomingBehavior :: GetDefaultBehaviorID () );
	Behaviors.AddBehavior ( & WinchBehavior, WinchControlBehavior :: GetDefaultBehaviorID () );
	
	Nav.Start ();
	
};

Robot :: ~Robot ()
{
};

void Robot :: TeleopInit ()
{
	
	HomingBehavior.SetStartWinchControl ( true );
	
	HomingBehavior.ResetHomed ();
	
	Behaviors.StartBehavior ( JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	Behaviors.StartBehavior ( WinchHomingBehavior :: GetDefaultBehaviorID () );
	
};

void Robot :: TestInit ()
{
	
	HomingBehavior.SetStartWinchControl ( false );
	HomingBehavior.ResetHomed ();
	
	Behaviors.StartBehavior ( WinchHomingBehavior :: GetDefaultBehaviorID () );
	
};

void Robot :: AutonomousInit ()
{
	
	HomingBehavior.SetStartWinchControl ( false );
	
	Behaviors.StartBehavior ( WinchHomingBehavior :: GetDefaultBehaviorID () );
	
};

void Robot :: DisabledInit ()
{
	
	Behaviors.StopBehavior ( JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	Behaviors.StopBehavior ( WinchHomingBehavior :: GetDefaultBehaviorID () );
	Behaviors.StopBehavior ( WinchControlBehavior :: GetDefaultBehaviorID () );
	
	
};

void Robot :: TeleopPeriodic ()
{
	
	Behaviors.Update ();
	
	std :: cout << "Winch position: " << Winch.GetPosition () << "\n";
	
};

void Robot :: TestPeriodic ()
{
	
	Behaviors.Update ();
	
};

void Robot :: AutonomousPeriodic ()
{
	
	Behaviors.Update ();
	
	OrientationOffset.CalibrateZero ();
	
};

void Robot :: DisabledPeriodic ()
{
	
	Behaviors.Update ();
	
};


START_ROBOT_CLASS ( ROBOT_CLASS )
