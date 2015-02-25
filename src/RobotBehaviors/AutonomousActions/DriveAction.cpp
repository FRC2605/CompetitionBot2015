#include "DriveAction.h"

DriveAction :: DriveAction ( MecanumDriveTrain * Drive, double XSpeed, double YSpeed, double Time ):
	Drive ( Drive ),
	XSpeed ( XSpeed ),
	YSpeed ( YSpeed ),
	Time ( Time ),
	Timer ()
{
};

DriveAction :: ~DriveAction ()
{
};

void DriveAction :: Reset ()
{
	
	Timer.Reset ();
	
};

void DriveAction :: Start ()
{
	
	if ( Timer.GetTimeS () < Time )
	{
		
		Drive -> SetTranslation ( XSpeed, YSpeed );
		Drive -> SetRotation ( 0.0 );
		
		Drive -> PushTransform ();
		
	}
	
	Timer.Start ();
	
};

bool DriveAction :: IsComplete ()
{
	
	return Timer.GetTimeS () >= Time;
	
};

void DriveAction :: Stop ()
{
	
	Drive -> SetTranslation ( 0.0, 0.0 );
	Drive -> SetRotation ( 0.0 );
	
	Drive -> PushTransform ();
	
	Timer.Stop ();
	
};

void DriveAction :: Update ()
{
};
