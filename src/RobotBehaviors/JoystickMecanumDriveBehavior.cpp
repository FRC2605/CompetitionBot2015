#include "JoystickMecanumDriveBehavior.h"

JoystickMecanumDriveBehavior :: JoystickMecanumDriveBehavior ( MecanumDriveTrain * DriveTrain, IXYInput * StrafeInput, IXInput * RotationInput ):
	Drive ( DriveTrain ),
	Strafe ( StrafeInput ),
	Rotate ( RotationInput )
{
};

JoystickMecanumDriveBehavior :: ~JoystickMecanumDriveBehavior ()
{
};

void JoystickMecanumDriveBehavior :: Init ()
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
	
	Drive -> SetTranslation ( X, Y );
	Drive -> SetRotation ( R );
	
	Drive -> PushTransform ();
	
};

const char * JoystickMecanumDriveBehavior :: GetDefaultBehaviorID ()
{
	
	return JOYSTICKMECANUMDRIVE_BID;
	
};

