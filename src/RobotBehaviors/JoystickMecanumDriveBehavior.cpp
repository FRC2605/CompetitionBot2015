#include "JoystickMecanumDriveBehavior.h"

JoystickMecanumDriveBehavior :: JoystickMecanumDriveBehavior ( MecanumDriveTrain * DriveTrain, IXYInput * StrafeInput, IXInput * RotationInput, IBooleanInput * TurboButton, double LowMotorSpeed, double HighMotorSpeed, IQuadRectangularDriveBase * LowSpeedDrive, IQuadRectangularDriveBase * HighSpeedDrive ):
	Drive ( DriveTrain ),
	LowSpeedDrive ( LowSpeedDrive ),
	HighSpeedDrive ( HighSpeedDrive ),
	LowMotorSpeed ( LowMotorSpeed ),
	HighMotorSpeed ( HighMotorSpeed ),
	Strafe ( StrafeInput ),
	Rotate ( RotationInput ),
	TurboButton ( TurboButton ),
	LastTurboState ( false )
{
	
	if ( HighSpeedDrive == NULL )
		HighSpeedDrive = LowSpeedDrive;
	
};

JoystickMecanumDriveBehavior :: ~JoystickMecanumDriveBehavior ()
{
};

void JoystickMecanumDriveBehavior :: Init ( BehaviorController * Controller, const char * AppliedID )
{
};

void JoystickMecanumDriveBehavior :: Destroy ()
{
};

void JoystickMecanumDriveBehavior :: Start ()
{
	
	LastTurboState = false;
	Drive -> SetPreScale ( 0.5, 0.5 );
	Drive -> SetDriveBase ( LowSpeedDrive );
	Drive -> SetMotorScale ( LowMotorSpeed );
	
	Drive -> Enable ();
	
};

void JoystickMecanumDriveBehavior :: Stop ()
{
	
	Drive -> Disable ();
	
};

void JoystickMecanumDriveBehavior :: Update ()
{
	
	double SScale = Strafe -> GetScale ();
	
	double X = Strafe -> GetX () / SScale;
	double Y = Strafe -> GetY () / SScale;
	
	double RScale = Rotate -> GetScale ();
	
	double R = Rotate -> GetX () / RScale;
	
	if ( LastTurboState && ( ! TurboButton -> GetBoolean () ) )
	{
		
		Drive -> SetPreScale ( 0.5, 0.5 );
		Drive -> SetDriveBase ( LowSpeedDrive );
		Drive -> SetMotorScale ( LowMotorSpeed );
		
		LastTurboState = false;
		
	}
	else if ( ( ! LastTurboState ) && TurboButton -> GetBoolean () )
	{
		
		Drive -> SetPreScale ( 1.0, 1.0 );
		Drive -> SetDriveBase ( HighSpeedDrive );
		Drive -> SetMotorScale ( HighMotorSpeed );
		
		LastTurboState = true;
		
	}
	
	Drive -> SetTranslation ( X, Y );
	Drive -> SetRotation ( R / 1.5 );
	
	Drive -> PushTransform ();
	
	Drive -> Update ();
	
};

const char * JoystickMecanumDriveBehavior :: GetDefaultBehaviorID ()
{
	
	return JOYSTICKMECANUMDRIVE_BID;
	
};

