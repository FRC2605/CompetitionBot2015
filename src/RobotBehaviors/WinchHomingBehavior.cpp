#include "WinchHomingBehavior.h"

WinchHomingBehavior :: WinchHomingBehavior ( LinearSlide * Winch ):
	Winch ( Winch )
{
};

WinchHomingBehavior :: ~WinchHomingBehavior ()
{
};

void WinchHomingBehavior :: Init ()
{
};

void WinchHomingBehavior :: Destroy ()
{
};

void WinchHomingBehavior :: Start ()
{
	
	Winch -> Enable ();
	Winch -> Home ();
	
};

void WinchHomingBehavior :: Stop ()
{
	
	Winch -> Disable ();
	
};

void WinchHomingBehavior :: Update ()
{
	
	Winch -> Update ();
	
};

const char * WinchHomingBehavior :: GetDefaultBehaviorID ()
{
	
	return WINCHHOMINGBEHAVIOR_BID;
	
};

