#include "WinchHomingBehavior.h"

WinchHomingBehavior :: WinchHomingBehavior ( LinearSlide * Winch, const char * WinchControllBehaviorID, bool StartWinchControl ):
	Winch ( Winch ),
	Homed ( false ),
	Controller ( NULL ),
	AppliedID ( NULL ),
	WinchControllID ( WinchControllBehaviorID ),
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
	
	Winch -> Enable ();
	
	if ( ! Homed )
	{
		
		Winch -> OverrideLowLimit ( - 1000000 );
		Winch -> OverrideHighLimit ( 1000000 );
		
		Winch -> HomeLow ();
		
		
	}
	
};

void WinchHomingBehavior :: Stop ()
{
	
	Winch -> Disable ();
	
};

void WinchHomingBehavior :: Update ()
{
	
	Winch -> Update ();
	
	if ( ! Homed )
	{
		
		Homed = Winch -> TargetReached ( 0.0 );
		
	}
	
	if ( Homed )
	{
		
		Winch -> SetLowLimit ( 0.0 );
		Winch -> OverrideHighLimit ( 105012 );
		Controller -> StopBehavior ( AppliedID );
		
		if ( StartWinchControl )
			Controller -> StartBehavior ( WinchControllID );
		
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

