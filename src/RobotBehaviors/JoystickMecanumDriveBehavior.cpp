#include "JoystickMecanumDriveBehavior.h"

JoystickMecanumDriveBehavior :: JoystickMecanumDriveBehavior ( MecanumDriveTrain * DriveTrain, IXYInput * StrafeInput, IXInput * RotationInput, IBooleanInput * TurboButton ):
	Drive ( DriveTrain ),
	Strafe ( StrafeInput ),
	Rotate ( RotationInput ),
	TurboButton ( TurboButton )
{
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
	
	double FineScale = TurboButton -> GetBoolean () ? 1.0 : 0.5;
	
	Drive -> SetTranslation ( X, Y );
	Drive -> SetRotation ( R / 1.5 );
	
	Drive -> SetPreScale ( FineScale, FineScale );
	
	Drive -> PushTransform ();
	
	Drive -> Update ();
	
};

const char * JoystickMecanumDriveBehavior :: GetDefaultBehaviorID ()
{
	
	return JOYSTICKMECANUMDRIVE_BID;
	
};

