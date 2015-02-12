#ifndef SHS2605_POSITIONCONTROLBEHAVIOR_H
#define SHS2605_POSITIONCONTROLBEHAVIOR_H

#include "WinchControllBehavior.h"

#include <cstddef>
#include <iostream>

WinchControllBehavior :: WinchControllBehavior ( LinearSlide * Winch, IBooleanInput * UpButton, IBooleanInput * DownButton, double JogSpeed ):
	Winch ( Winch ),
	UpButton ( UpButton ),
	DownButton ( DownButton ),
	PositionTargets (),
	JogSpeed ( JogSpeed ),
	Targeting ( false )
{
};

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
	
	Winch -> RunVelocity ( 0.0 );
	
	Winch -> Enable ();
	
	Targeting = false;
	
};

void WinchControllBehavior :: Stop ()
{
	
	Winch -> Disable ();
	
};

#include <iostream>

void WinchControllBehavior :: Update ()
{
	
	if ( UpButton -> GetBoolean () && ( ! DownButton -> GetBoolean () ) )
	{
		
		Winch -> RunVelocity ( JogSpeed );
		
		Targeting = false;
		
	}
	else if ( DownButton -> GetBoolean () && ( ! UpButton -> GetBoolean () ) )
	{
		
		Winch -> RunVelocity ( - JogSpeed );
		
		Targeting = false;
		
	}
	else if ( ! Targeting )
		Winch -> RunVelocity ( 0 );
	
	for ( uint32_t i = 0; i < PositionTargets.Length (); i ++ )
	{
		
		PositionTargetButton * Target = PositionTargets [ i ];
		
		if ( Target -> Button -> GetBoolean () )
		{
			
			Winch -> TargetPosition ( Target -> SetPoint );
			
			Targeting = true;
			
			break;
			
		}
		
	}
	
	Winch -> Update ();
	
	std :: cout << "WinchPosition: " << Winch -> GetPosition () << "\n";
	
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
