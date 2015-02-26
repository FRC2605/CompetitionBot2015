#include "TurnAction.h"

#include <math.h>

TurnAction :: TurnAction ( MecanumDriveTrain * Drive, IAngularInput * Angle, double Target, double RotationSpeed, double Tolerance ):
	Drive ( Drive ),
	Tracker ( Angle ),
	Target ( Target ),
	RotationSpeed ( RotationSpeed ),
	Tolerance ( Tolerance )
{	
};

TurnAction :: ~TurnAction ()
{
};

void TurnAction :: Reset ()
{
	
	Tracker.Set ( 0.0 );
	
};

void TurnAction :: Start ()
{
	
	Tracker.SyncAngle ();
	
	Drive -> SetRotation ( RotationSpeed );
	Drive -> SetTranslation ( 0.0, 0.0 );
	
	Drive -> PushTransform ();
	
};

bool TurnAction :: IsComplete ()
{
	
	if ( Target < 0 )
		return ( Target - Tracker.Get () ) > - Tolerance;
	
	return ( Target - Tracker.Get () ) < Tolerance;
	
};

void TurnAction :: Stop ()
{
	
	Tracker.Update ();
	
	Drive -> SetRotation ( 0.0 );
	Drive -> SetTranslation ( 0.0, 0.0 );
	
	Drive -> PushTransform ();
	
};

void TurnAction :: Update ()
{
	
	Tracker.Update ();
	
};
