#include "BallastPositionAction.h"

BallastPositionAction :: BallastPositionAction ( LinearSlide * Ballast, double Position, double Tolerance ):
	Ballast ( Ballast ),
	Position ( Position ),
	Tolerance ( Tolerance )
{
};

BallastPositionAction :: ~BallastPositionAction ()
{
};

void BallastPositionAction :: Reset ()
{
};

void BallastPositionAction :: Start ()
{
	
	Ballast -> TargetPosition ( Position );
	
};

bool BallastPositionAction :: IsComplete ()
{
	
	return Ballast -> TargetReached ( Tolerance );
	
};

void BallastPositionAction :: Stop ()
{
	
	Ballast -> RunVelocity ( 0.0 );
	
};

void BallastPositionAction :: Update ()
{
};
