#ifndef SHS2605_AUTONOMOUSBEHAVIOR_H
#define SHS2605_AUTONOMOUSBEHAVIOR_H

#include <Behaviors/IBehavior.h>
#include <Actions/ActionController.h>

#include <Hardware/Drive/MecanumDriveTrain.h>

#include <Sensing/IAngularInput.h>

#include "AutonomousActions/TurnAction.h"
#include "AutonomousActions/DriveAction.h"
#include "AutonomousActions/WinchPositionAction.h"
#include "AutonomousActions/BallastPositionAction.h"
#include "AutonomousActions/WaitAction.h"

#define AUTOBEHAVIOR_BID "autonomous"

class AutonomousBehavior : public IBehavior
{
public:
	
	AutonomousBehavior ( MecanumDriveTrain * Drive, LinearSlide * Winch, LinearSlide * Ballast, IAngularInput * RobotYaw );
	~AutonomousBehavior ();
	
	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	MecanumDriveTrain * Drive;
	LinearSlide * Winch;
	LinearSlide * Ballast;
	
	DriveAction Drive1;
	WinchPositionAction WinchPos1;
	WaitAction Wait1;
	TurnAction Turn1;
	DriveAction Drive2;
	WinchPositionAction WinchPos2;
	BallastPositionAction BallastPos1;
	BallastPositionAction BallastPos2;
	
	ActionController Actions;
	
};

#endif
