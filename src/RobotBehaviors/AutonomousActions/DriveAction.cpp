#include "DriveAction.h"

DriveAction :: DriveAction ( MecanumDriveTrain * Drive, double XSpeed, double YSpeed, double Time ):
	Drive ( Drive ),
	XSpeed ( XSpeed ),
	YSpeed ( YSpeed ),
	Time ( Time ),
	Timer ()
{
	
	Timer.Reset ();
	
};

DriveAction :: ~DriveAction ()
{
};

void DriveAction :: Reset ()
{
	
	Timer.Reset ();
	
};

#include <iostream>

void DriveAction :: Start ()
{
	
	Timer.Start ();
	
	std :: cout << "DriveAction :: Start (), CTime: " << Timer.GetTimeS () << " of " << Time << "\n";
	
	if ( Timer.GetTimeS () < Time )
	{
		
		std :: cout << "    * X: " << XSpeed << " Y:" << YSpeed << "\n";
		
		Drive -> SetTranslation ( XSpeed, YSpeed );
		Drive -> SetRotation ( 0.0 );
		
		Drive -> PushTransform ();
		
	}
	
};

bool DriveAction :: IsComplete ()
{
	
	return Timer.GetTimeS () >= Time;
	
};

void DriveAction :: Stop ()
{
	
	std :: cout << "DriveAction :: Stop ()\n";
	
	Drive -> SetTranslation ( 0.0, 0.0 );
	Drive -> SetRotation ( 0.0 );
	
	Drive -> PushTransform ();
	
	Timer.Stop ();
	
};

void DriveAction :: Update ()
{
};
