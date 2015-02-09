#include "Robot.h"

Robot :: Robot ():
	IterativeRobot (),
	WheelConfig ( CANTalon :: kSpeed, CANTalonConfiguration :: kFeedbackType_QuadratureEncoder ),
	VProfile ( 2.0 ),
	DriveBase ( 40, 1, 43, 15, 41, 13, 42, 14, WheelConfig, 40.0, 120.0 ),
	DriveTrain ( & DriveBase ),
	StrafeStick ( 0 ),
	RotateStick ( 1 ),
	Lift ( 1 )
{
	WheelConfig.SetPIDF ( 0.2, 0.0, 0.0, 0.0 );
	WheelConfig.SetControlSlot ( 0 );
	WheelConfig.SetRampRates ( 0.0, 0.0 );
	WheelConfig.SetNeutralMode ( CANTalon :: kNeutralMode_Brake );

	DriveBase.SetWheelConfig ( WheelConfig );
	DriveBase.SetInversion ( false, true, false, true );

	DriveTrain.SetMotorScale ( 7000 );
	DriveTrain.AddMagDirFilter ( & VProfile );
};

Robot :: ~Robot ()
{
};

void Robot :: TeleopInit ()
{
	//Nav 6??
	DriveTrain.Enable ();
};

void Robot :: TeleopPeriodic()
{
	double X;
	double Y;
	double R;
	
	bool BLiftUp;
	bool BLiftDown;
	
	X = StrafeStick.GetX ();
	Y = StrafeStick.GetY ();
	
	R = RotateStick.GetX ();
	BLiftUp = RotateStick.GetButtonState ( 1 );
	BLiftDown = RotateStick.GetButtonState ( 2 );

	DriveTrain.SetTranslation ( X , - Y );
	DriveTrain.SetRotation ( R );

	DriveTrain.PushTransform ();

	if ( BLiftUp && ! BLiftDown )
		Lift.Set ( 1.0 );
	else if ( BLiftDown && ! BLiftUp )
		Lift.Set ( - 1.0 );
	else
		Lift.Set ( 0.0 );
};

void Robot :: DisabledInit ()
{
	DriveTrain.Disable();
};

void Robot :: DisabledPeriodic ()
{

	//std :: cout << "Connected: " << ( Nav6.IsConnected () ? "Yes" : "No" ) << ", Yaw: " << Nav6.GetYaw () << "\n";

};

START_ROBOT_CLASS ( ROBOT_CLASS )
