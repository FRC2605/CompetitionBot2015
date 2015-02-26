#include "WinchHomingBehavior.h"

#include <iostream>

WinchHomingBehavior :: WinchHomingBehavior ( LinearSlide * Winch, LinearSlide * Ballast ):
	Winch ( Winch ),
	Ballast ( Ballast ),
	Homed ( false ),
	Controller ( NULL ),
	AppliedID ( NULL )
{
};

WinchHomingBehavior :: ~WinchHomingBehavior ()
{
};

void WinchHomingBehavior :: Init ( BehaviorController * Controller, const char * AppliedID )
{
	
	this -> Controller = Controller;
	this -> AppliedID = AppliedID;
	
};

void WinchHomingBehavior :: Destroy ()
{
};

void WinchHomingBehavior :: Start ()
{
	
	Ballast -> Enable ();
	Winch -> Enable ();
	
	Ballast -> RunVelocity ( 0.0 );
	Winch -> RunVelocity ( 0.0 );

	if ( ! Homed )
	{
		
		Ballast -> SetPosition ( 0.0 );
		Ballast -> OverrideLowLimit ( 0.0 );
		Ballast -> OverrideHighLimit ( 12500 );
		
		Winch -> SetPosition ( 0.0 );
		Winch -> OverrideLowLimit ( 0.0 );
		Winch -> OverrideHighLimit ( 92000.0 );
		
	}
	
};

void WinchHomingBehavior :: Stop ()
{
	
	Winch -> Disable ();
	Ballast -> Disable ();
	
};

void WinchHomingBehavior :: Update ()
{
	
	Homed = true;
	
	Controller -> StopBehavior ( AppliedID );
	
};

void WinchHomingBehavior :: ResetHomed ()
{
	
	Homed = false;
	
};

const char * WinchHomingBehavior :: GetDefaultBehaviorID ()
{
	
	return WINCHHOMINGBEHAVIOR_BID;
	
};

