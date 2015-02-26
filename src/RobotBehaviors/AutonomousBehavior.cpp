#include "AutonomousBehavior.h"

AutonomousBehavior :: AutonomousBehavior ( MecanumDriveTrain * Drive, LinearSlide * Winch, IAngularInput * RobotYaw ):
	Drive ( Drive ),
	Winch ( Winch ),
	Drive1 ( Drive, 0, - 1.0, 1.0 ),
	WinchPos1 ( Winch, 31200.0, 400.0 ),
	Turn1 ( Drive, RobotYaw, M_PI, 0.5, 0.03 ),
	Drive2 ( Drive, 0, 0.5, 2.0 ),
	WinchPos2 ( Winch, 0.0, 400.0 ),
	Actions ()
{
	
	Actions.AddAction ( & Drive1 );
	/*Actions.AddAction ( & WinchPos1 );
	Actions.AddAction ( & Turn1 );
	Actions.AddAction ( & Drive2 );
	Actions.AddAction ( & WinchPos2 );*/// Commented out till we can test each thing
	
};

AutonomousBehavior :: ~AutonomousBehavior ()
{
};

void AutonomousBehavior :: Init ( BehaviorController * Controller, const char * AppliedID )
{
};

void AutonomousBehavior :: Destroy ()
{
};

void AutonomousBehavior :: Start ()
{
	
	Drive -> Enable ();
	Winch -> Enable ();
	
	Actions.Reset ();
	Actions.Start ();
	
};

void AutonomousBehavior :: Stop ()
{
	
	Actions.Stop ();
	
	Drive -> Disable ();
	Winch -> Disable ();
	
};

void AutonomousBehavior :: Update ()
{
	
	Actions.Update ();
	
	Winch -> Update ();
	
};

const char * AutonomousBehavior :: GetDefaultBehaviorID ()
{
	
	return AUTOBEHAVIOR_BID;
	
};
