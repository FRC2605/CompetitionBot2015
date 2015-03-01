#include "WaitAction.h"

WaitAction :: WaitAction ( double Delay ):
	Wait ( Delay ),
	Timer ()
{
};

WaitAction :: ~WaitAction ()
{
};

void WaitAction :: Reset ()
{
	
	Timer.Reset ();
	
};

void WaitAction :: Start ()
{
	
	Timer.Start ();
	
};

bool WaitAction :: IsComplete ()
{
	
	return ( Timer.GetTimeS () >= Wait );
	
};

void WaitAction :: Stop ()
{
	
	Timer.Stop ();
	
};
	
void WaitAction :: Update ()
{
	
	
	
};

