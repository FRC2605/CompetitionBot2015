#include "AutonomousBehavior.h"

AutonomousBehavior :: AutonomousBehavior ( MecanumDriveTrain * Drive, LinearSlide * Winch, LinearSlide * Ballast, IAngularInput * RobotYaw, double MotorSpeed, IQuadRectangularDriveBase * DriveBase ):
	Drive ( Drive ),
	Winch ( Winch ),
	Ballast ( Ballast ),
	MotorSpeed ( MotorSpeed ),
	DriveBase ( DriveBase ),
	Drive1 ( Drive, 0, - 0.23, 0.8 ),
	WinchPos1 ( Winch, 31200.0, 400.0 ),
	Wait1 ( 5.0 ),
	Turn1 ( Drive, RobotYaw, - M_PI, - 0.15, 0.01, false ),
	Drive2 ( Drive, 0, 0.5, 2.6 ),
	WinchPos2 ( Winch, 0.0, 400.0 ),
	BallastPos1 ( Ballast, 10000.0, 400.0 ),
	BallastPos2 ( Ballast, 0.0, 400.0 ),
	Actions ()
{
	
	//Actions.AddAction ( & Drive1 );
	Actions.AddAction ( & WinchPos1 );
	Actions.AddAction ( & Wait1 );
	Actions.AddAction ( & Turn1 );
	Actions.AddAction ( & Drive2 );
	Actions.AddAction ( & WinchPos2 );
	//Actions.AddAction ( & BallastPos1 );
	//Actions.AddAction ( & BallastPos2 );
	
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
	
	Actions.Reset ();
	Actions.Start ();

	Drive -> SetPreScale ( 0.5, 0.5 );
	Drive -> SetDriveBase ( DriveBase );
	Drive -> SetMotorScale ( MotorSpeed );
	
	Drive -> Enable ();
	Winch -> Enable ();
	Ballast -> Enable ();
	
};

void AutonomousBehavior :: Stop ()
{
	
	Actions.Stop ();
	
	Drive -> Disable ();
	Winch -> Disable ();
	Ballast -> Disable ();
	
};

void AutonomousBehavior :: Update ()
{
	
	Actions.Update ();
	
	Winch -> Update ();
	Ballast -> Update ();
	Drive -> Update ();
	
};

const char * AutonomousBehavior :: GetDefaultBehaviorID ()
{
	
	return AUTOBEHAVIOR_BID;
	
};
