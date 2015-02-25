#include "TurnAction.h"

#include <math.h>

TurnAction :: TurnAction ( MecanumDriveTrain * Drive, IAngularInput * Angle, double Target, double RotationSpeed, double Tolerance ):
	Drive ( Drive ),
	Angle ( Angle ),
	Offset ( 0.0 ),
	Turned ( 0.0 ),
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
	
	Turned = 0.0;
	
};

void TurnAction :: Start ()
{
	
	Offset = Angle -> GetAngle ();
	
	Drive -> SetRotation ( RotationSpeed );
	Drive -> SetTranslation ( 0.0, 0.0 );
	
	Drive -> PushTransform ();
	
};

bool TurnAction :: IsComplete ()
{
	
	double Total = Turned + ( Angle -> GetAngle () - Offset );
	
	return fabs ( Total ) > Target;
	
};

void TurnAction :: Stop ()
{
	
	double CAngle = Angle -> GetAngle ();
	
	Turned += CAngle - Offset;
	Offset = CAngle;
	
	Drive -> SetRotation ( 0.0 );
	Drive -> SetTranslation ( 0.0, 0.0 );
	
	Drive -> PushTransform ();
	
};

void TurnAction :: Update ()
{
};
