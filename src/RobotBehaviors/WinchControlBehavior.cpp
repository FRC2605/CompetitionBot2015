#ifndef SHS2605_POSITIONCONTROLBEHAVIOR_H
#define SHS2605_POSITIONCONTROLBEHAVIOR_H

#include <RobotBehaviors/WinchControlBehavior.h>
#include <cstddef>
#include <iostream>

WinchControlBehavior :: WinchControlBehavior ( LinearSlide * Winch, IBooleanInput * UpButton, IBooleanInput * DownButton, double JogSpeed ):
	Winch ( Winch ),
	UpButton ( UpButton ),
	DownButton ( DownButton ),
	PositionTargets (),
	JogSpeed ( JogSpeed ),
	Targeting ( false )
{
};

WinchControlBehavior :: ~WinchControlBehavior ()
{
};

void WinchControlBehavior :: Init ( BehaviorController * Controller, const char * AppliedID )
{
};

void WinchControlBehavior :: Destroy ()
{
};

void WinchControlBehavior :: Start ()
{
	
	Winch -> RunVelocity ( 0.0 );
	
	Winch -> Enable ();
	
	Targeting = false;
	
};

void WinchControlBehavior :: Stop ()
{
	
	Winch -> Disable ();
	
};

#include <iostream>

void WinchControlBehavior :: Update ()
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
	{
		
		Winch -> RunVelocity ( 0 );
		
	}
	
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
	
};

void WinchControlBehavior :: AddPositionTargetButton ( PositionTargetButton * Target )
{
	
	if ( Target == NULL )
		return;
	
	if ( PositionTargets.IndexOf ( Target, 0 ) == - 1 )
		return;
	
	PositionTargets.Push ( Target );
	
};

void WinchControlBehavior :: RemovePositionTargetButton ( PositionTargetButton * Target )
{
	
	int32_t Index = PositionTargets.IndexOf ( Target, 0 );
	
	if ( Index == - 1 )
		return;
	
	PositionTargets.Remove ( Index, 1 );
	
};

const char * WinchControlBehavior :: GetDefaultBehaviorID ()
{
	
	return WinchControlBEHAVIOR_BID;
	
};

#endif
