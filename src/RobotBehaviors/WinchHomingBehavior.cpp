#include "WinchHomingBehavior.h"

#include <iostream>

WinchHomingBehavior :: WinchHomingBehavior ( LinearSlide * Winch, LinearSlide * Ballast, const char * WinchControlBehaviorID, bool StartWinchControl ):
	Winch ( Winch ),
	Ballast ( Ballast ),
	Homed ( false ),
	Controller ( NULL ),
	AppliedID ( NULL ),
	WinchControlID ( WinchControlBehaviorID ),
	StartWinchControl ( StartWinchControl )
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
	
	if ( ! Homed )
	{
		
		Ballast -> HomeLow ();
		
		Winch -> SetPosition ( 0.0 );
		
		Winch -> OverrideLowLimit ( 0.0 );
		Winch -> OverrideHighLimit ( 92000.0 );
		
		Winch -> TargetPosition ( 0.0 );
		
		std :: cout << "Homing low\n";
		
	}
	
};

void WinchHomingBehavior :: Stop ()
{
	
	Winch -> Disable ();
	Ballast -> Disable ();
	
};

void WinchHomingBehavior :: Update ()
{
	
	Winch -> Update ();
	Ballast -> Update ();
	
	if ( ! Homed )
	{
		
		Homed = Winch -> TargetReached ( 400.0 ) && Ballast -> TargetReached ( 400.0 );
		
	}
	
	if ( Homed )
	{
		
		Controller -> StopBehavior ( AppliedID );
		
		if ( StartWinchControl )
			Controller -> StartBehavior ( WinchControlID );
		
	}
	
};

void WinchHomingBehavior :: ResetHomed ()
{
	
	Homed = false;
	
};

void WinchHomingBehavior :: SetStartWinchControl ( bool DoStart )
{
	
	StartWinchControl = DoStart;
	
};

const char * WinchHomingBehavior :: GetDefaultBehaviorID ()
{
	
	return WINCHHOMINGBEHAVIOR_BID;
	
};

