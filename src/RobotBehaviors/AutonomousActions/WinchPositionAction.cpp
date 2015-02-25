#include "WinchPositionAction.cpp"

WinchPositionAction :: WinchPositionAction ( LinearSlide * Winch, double Position, double Tolerance ):
	Winch ( Winch ),
	Position ( Position ),
	Tolerance ( Tolerance )
{
};

WinchPositionAction :: ~WinchPositionAction ()
{
};

void WinchPositionAction :: Reset ()
{
};

void WinchPositionAction :: Start ()
{
	
	Winch -> TargetPosition ( Position );
	
};

bool WinchPositionAction :: IsComplete ()
{
	
	return Winch -> TargetReached ( Tolerance );
	
};

void WinchPositionAction :: Stop ()
{
	
	Winch -> RunVelocity ( 0.0 );
	
};

void WinchPositionAction :: Update ()
{
};
