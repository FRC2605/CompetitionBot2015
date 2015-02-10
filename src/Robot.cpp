#include "Robot.h"

Robot :: Robot ():
	WheelConfig ( CANTalon :: kSpeed, CANTalonConfiguration :: kFeedbackType_QuadratureEncoder ),
	DriveBase ( 40, 1, 43, 15, 41, 13, 42, 14, WheelConfig, 40.0, 120.0 ),
	VProfile ( 2.0 ),
	Drive ( & DriveBase ),
	WinchServo ( 44, CANTalon :: QuadEncoder, 0 ),
	WinchLimitHigh ( 0 ),
	WinchLimitLow ( 1 ),
	WinchLimits ( & WinchLimitHigh, & WinchLimitLow ),
	Winch ( & WinchServo, & WinchLimits, 10000.0, 0.0 ),
	StrafeStick ( 0 ),
	RotateStick ( 1 ),
	StrafeInput ( & StrafeStick ),
	RotateInput ( & RotateStick ),
	Behaviors (),
	DriveBehavior ( & Drive, & StrafeInput, & RotateInput ),
	HomingBehavior ( & Winch )
{
	
	StrafeInput.SetDeadband ( 0.09 );
	RotateInput.SetDeadband ( 0.09 );
	
	StrafeInput.SetInversion ( false, true );
	
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
	
	Behaviors.AddBehavior ( & DriveBehavior, JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	Behaviors.AddBehavior ( & HomingBehavior, WinchHomingBehavior :: GetDefaultBehaviorID () );
	
};

Robot :: ~Robot ()
{
};

void Robot :: TeleopInit ()
{
	
	Behaviors.StartBehavior ( JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	
};

void Robot :: TestInit ()
{
	
	
	
};

void Robot :: AutonomousInit ()
{
	
	Behaviors.StartBehavior ( WinchHomingBehavior :: GetDefaultBehaviorID () );
	
};

void Robot :: DisabledInit ()
{
	
	Behaviors.StopBehavior ( JoystickMecanumDriveBehavior :: GetDefaultBehaviorID () );
	Behaviors.StopBehavior ( WinchHomingBehavior :: GetDefaultBehaviorID () );
	
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