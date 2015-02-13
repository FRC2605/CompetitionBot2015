#include "Robot.h"

Robot :: Robot ():
	WheelConfig ( CANTalon :: kSpeed, CANTalonConfiguration :: kFeedbackType_QuadratureEncoder ),
	DriveBase ( 42, 14, 41, 13, 43, 15, 40, 1, WheelConfig, 40.0, 120.0 ),
	Nav6Port ( Nav6 :: GetDefaultBaudRate () ),
	Nav6Com ( & Nav6Port ),
	Nav ( & Nav6Com, 100 ),
	Nav6YawInput ( & Nav ),
	OrientationOffset ( & Nav6YawInput ),
	VProfile ( 2.0 ),
	Drive ( & DriveBase ),
	WinchServo ( 44, CANTalon :: QuadEncoder, 0 ),
	WinchLimitHigh ( 2 ),
	WinchLimitLow ( 1 ),
	WinchLimits ( & WinchLimitLow, NULL ),
	Winch ( & WinchServo, & WinchLimits, 10000.0, 0.0 ),
	StrafeStick ( 0 ),
	RotateStick ( 1 ),
	StrafeInput ( & StrafeStick ),
	RotateInput ( & RotateStick ),
	WinchUpButton ( & RotateStick, 3 ),
	WinchDownButton ( & RotateStick, 2 ),
	FinePositioningButton ( & StrafeStick, 2 ),
	Behaviors (),
	DriveBehavior ( & Drive, & StrafeInput, & RotateInput, & FinePositioningButton ),
	HomingBehavior ( & Winch, WinchControllBehavior :: GetDefaultBehaviorID (), false ),
	WinchBehavior ( & Winch, & WinchUpButton, & WinchDownButton, 20000.0 )
{
	
	WinchServo.SetProfileSlot ( 0 );
	WinchServo.SetPIDF ( 0.7, 0.0, 0.3, 0.0 );
	
	WheelConfig.SetPIDF ( 0.2, 0.0, 0.0, 0.0 );
	WheelConfig.SetControlSlot ( 0 );
	WheelConfig.SetRampRates ( 0.0, 0.0 );
	WheelConfig.SetNeutralMode ( CANTalon :: kNeutralMode_Brake );
	
	DriveBase.SetWheelConfig ( WheelConfig );
	DriveBase.SetInversion ( false, true, false, true );
	
	Drive.SetMotorScale ( 7000 );
	Drive.AddMagDirFilter ( & VProfile );
	Drive.AddMagDirFilter ( & OrientationOffset );
	
	StrafeInput.SetDeadband ( 0.09 );
	RotateInput.SetDeadband ( 0.09 );
	
	StrafeInput.SetInversion ( false, true );
	
	Behaviors.AddBehavior ( & DriveBehavior, JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	Behaviors.AddBehavior ( & HomingBehavior, WinchHomingBehavior :: GetDefaultBehaviorID () );
	Behaviors.AddBehavior ( & WinchBehavior, WinchControllBehavior :: GetDefaultBehaviorID () );
	
	Nav.Start ();
	
};

Robot :: ~Robot ()
{
};

void Robot :: TeleopInit ()
{
	
	HomingBehavior.SetStartWinchControl ( true );
	
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
	Behaviors.StopBehavior ( WinchControllBehavior :: GetDefaultBehaviorID () );
	
	
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
	
	OrientationOffset.CalibrateZero ();
	
};

void Robot :: DisabledPeriodic ()
{
	
	Behaviors.Update ();
	
};


START_ROBOT_CLASS ( ROBOT_CLASS )
