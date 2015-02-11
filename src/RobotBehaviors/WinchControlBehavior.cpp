#ifndef SHS2605_POSITIONCONTROLBEHAVIOR_H
#define SHS2605_POSITIONCONTROLBEHAVIOR_H

#include "WinchControllBehavior.h"

#include <cstddef>

WinchControllBehavior :: WinchControllBehavior ( LinearSlide * Winch, IBooleanInput * UpButton, IBooleanInput * DownButton, double JogSpeed ):
	Winch ( Winch ),
	UpButton ( UpButton ),
	DownButton ( UpButton ),
	PositionTargets (),
	JogSpeed ( JogSpeed )
{
	
	
	
}

WinchControllBehavior :: ~WinchControllBehavior ()
{
};

void WinchControllBehavior :: Init ( BehaviorController * Controller, const char * AppliedID )
{
};

void WinchControllBehavior :: Destroy ()
{
};

void WinchControllBehavior :: Start ()
{
	
	Winch -> Enable ();
	Winch -> RunVelocity ( 0 );
	
};

void WinchControllBehavior :: Stop ()
{
	
	Winch -> Disable ();
	
};

void WinchControllBehavior :: Update ()
{
	
	if ( UpButton -> GetBoolean () && ! DownButton -> GetBoolean () )
		Winch -> RunVelocity ( JogSpeed );
	
	if ( ! UpButton -> GetBoolean () && DownButton -> GetBoolean () )
			Winch -> RunVelocity ( - JogSpeed );
		
	
	for ( uint32_t i = 0; i < PositionTargets.Length (); i ++ )
	{
		
		PositionTargetButton * Target = PositionTargets [ i ];
		
		if ( Target -> Button -> GetBoolean () )
			Winch -> TargetPosition ( Target -> SetPoint );
		
	}
	
};

void WinchControllBehavior :: AddPositionTargetButton ( PositionTargetButton * Target )
{
	
	if ( Target == NULL )
		return;
	
	if ( PositionTargets.IndexOf ( Target, 0 ) == - 1 )
		return;
	
	PositionTargets.Push ( Target );
	
};

void WinchControllBehavior :: RemovePositionTargetButton ( PositionTargetButton * Target )
{
	
	int32_t Index = PositionTargets.IndexOf ( Target, 0 );
	
	if ( Index == - 1 )
		return;
	
	PositionTargets.Remove ( Index, 1 );
	
};

const char * WinchControllBehavior :: GetDefaultBehaviorID ()
{
	
	return WINCHCONTROLLBEHAVIOR_BID;
	
};

#endif
