#ifndef SHS2605_POSITIONCONTROLBEHAVIOR_H
#define SHS2605_POSITIONCONTROLBEHAVIOR_H

#include <RobotBehaviors/WinchControlBehavior.h>
#include <cstddef>
#include <iostream>

WinchControlBehavior :: WinchControlBehavior ( LinearSlide * Winch, LinearSlide * Ballast, IBooleanInput * UpButton, IBooleanInput * DownButton, double JogSpeed ):
	Winch ( Winch ),
	Ballast ( Ballast ),
	UpButton ( UpButton ),
	DownButton ( DownButton ),
	WinchPositionTargets (),
	BallastPositionTargets (),
	JogSpeed ( JogSpeed ),
	Targeting ( false )
{
};

WinchControlBehavior :: ~WinchControlBehavior ()
{
};

WinchControlBehavior :: PositionTargetButton_Struct :: PositionTargetButton_Struct ( IBooleanInput * Button, double SetPoint ):
	Button ( Button ),
	SetPoint ( SetPoint )
{	
};

WinchControlBehavior :: PositionTargetButton_Struct :: ~PositionTargetButton_Struct ()
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
	
	Ballast -> RunVelocity ( 0.0 );
	Ballast -> Enable ();
	
	Targeting = false;
	
};

void WinchControlBehavior :: Stop ()
{
	
	Winch -> Disable ();
	Ballast -> Disable ();
	
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
	
	PositionTargetButton * Target;
	
	for ( uint32_t i = 0; i < WinchPositionTargets.Length (); i ++ )
	{
		
		Target = WinchPositionTargets [ i ];
		
		if ( Target -> Button -> GetBoolean () )
		{
			
			Winch -> TargetPosition ( Target -> SetPoint );
			
			Targeting = true;
			
			break;
			
		}
		
	}
	
	for ( uint32_t i = 0; i < BallastPositionTargets.Length (); i ++ )
	{
		
		Target = BallastPositionTargets [ i ];
		
		if ( Target -> Button -> GetBoolean () )
			Ballast -> TargetPosition ( Target -> SetPoint );
		
	}
	
	
	Winch -> Update ();
	Ballast -> Update ();
	
};

void WinchControlBehavior :: AddWinchPositionTargetButton ( PositionTargetButton * Target )
{
	
	if ( Target == NULL )
		return;
	
	if ( WinchPositionTargets.IndexOf ( Target, 0 ) != - 1 )
		return;
	
	WinchPositionTargets.Push ( Target );
	
};

void WinchControlBehavior :: RemoveWinchPositionTargetButton ( PositionTargetButton * Target )
{
	
	int32_t Index = WinchPositionTargets.IndexOf ( Target, 0 );
	
	if ( Index == - 1 )
		return;
	
	WinchPositionTargets.Remove ( Index, 1 );
	
};

void WinchControlBehavior :: AddBallastPositionTargetButton ( PositionTargetButton * Target )
{
	
	if ( Target == NULL )
		return;
	
	if ( BallastPositionTargets.IndexOf ( Target, 0 ) != - 1 )
		return;
	
	BallastPositionTargets.Push ( Target );
	
};

void WinchControlBehavior :: RemoveBallastPositionTargetButton ( PositionTargetButton * Target )
{
	
	int32_t Index = BallastPositionTargets.IndexOf ( Target, 0 );
	
	if ( Index == - 1 )
		return;
	
	BallastPositionTargets.Remove ( Index, 1 );
	
};

const char * WinchControlBehavior :: GetDefaultBehaviorID ()
{
	
	return WinchControlBEHAVIOR_BID;
	
};

#endif
